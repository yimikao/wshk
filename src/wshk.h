#ifndef WSHK_H
#define WSHK_H

// netinet headers are mostly the alternative to the <linux/> variants
#include <net/ethernet.h>
// #include <netinet/if_ether.h>
#include <netinet/ip.h>
// #include <netinet/ip_icmp.h>
#include <netinet/tcp.h>

#define BUFFSIZE 1024

typedef struct ethernet_hdr
{
    struct ether_header e_hdr;
} ethernet_hdr;

typedef struct ip_hdr
{
    struct ip i_hdr;
} ip_hdr;

typedef struct transport_hdr
{
    struct tcphdr t_hdr;
} transport_hdr;

typedef struct request
{
    char *protocol_version;
    char *method;
} request;

typedef struct response
{
    char *protocol_version;
    char *method;
} response;


int get_rawsock_or_die(int);



void set_rawsock_opt();

int packet_read(int, char buffer[BUFFSIZE]);

int ethernet_header_parse(ethernet_hdr);

int ip_header_parse(ip_hdr);

int transport_header_parse(transport_hdr);

int packet_http_data_parse(char buffer[BUFFSIZE], request*, response*);

typedef int (*http_handler_ptr)(request*, response*);

int http_handler(request*, response*);


#endif