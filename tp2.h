#ifndef __include_tp2_h__
#define __include_tp2_h__
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <stdint.h>
#include <unistd.h>
#include <arpa/inet.h>
typedef struct {
    struct iphdr ip_header;
    struct icmphdr icmp_header;
}header_ip_icmp;

void display(char *buffer, int length);
struct iphdr fillingStructIphdr(uint16_t tot_len, uint16_t id, uint16_t frag_off,
               uint8_t ttl, uint8_t protocol, uint32_t saddr, uint32_t daddr);
struct icmphdr fillingStructIcmphdr(uint16_t id, uint16_t sequence) ;
short checksum(char *addr, int count) ;
header_ip_icmp fillingIpIcmpHraderAndUpdateCheckSumIcmp(char *ip_packet,char *icmp_packet,struct iphdr ip_header,struct icmphdr icmp_header);
header_ip_icmp checkingBeforeAndAfterUpdateCheckSumIcmp(char *ip_packet,char *icmp_packet,struct iphdr ip_header,struct icmphdr icmp_header);
void creationSocketToSendPacket(struct iphdr ip_header,char *ip_packet);
#endif /* #ifndef __include_fichier_h__ */