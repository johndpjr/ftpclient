#include "ftp_cmds.h"
#include "../repl.h"
#include "../network/server.h"

#include <stdio.h>
#include <string.h>

void make_ftp_cmd(char *s, char *cmd, char *arg) {
    if (arg == NULL)
        sprintf(s, "%s\r\n", cmd);
    else
        sprintf(s, "%s %s\r\n", cmd, arg);
}

void send_ftp_cmd(int sd, char *cmd, char *arg) {
    char cmdbuf[REPL_CMD_BUFSIZE];
    make_ftp_cmd(cmdbuf, cmd, arg);
    server_send_cmd(sd, cmdbuf, strlen(cmdbuf));
}

void send_ftp_cmd_user(int sd, char *username) {
    send_ftp_cmd(sd, "USER", username);
}
