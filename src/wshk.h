#ifndef WSHK_H
#define WSHK_H


// create raw socket
int rawsock_create(int protocol);

// set options on the socket
void setrawsockopt();


// get address details of network interface for packet config
void config_fetch();

// receive packets (sniffing)
int packet_recv();


#endif