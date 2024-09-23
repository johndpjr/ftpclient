#include "ftp_cmds.h"
#include "../network/server.h"
#include "../network/sockets.h"
#include "../defs.h"

#include <ctype.h>
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

int recv_ftp_cmd_pasv(int sd, char *recvbuf) {
    size_t bytes_read = server_recv_resp(sd, recvbuf, FTP_RESP_MAXSIZE);
    recvbuf[bytes_read] = '\0';
    // Look for first digit after initial space
    char *cursor = strchr(recvbuf, ' ') + 1;
    int h1, h2, h3, h4, p1, p2;
    int matches = 0;
    while (*cursor != '\0') {
        if (isdigit(*cursor)) {
            matches = sscanf(cursor, "%d,%d,%d,%d,%d,%d", &h1, &h2, &h3, &h4, &p1, &p2);
            break;
        }
        ++cursor;
    }
    if (matches != 6)
        return -1;

    char addrstr[IPADDR_STRLEN];
    sprintf(addrstr, "%d.%d.%d.%d", h1, h2, h3, h4);
    struct sockaddr_in serveraddr;
    int port = p1 * 256 + p2;
    resolve_server(addrstr, &serveraddr, port);
    int data_transfer_sd = socket_make();
    return socket_connect(data_transfer_sd, &serveraddr);
}

void recv_ftp_cmd_retr(int sd, int dt_sd, char *recvbuf, char *pathname) {
//    server_recv_resp(sd, recvbuf, FTP_RESP_MAXSIZE);
    // Create file
    // Receive data from data transfer socket
//    server_recv_resp(data_transfer_sd, )
}
