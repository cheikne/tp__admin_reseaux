#include "tp1.h"
#include "tp2.h"

int main()
{

    // pingHote_Exo1();
    // lectureFichierIp_Exo3();
    // calculPourcentagePacket_Exo2();
    //char buffer[] = "Ceci est un exemple de texte à afficher en hexadécimal.";
    //display(buffer,strlen(buffer));

    struct iphdr ip_header;
    struct icmphdr icmp_header;
    header_ip_icmp headers;
    char ip_packet[100]; // Taille du paquet IP (modifiable selon vos besoins)cv
    char icmp_packet[50]; // Taille du paquet ICMP (modifiable selon vos besoins)cv
    //------------------------Exercice 8 et 9----------------------------------------------
    //Remplissage des structures iphdr et icmphdr Mise en jour de la somme de controle de IP et ICmP
    printf("\n\n------------------------Exercice 8 et 9----------------------------------------------------------\n\n");
    printf("Remplissage des structures iphdr et icmphdr et Mise en jour de la somme de controle de IP et ICMP\n\n");

    icmp_header = fillingStructIcmphdr(12,0);
    uint16_t to_len= sizeof(headers.ip_header)+sizeof(headers.icmp_header);
    ip_header = fillingStructIphdr(to_len,0,0,100,IPPROTO_ICMP,inet_addr("192.168.1.1"),inet_addr("192.168.1.2"));
    headers = fillingIpIcmpHraderAndUpdateCheckSumIcmp(ip_packet,icmp_packet,ip_header,icmp_header);
    printf("La somme de controle est ICMP: 0x%04X\n",headers.icmp_header.checksum);
    printf("La somme de controle est IP: 0x%04X\n",headers.ip_header.check);
    //------------------------Exercice 10 et 11----------------------------------------------
    printf("------------------------Exercice 10----------------------------------------------------------\n");
    printf("\n\nVerification du calcul de la somme de controle de IP et ICMP\n");
    icmp_header = fillingStructIcmphdr(0x5678,1);
    to_len= sizeof(headers.ip_header)+sizeof(headers.icmp_header);
    ip_header = fillingStructIphdr(to_len,0x1234,0,100,IPPROTO_ICMP,inet_addr("192.168.0.1"),inet_addr("192.168.0.2"));
    headers = checkingBeforeAndAfterUpdateCheckSumIcmp(ip_packet,icmp_packet,ip_header,icmp_header);
    
    



    return 0;
}
