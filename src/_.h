// int rawsocket_create_or_die(int protocol)
// {
//     int sockfd;
//     // or htons(ETH_P_ALL)
//     sockfd = socket(PF_NDRV, SOCK_RAW, IPPROTO_TCP);

//     if (sockfd < 0) {
//         fprintf(stderr, "socket create error\n");
//         return -1;
//     }
//     return sockfd;
// }

// int packet_recv(int sockfd)
// {
//     struct ether_header a;
//     unsigned char *buffer;
//     // source info
//     struct sockaddr saddr;

//     buffer = (unsigned char *) malloc(65536);
//     int buf_size = sizeof(buffer);
//     memset(buffer, 0, buf_size);
//     int saddr_len = sizeof (saddr);

//     // copy network packet
//     int bytes_recv = recvfrom(sockfd, buffer, 0, buf_size, &saddr, (socklen_t *)&saddr_len);
//     if (bytes_recv < 0) {
//         fprintf(stderr, "packet receive error\n");
//         return -1;
//     }
//     return 0;
// }


// void ethheader_extract(struct ethhdr ethheader)
// {

// }