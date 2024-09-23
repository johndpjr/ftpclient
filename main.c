#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/network/sockets.h"
#include "src/repl.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: ftpclient <server-or-ip-addr>\n");
        exit(-1);
    }

    char *server = argv[1];
    char addrstr[IPADDR_STRLEN];
    strcpy(addrstr, server);
    struct sockaddr_in serveraddr;

    if (resolve_server(server, &serveraddr, FTP_CONNECTION_PORT) == -1) {
        printf("ERROR: failed to resolve server %s\n", server);
        exit(-1);
    }
    ip_binary_to_text(&serveraddr, addrstr);
    printf("Trying %s...\n", addrstr);

    int sd = socket_make();
    int ret = socket_connect(sd, &serveraddr);
    if (ret != 0) {
        printf("ERROR: socket_connect failed with %d\n", ret);
        exit(-1);
    }
    printf("Connected to %s.\n", server);

    // Start REPL
    start_repl(sd);

    close(sd);

    return 0;
}
