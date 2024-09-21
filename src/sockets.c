#include "sockets.h"

#include <sys/select.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

int socket_make() {
    return socket(AF_INET, SOCK_STREAM, 0);
}

int resolve_server(const char *server, struct sockaddr_in *serveraddr, char *addrstr) {
    memset(serveraddr, 0, sizeof(*serveraddr));
    serveraddr->sin_family = AF_INET;
    serveraddr->sin_port = htons(FTP_CONNECTION_PORT);
    serveraddr->sin_addr.s_addr = inet_addr(server);

    struct hostent *hostp;
    if (serveraddr->sin_addr.s_addr == (unsigned long)INADDR_NONE) {
        // Perform a DNS lookup
        hostp = gethostbyname(server);
        if (hostp == (struct hostent *)NULL) {
            return -1;
        }

        memcpy(&serveraddr->sin_addr, hostp->h_addr, sizeof(serveraddr->sin_addr));
        inet_ntop(AF_INET, &(serveraddr->sin_addr), addrstr, INET_ADDRSTRLEN);
    }
    return 0;
}

int socket_connect(int sd, struct sockaddr_in *serveraddr) {
    return connect(sd, (struct sockaddr *)serveraddr, sizeof(*serveraddr));
}

size_t socket_send(int sd, char *sbuf, size_t n) {
    return send(sd, sbuf, n, 0);
}

size_t socket_recv(int sd, char *buf, size_t n) {
    return recv(sd, buf, n, 0);
}
