#include "wshk.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <net/if_dl.h>
#include <stdlib.h>
#include <stdio.h>


int rawsocket_create_or_die(int protocol)
{
    int sockfd;
    // or htons(ETH_P_ALL)
    sockfd = socket(PF_NDRV, SOCK_RAW, IPPROTO_RAW);

    if (sockfd < 0) {
        fprintf(stderr, "socket create error\n");
        return -1;
    }
    return sockfd;
}

int packet_recv(int sockfd)
{
    unsigned char *buffer;
    // source info
    struct sockaddr saddr;

    buffer = (unsigned char *) malloc(65536);
    int buf_size = sizeof(buffer);
    memset(buffer, 0, buf_size);
    int saddr_len = sizeof (saddr);

    // copy network packet
    int bytes_recv = recvfrom(sockfd, buffer, 0, buf_size, &saddr, (socklen_t *)&saddr_len);
    if (bytes_recv < 0) {
        fprintf(stderr, "packet receive error\n");
        return -1;
    }
    return 0;
}

//