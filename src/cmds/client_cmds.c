#include "client_cmds.h"
#include "../defs.h"
#include "ftp_cmds.h"
#include "../network/server.h"

#include <string.h>
#include <malloc.h>

enum ClientCommand match_client_cmd(char *cmd) {
    for (int ccmd = 0; ccmd < N_CCMDS; ++ccmd) {
        if (strcmp(cmd, CCMDS[ccmd]) == 0)
            return ccmd;
    }
    // No matching command was found; return error
    return INVALID_CCMD;
}

struct ClientInput parse_client_input(char *input) {
    struct ClientInput clientin;
    clientin.arg = NULL;
    // Parse input
    const char sep = ' ';
    char * const sep_at = strchr(input, sep);
    // Remove newline '\n' in input
    char *newline = strchr(input, '\n');
    if (newline != NULL) *newline = '\0';
    if (sep_at != NULL) {
        // Found a space; make two strings
        *sep_at = '\0';
        // arg is found after the first space
        clientin.arg = sep_at + 1;
    }
    clientin.ccmd = match_client_cmd(input);
    return clientin;
}

enum ClientAction handle_client_cmd(int sd, struct ClientInput clientin) {
    switch (clientin.ccmd) {
        case CCMD_cd:
            return client_cmd_cd(sd, clientin.arg);
        case CCMD_exit:
        case CCMD_quit:
            return client_cmd_quit(sd);
        case CCMD_get:
            return client_cmd_get(sd, clientin.arg);
        case CCMD_ls:
            return client_cmd_ls(sd, clientin.arg);
        case CCMD_pwd:
            return client_cmd_pwd(sd);
        case CCMD_help:
            return client_cmd_help(clientin.arg);
        case CCMD_rhelp:
            return client_cmd_rhelp(sd, clientin.arg);
        case CCMD_size:
            return client_cmd_size(sd, clientin.arg);
    }
}

enum ClientAction client_cmd_cd(int sd, char *arg) {
    send_ftp_cmd_cwd(sd, arg);
    return CA_Parse;
}

enum ClientAction client_cmd_quit(int sd) {
    send_ftp_cmd_quit(sd);
    return CA_End;
}

enum ClientAction client_cmd_get(int sd, char *arg) {
    char *recvbuf = malloc(FTP_RESP_MAXSIZE);
    // Change TYPE to Image
    send_ftp_cmd_type(sd, "I");
    server_recv_resp(sd, recvbuf, FTP_RESP_MAXSIZE);
    // Invoke SIZE to get filesize
    send_ftp_cmd_size(sd, arg);
    int filesize = recv_ftp_cmd_size(sd, recvbuf);
    // Enter PASV mode
    send_ftp_cmd_pasv(sd);
    // Get socket connection from PASV response
    int data_transfer_sd = recv_ftp_cmd_pasv(sd, recvbuf);
    // Start file transfer via RETR
    send_ftp_cmd_retr(sd, arg);
    recv_ftp_cmd_retr(sd, data_transfer_sd, recvbuf, arg, filesize);
    // Clean up resources
    free(recvbuf);
    close(data_transfer_sd);
    return CA_NextCommand;
}

enum ClientAction client_cmd_ls(int sd, char *arg) {
    return CA_NextCommand;
}

enum ClientAction client_cmd_pwd(int sd) {
    send_ftp_cmd_pwd(sd);
    return CA_Parse;
}

enum ClientAction client_cmd_help(char *arg) {
    if (arg == NULL) {
        printf("Commands are:\n");
        int i = 0;
        for (i = 0; i < N_CCMDS; ++i) {
            printf("%s", CCMDS[i]);
            if (i % 4 == 0 && i != 0) printf("\n");
            else printf("\t");
        }
    } else {
        int c;
        for (c = 0; c < N_CCMDS; ++c) {
            if (strcmp(CCMDS[c], arg) == 0) {
                printf("%s\n", CCMD_HELP[c]);
                goto out;
            }
        }
        // Unrecognized command
        printf("Invalid command '%s'\n", arg);
    }

out:
    return CA_NextCommand;
}

enum ClientAction client_cmd_rhelp(int sd, char *arg) {
    send_ftp_cmd_help(sd, arg);
    return CA_NextCommand;
}

enum ClientAction client_cmd_size(int sd, char *arg) {
    send_ftp_cmd_size(sd, arg);
    return CA_NextCommand;
}
