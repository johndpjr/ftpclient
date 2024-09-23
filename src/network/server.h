#ifndef FTPCLIENT_SERVER_H
#define FTPCLIENT_SERVER_H

#include <unistd.h>

void server_send_cmd(int sd, char *cmd, size_t cmdsize);
size_t server_recv_resp(int sd, char *respbuf, size_t max_respsize);

#endif //FTPCLIENT_SERVER_H
