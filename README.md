# wshk
mini network analyzer

## Note on sockets (regular and raw)

For regular socket programming, data is only sent and revd at the app layer. Each program can only recv data at the bound port, and the received data usually includes only app-layer data.
These sockets like `STREAM` and `DATAGRAM` recv data from `transport layer` that contains no `headers` but only the `payload`; no info about `source IP and MAC address`. Therefore, communicating applications (same machine or diff) are only exchanging data.

In some cases, we need to perform low-level ops e.g listening to all data sent & received by the native machine, modifying headers etc. With `raw sockets`, we can capture all `IP packets` sent to the local machine (inclusing IP headers and TCP/UDP/ICMP headers) and all frames received (including DATA LINK PROTOCOL headers). A common socket cannot process network packets such as ICMP and IGMP, but SOCK_RAW can. With raw sockets, we can construct custom IP headers.

Raw sockets allow apps directly access lower level protocols, which means a raw socket receives un-extracted packets(the process is as following graph). There is no need to provide the port and IP address to a raw socket, unlike in the case of stream and datagram sockets.


