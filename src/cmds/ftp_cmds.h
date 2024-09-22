#ifndef FTPCLIENT_FTP_CMDS_H
#define FTPCLIENT_FTP_CMDS_H

static void make_ftp_cmd(char *s, char *cmd, char *arg);
static void send_ftp_cmd(int sd, char *cmd, char *arg);
void send_ftp_cmd_user(int sd, char *username);

#endif //FTPCLIENT_FTP_CMDS_H
