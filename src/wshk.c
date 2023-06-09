#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
// #include <net/ethernet.h>
#include <errno.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "wshk.h"

int get_rawsock_or_die(int protocol)
{
    // struct addrinfo hints, *res;
    int sckfd;
    sckfd = socket(PF_NDRV, SOCK_RAW, IPPROTO_RAW);
    if(sckfd < 0)
    {
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
        return -1;
    }
    return bytes_recv;
}

void ethernet_header_parse(char *buffer, ethernethd *ehd)
{
    ehd = (ethernethd*) buffer;
}


void ip_header_parse(char buffer[BUFFSIZE], iphd *ihd)
{
    ihd = (iphd*) (buffer + sizeof(ethernethd));
}

void transport_header_parse(char buffer[BUFFSIZE], transporthd *thd)
{
    // The size of the IP header varies from 20 bytes to 60 bytes.
    // We can calculate this from the IP header field or IHL. IHL means
    // Internet Header Length (IHL), which is the number of 32-bit words in the header.
    // So we have to multiply the IHL by 4 to get the size of the header in bytes
    iphd *ihd = (iphd*) (buffer + sizeof(ethernethd));
    size_t iphd_len = ihd->ihd.ip_hl * 4;
    thd = (transporthd*) (buffer + sizeof(ethernethd) + iphd_len);
}

void app_header_parse(char buffer[BUFFSIZE], char *data)
{
    iphd *ih = (iphd*) (buffer + sizeof(ethernethd));
    size_t ihlen = ih->ihd.ip_hl * 4;
    transporthd *th = (transporthd*) (buffer + sizeof(ethernethd) + ihlen);
    size_t thlen = sizeof(th);
    data = buffer + thlen;
}

void print_headers(ethernethd *ehd, iphd *ihd, transporthd *thd, char *data)
{
    printf("############################################\n");
    printf("ETHERNET HEADER\n\n");
    printf(
        "Source Addr: %s\n"
        "Destination Addr: %s\n"
        "Protocol: %s\n"
        "############################################\n",

        ehd->ehd.ether_shost,
        ehd->ehd.ether_dhost,
        ehd->ehd.ether_type
    );

    printf("IP HEADER\n\n");
    printf(
        "Source IP: %s\n"
        "Destination IP: %s\n"
        "Protocol: %s\n"
        "############################################\n",

        inet_ntoa(ihd->ihd.ip_src),
        inet_ntoa(ihd->ihd.ip_dst),
        ihd->ihd.ip_p
    );
}

int packet_http_data_parse(char[BUFFSIZE], request *, response *)
{
    return 0;
}
