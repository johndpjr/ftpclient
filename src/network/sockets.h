#ifndef FTPCLIENT_SOCKETS_H
#define FTPCLIENT_SOCKETS_H

#include <unistd.h>
#include <netinet/in.h>

#define IPADDR_STRLEN 16
#define FTP_CONNECTION_PORT 21
#define FTP_DATA_PORT 20

void ip_binary_to_text(struct sockaddr_in *serveraddr, char *addrstr);
int socket_make();
int resolve_server(const char *server, struct sockaddr_in *serveraddr, int port);
int socket_connect(int sd, struct sockaddr_in *serveraddr);
size_t socket_send(int sd, char *sbuf, size_t n);
size_t socket_recv(int sd, char *buf, size_t n);

#endif //FTPCLIENT_SOCKETS_H
