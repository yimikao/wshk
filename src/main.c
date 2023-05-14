#include "ch.h"
#include "wshk.h"


int main()
{
    int sockfd;
    char global_buffer[BUFFSIZE];
    size_t revd_bytes;

    memset(global_buffer, 0, BUFFSIZE);

    // individual headers
    ethernethd *ehd;
    iphd *ihd;
    transporthd *thd;
    char *data;


    sockfd = get_rawsock_or_die(0);
    if (sockfd < 0) {
        // fprintf(stderr, "socket create", strerr(errno));
        perror("socket create\n");
    }

    revd_bytes = packet_read(sockfd, global_buffer);
    if (revd_bytes < 0) {
        perror("socket read");
    }

    printf("read total %d bytes\n", revd_bytes);

    // parse individual headers
    ethernet_header_parse(global_buffer, ehd);
    ip_header_parse(global_buffer, ihd);
    transport_header_parse(global_buffer, thd);
    app_header_parse(global_buffer, data);

    print_headers(ehd, ihd, thd, data);
    
}