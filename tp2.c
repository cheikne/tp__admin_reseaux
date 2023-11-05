#include "tp2.h"
#include "tp1.h"

void display(char *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02X ", (unsigned char)buffer[i]);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }printf("\n");
}

// Fonction pour remplir une structure iphdr
struct iphdr *fillingStructIphdr(uint16_t tot_len, uint16_t id, uint16_t frag_off,
               uint8_t ttl, uint8_t protocol, uint32_t saddr, uint32_t daddr) {
    struct iphdr *ip_header;
    ip_header->version = 4; // Version IPv4
    ip_header->ihl = 5;    // Header Length en mots de 32 bits (5 mots)
    ip_header->tos = 0;    // Type of Service
    ip_header->tot_len = htons(tot_len); // Longueur totale du paquet
    ip_header->id = htons(id);           // Identificateur
    ip_header->frag_off = htons(frag_off); // Fragment Offset
    ip_header->ttl = ttl;                 // Time To Live
    ip_header->protocol = protocol;       // Protocole de transport
    ip_header->check = 0;                 // Calcul du checksum (peut être laissé à 0)
    ip_header->saddr = saddr;             // Adresse source
    ip_header->daddr = daddr;             // Adresse de destination

    return ip_header;
}

struct icmphdr *fillingStructIcmphdr(uint16_t id, uint16_t sequence) {
    struct icmphdr *icmp_header;
    icmp_header->type = ICMP_ECHO;             // Type ICMP (8 pour demande d'écho)
    icmp_header->code = 0;             // Code (0 pour une demande d'écho standard)
    icmp_header->checksum = 0;            // Le checksum sera calculé plus tard
    icmp_header->un.echo.id = id;         // Identifiant
    icmp_header->un.echo.sequence = sequence; // Numéro de séquence

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

// Fonction pour calculer la somme de contrôle selon l'algorithme de la RFC 1071
short checksum_update(char *addr, int count) {
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

