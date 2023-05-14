#ifndef WSHK_H
#define WSHK_H

// netinet headers are mostly the alternative to the <linux/> variants
#include <net/ethernet.h>
// #include <netinet/if_ether.h>
#include <netinet/ip.h>
// #include <netinet/ip_icmp.h>
#include <netinet/tcp.h>

#define BUFFSIZE 1024

typedef struct ethernethd
{
    struct ether_header ehd;
} ethernethd;

typedef struct iphd
{
    struct ip ihd;
} iphd;

typedef struct transporthd
{
    struct tcphdr thd;
} transporthd;

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

typedef int (*http_handler_ptr)(request*, response*);

int get_rawsock_or_die(int);

void set_rawsock_opt();

int packet_read(int, char [BUFFSIZE]);

void ethernet_header_parse(char [BUFFSIZE], ethernethd*);

void ip_header_parse(char [BUFFSIZE], iphd*);

void transport_header_parse(char [BUFFSIZE], transporthd*);

void app_header_parse(char [BUFFSIZE], char*);

void print_headers(ethernethd*, iphd*, transporthd*, char*);

int packet_http_data_parse(char [BUFFSIZE], request*, response*);

int http_handler(request*, response*);


#endif