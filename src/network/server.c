#include "server.h"
#include "sockets.h"

void server_send_cmd(int sd, char *cmd, size_t cmdsize) {
    socket_send(sd, cmd, cmdsize);
}

void server_recv_resp(int sd, char *respbuf, size_t max_respsize) {
    return;
}
