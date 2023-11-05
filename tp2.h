#ifndef __include_tp2_h__
#define __include_tp2_h__
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>

void display(char *buffer, int length);
struct iphdr *fillingStructIphdr(uint16_t tot_len, uint16_t id, uint16_t frag_off,
               uint8_t ttl, uint8_t protocol, uint32_t saddr, uint32_t daddr);
struct icmphdr *fillingStructIcmphdr(uint16_t id, uint16_t sequence) ;
short checksum(char *addr, int count) ;
short checksum_update(char *addr, int count) ;
#endif /* #ifndef __include_fichier_h__ */