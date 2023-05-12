#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
// #include <net/ethernet.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "wshk.h"

int get_rawsock_or_die(int protocol)
{
    // struct addrinfo hints, *res;
    int sckfd;
    sckfd = socket(PF_NDRV, SOCK_RAW, IPPROTO_RAW);
    if(sckfd < 0)
    {
        // fprintf(stderr, "socket create", strerr(errno));
        perror("socket create");
        return -1;
    }
    return sckfd;
}

int packet_read(int fd, char buffer[BUFFSIZE])
{
    size_t bytes_read, bytes_recv;
    // if socket is is not connection-oriented, source info gets filled in 
    struct sockaddr saddr;
    size_t saddr_len = sizeof (saddr); 

    bytes_recv = recvfrom(fd, buffer, BUFFSIZE, 0, &saddr, (socklen_t*)&saddr_len);
    if (bytes_recv < 0) {
        perror("socket read");
        return -1;
    }
    return bytes_recv;
}

void ethernet_header_parse(char *buffer, ethernet_hdr *e_hdr)
{
    e_hdr = (ethernet_hdr*) buffer;
}


void ip_header_read(char buffer[BUFFSIZE], ip_hdr *i_hdr)
{
    i_hdr = (ip_hdr*) (buffer + sizeof(ethernet_hdr));
}

void transport_header_read(char buffer[BUFFSIZE], transport_hdr *t_hdr)
{
    // The size of the IP header varies from 20 bytes to 60 bytes.
    // We can calculate this from the IP header field or IHL. IHL means
    // Internet Header Length (IHL), which is the number of 32-bit words in the header.
    // So we have to multiply the IHL by 4 to get the size of the header in bytes
    ip_hdr *i_hdr = (ip_hdr*) (buffer + sizeof(ethernet_hdr));
    size_t iphdr_len = i_hdr->i_hdr.ip_hl * 4;
    t_hdr = (transport_hdr*) (buffer + sizeof(ethernet_hdr) + iphdr_len);
}