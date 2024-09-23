#ifndef FTPCLIENT_FTP_CMDS_H
#define FTPCLIENT_FTP_CMDS_H

static void make_ftp_cmd(char *s, char *cmd, char *arg);
static void send_ftp_cmd(int sd, char *cmd, char *arg);

/* Send commands */

void send_ftp_cmd_user(int sd, char *username);
void send_ftp_cmd_cwd(int sd, char *pathname);    // cd
void send_ftp_cmd_quit(int sd);                   // exit & quit
void send_ftp_cmd_type(int sd, char *typecode);
void send_ftp_cmd_size(int sd, char *pathname);
void send_ftp_cmd_pasv(int sd);
void send_ftp_cmd_retr(int sd, char *pathname);  // get
void send_ftp_cmd_list(int sd, char *pathname);  // ls
void send_ftp_cmd_pwd(int sd);                   // pwd
void send_ftp_cmd_help(int sd, char *cmdname);   // rhelp

/* Receive commands */

int recv_ftp_cmd_pasv(int sd, char *recvbuf);
void recv_ftp_cmd_retr(int sd, int dt_sd, char *recvbuf, char *pathname);

#endif //FTPCLIENT_FTP_CMDS_H
