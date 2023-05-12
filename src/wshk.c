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