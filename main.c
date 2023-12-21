#include "tp1.h"
#include "tp2.h"

int main()
{

    printf("\n\n***********************************  TP 1 ******************************************************\n\n");
    printf("------------------------Exercice 1----------------------------------------------------------\n\n");
    pingHote_Exo1();
    printf("\n------------------------Exercice 2----------------------------------------------------------\n\n");
    calculPourcentagePacket_Exo2();
    printf("\n------------------------Exercice 3----------------------------------------------------------\n\n");
    lectureFichierIp_Exo3();
    printf("\n\n\n\n\n***********************************  TP 2 ******************************************************\n\n");
    struct iphdr ip_header;
    struct icmphdr icmp_header;
    header_ip_icmp headers;
    char ip_packet[100]; // Taille du paquet IP 
    char icmp_packet[50]; // Taille du paquet ICMP 
    printf("------------------------Exercice 4----------------------------------------------------------\n\n");
    char buffer[100];
    printf("Saisissez un une phrase que vous voullez afficher en hexadecimal:\n");
    fgets(buffer,sizeof(buffer),stdin);printf("\n\n");
    fgets(buffer,sizeof(buffer),stdin);printf("\n\n");
    display(buffer,strlen(buffer));
    printf("\n\nTapez quelque chose et cliquer ensuite sur Entrez pour continuer :\n\n");
    scanf("%s",buffer);printf("\n\n");
    //------------------------Exercice 8 et 9----------------------------------------------
    //Remplissage des structures iphdr et icmphdr Mise en jour de la somme de controle de IP et ICmP
    printf("\n\n------------------------Exercice 8 et 9----------------------------------------------------------\n\n");
    printf("Remplissage des structures iphdr et icmphdr et Mise en jour de la somme de controle de IP et ICMP\n\n");

    icmp_header = fillingStructIcmphdr(12,0);
    uint16_t to_len= sizeof(headers.ip_header)+sizeof(headers.icmp_header);
    ip_header = fillingStructIphdr(to_len,0,0,100,IPPROTO_ICMP,inet_addr("192.168.1.1"),inet_addr("192.168.1.2"));
    headers = fillingIpIcmpHraderAndUpdateCheckSumIcmp(ip_packet,icmp_packet,ip_header,icmp_header);
    printf("La somme de controle de ICMP est : 0x%04X\n",headers.icmp_header.checksum);
    printf("La somme de controle de IP  est  : 0x%04X\n",headers.ip_header.check);
    //------------------------Exercice 10 et 11----------------------------------------------
    printf("------------------------Exercice 10 et 11----------------------------------------------------------\n");
    printf("\n\nVerification du calcul de la somme de controle de IP et ICMP\n");
    icmp_header = fillingStructIcmphdr(0x5678,1);
    to_len= sizeof(headers.ip_header)+sizeof(headers.icmp_header);
    ip_header = fillingStructIphdr(to_len,0x1234,0,100,IPPROTO_ICMP,inet_addr("192.168.0.1"),inet_addr("192.168.0.2"));
    headers = checkingBeforeAndAfterUpdateCheckSumIcmp(ip_packet,icmp_packet,ip_header,icmp_header);
    
    printf("\n\n------------------------Exercice 12 et 13----------------------------------------------------------\n");
    printf("Creation du socket et envoi du packet a travers le socket\n");
    creationSocketToSendPacket(headers.ip_header,ip_packet);
    



    return 0;
}
