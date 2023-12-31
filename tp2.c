#include "tp2.h"
#include "tp1.h"

void display(char *buffer, int length) {
    for (int i = 0; i < length-1; i++) {
        printf("%02X%02X ", (unsigned char)buffer[i],(unsigned char)buffer[i+1]);
        i++;
        if ((i + 1) % 16 == 0)
            printf("\n");
    }printf("\n");
}

// Fonction pour remplir une structure iphdr
struct iphdr fillingStructIphdr(uint16_t tot_len, uint16_t id, uint16_t frag_off,
               uint8_t ttl, uint8_t protocol, uint32_t saddr, uint32_t daddr) {
    struct iphdr ip_header;
    ip_header.version = 4; // Version IPv4
    ip_header.ihl = 5;    // Header Length en mots de 32 bits (5 mots)
    ip_header.tos = 0;    // Type of Service
    ip_header.tot_len = htons(tot_len); // Longueur totale du paquet
    ip_header.id = htons(id);           // Identificateur
    ip_header.frag_off = htons(frag_off); // Fragment Offset
    ip_header.ttl = ttl;                 // Time To Live
    ip_header.protocol = protocol;       // Protocole de transport
    ip_header.check = 0;                 // Calcul du checksum (peut être laissé à 0)
    ip_header.saddr = saddr;             // Adresse source
    ip_header.daddr = daddr;             // Adresse de destination

    return ip_header;
}

struct icmphdr fillingStructIcmphdr(uint16_t id, uint16_t sequence) {
    struct icmphdr icmp_header;
    icmp_header.type = ICMP_ECHO;             // Type ICMP (8 pour demande d'écho)
    icmp_header.code = 0;             // Code (0 pour une demande d'écho standard)
    icmp_header.checksum = 0;            // Le checksum sera calculé plus tard
    icmp_header.un.echo.id = id;         // Identifiant
    icmp_header.un.echo.sequence = sequence; // Numéro de séquence

    return icmp_header;
}
// Fonction pour calculer la somme de contrôle
short checksum(char *addr, int count) {
    uint32_t sum = 0;
    uint16_t *addr_16 = (uint16_t *)addr;

    // Boucle pour additionner tous les mots de 16 bits dans l'en-tête
    while (count > 1) {
        sum += *addr_16++;
        count -= 2;
    }

    // Gestion des octets isolés pour les paquets de taille impaire
    if (count > 0) {
        sum += *((uint8_t *)addr_16);
    }

    // Réduction de la somme à un mot de 16 bits
    while (sum >> 16) {
        sum = (sum & 0xFFFF) + (sum >> 16);
    }

    // Complément à un de la somme
    sum = ~sum;

    return (short)sum;
}

header_ip_icmp fillingIpIcmpHraderAndUpdateCheckSumIcmp(char *ip_packet,char *icmp_packet,struct iphdr ip_header,struct icmphdr icmp_header){
    header_ip_icmp headers;
    headers.icmp_header = icmp_header;
    memcpy(icmp_packet,&headers.icmp_header,sizeof(headers.icmp_header));
    headers.ip_header = ip_header;
    memcpy(ip_packet,&headers.ip_header,sizeof(headers.ip_header));
    memcpy(ip_packet + sizeof(headers.ip_header),&headers.icmp_header,sizeof(headers.icmp_header));
    display(ip_packet,sizeof(ip_packet));
    display(icmp_packet,sizeof(icmp_packet));
    //Mise en jour de la somme de controle de ICMP
    headers.icmp_header.checksum = checksum(icmp_packet,sizeof(icmp_packet));
    //printf("La somme de controle est ICMP: 0x%04X\n",headers.icmp_header.checksum);
    headers.ip_header.check = checksum(ip_packet,sizeof(ip_packet));
    //printf("La somme de controle est de IP: 0x%04X\n",headers.ip_header.check);

    return headers;
}

header_ip_icmp checkingBeforeAndAfterUpdateCheckSumIcmp(char *ip_packet,char *icmp_packet,struct iphdr ip_header,struct icmphdr icmp_header){
    header_ip_icmp headers;
    headers.icmp_header = icmp_header;
    memcpy(icmp_packet,&headers.icmp_header,sizeof(headers.icmp_header));
    headers.ip_header = ip_header;
    memcpy(ip_packet,&headers.ip_header,sizeof(headers.ip_header));
    memcpy(ip_packet + sizeof(headers.ip_header),&headers.icmp_header,sizeof(headers.icmp_header));
    printf("\n\nL'affichage AVANT le calcul de la somme de controle\n");
    display(ip_packet,sizeof(ip_packet)+sizeof(ip_header));

    headers.icmp_header.checksum = checksum(icmp_packet,sizeof(icmp_packet));
    //printf("La somme de controle est ICMP: 0x%04X\n",headers.icmp_header.checksum);
    headers.ip_header.check = checksum(ip_packet,sizeof(ip_packet));
    printf("\nL'affichage APRES le calcul de la somme de controle\n");
    //printf("La somme de controle est de IP: 0x%04X\n",headers.ip_header.check);
    display(ip_packet,sizeof(ip_packet)+sizeof(ip_header));

    return headers;
}


void creationSocketToSendPacket(struct iphdr ip_header, char *ip_packet){

// Création de la socket
    int raw_socket = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (raw_socket == -1) {
        perror("Erreur lors de la création de la socket");
        exit(EXIT_FAILURE);
    }

    // Initialisation de l'adresse de destination
    struct sockaddr_in dest_addr;
    memset(&dest_addr, 0, sizeof(dest_addr));
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(1024);
    dest_addr.sin_addr.s_addr = ip_header.daddr; //L'adresse de destination
    memset(dest_addr.sin_zero, 0, sizeof(dest_addr.sin_zero));

    // Envoi du paquet
    ssize_t bytes_sent = sendto(raw_socket, ip_packet, sizeof(ip_packet), 0,
                                (struct sockaddr *)&dest_addr, sizeof(dest_addr));

    if (bytes_sent == -1) {
        perror("Erreur lors de l'envoi du paquet");
        exit(EXIT_FAILURE);
    } else {
        printf("Paquet envoyé avec succès (%zd octets)\n", bytes_sent);
    }

    //Reception de la reponse du ping
    char buffer[100];
    struct sockaddr_in from;
    socklen_t from_len = sizeof(from);

    ssize_t recv_len = recvfrom(raw_socket, buffer, sizeof(buffer), 0,
                                (struct sockaddr *)&from, &from_len);
    printf("Reception du paquet envoyé pour l'affichage.... : \n");
    if (recv_len < 0) {
        perror("Erreur lors de la réception de la réponse");
        close(raw_socket);
        exit(EXIT_FAILURE);
    }

    // Afficher l'adresse de l'émetteur
    printf("Paquet reçu de l'adresse %s\n", inet_ntoa(from.sin_addr));

    // Fermeture de la socket
    close(raw_socket);
}




