# wshk
mini network analyzer

## Note on sockets (regular and raw)

For regular socket programming, data is only sent and revd at the app layer. Each program can only recv data at the bound port, and the received data usually includes only app-layer data.
These sockets like `STREAM` and `DATAGRAM` recv data from `transport layer` that contains no `headers` but only the `payload`; no info about `source IP and MAC address`. Therefore, communicating applications (same machine or diff) are only exchanging data.

In some cases, we need to perform low-level ops e.g listening to all data sent & received by the native machine, modifying headers etc. With `raw sockets`, we can capture all `IP packets` sent to the local machine (inclusing IP headers and TCP/UDP/ICMP headers) and all frames received (including DATA LINK PROTOCOL headers). A common socket cannot process network packets such as ICMP and IGMP, but SOCK_RAW can. With raw sockets, we can construct custom IP headers.

Raw sockets allow apps directly access lower level protocols, which means a raw socket receives un-extracted packets(the process is as following graph). There is no need to provide the port and IP address to a raw socket, unlike in the case of stream and datagram sockets.

raw sockets can be used to receive data packets and send those packets to specific user applications, bypassing the normal TCP/IP protocols.This means packets received at the Ethernet layer will directly pass to the raw socket. Stating it precisely, a raw socket bypasses the normal TCP/IP processing and sends the packets to the specific user application. Other sockets like stream sockets and data gram sockets receive data from the transport layer that contains no headers but only the payload. This means that there is no information about the source IP address and MAC address. If applications running on the same machine or on different machines are communicating, then they are only exchanging data.

## Network packets and packet sniffers

When an application sends data into the network, it is processed by various network layers. Before sending data, it is wrapped in various headers of the network layer. The wrapped form of data, which contains all the information like the source and destination address, is called a network packet. According to Ethernet protocols, there are various types of network packets like Internet Protocol packets, Xerox PUP packets etc. In Linux, we can see all protocols in the if_ether.h header file.

`Ethernet

When we connect to the Internet, we receive network packets, and our machine extracts all network layer headers and sends data to a particular application. For example, when we type www.google.com in our browser, we receive packets sent from Google, and our machine extracts all the headers of the network layer and gives the data to our browser.

```c
#include <sys/socket.h>
#include <sys/types.h>

int socket(int domain, int type, int protocol)
```