#include "ftp_cmds.h"
#include "../network/server.h"
#include "../defs.h"

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

void send_ftp_cmd_cwd(int sd, char *pathname) {
    send_ftp_cmd(sd, "CWD", pathname);
}

void send_ftp_cmd_quit(int sd) {
    send_ftp_cmd(sd, "QUIT", NULL);
}

void send_ftp_cmd_type(int sd, char *typecode) {
    send_ftp_cmd(sd, "TYPE", typecode);
}

void send_ftp_cmd_size(int sd, char *pathname) {
    send_ftp_cmd(sd, "SIZE", pathname);
}

void send_ftp_cmd_pasv(int sd) {
    send_ftp_cmd(sd, "PASV", NULL);
}

void send_ftp_cmd_retr(int sd, char *pathname) {
    send_ftp_cmd(sd, "RETR", pathname);
}

void send_ftp_cmd_list(int sd, char *pathname) {
    send_ftp_cmd(sd, "LIST", pathname);
}

void send_ftp_cmd_pwd(int sd) {
    send_ftp_cmd(sd, "PWD", NULL);
}

void send_ftp_cmd_help(int sd, char *cmdname) {
    send_ftp_cmd(sd, "HELP", cmdname);
}
