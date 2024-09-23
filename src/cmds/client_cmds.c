#include "client_cmds.h"
#include "ftp_cmds.h"

#include <string.h>

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
    // Parse input
    const char sep = ' ';
    char * const sep_at = strchr(input, sep);
    clientin.arg = NULL;
    if (sep_at != NULL) {
        // Found a space; make two strings
        *sep_at = '\0';
        // arg is found after the first space
        clientin.arg = sep_at + 1;
    }
    // Remove newline '\n' in input
    char *newline = strchr(input, '\n');
    if (newline != NULL) *newline = '\0';
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
            return client_cmd_help(sd, NULL);
        case CCMD_rhelp:
            return client_cmd_rhelp(sd, NULL);
        case CCMD_size:
            return client_cmd_size(sd, clientin.arg);
    }
}

enum ClientAction client_cmd_cd(int sd, char *arg) {

    return CA_Continue;
}

enum ClientAction client_cmd_quit(int sd) {
    send_ftp_cmd_quit(sd);
    return CA_End;
}

enum ClientAction client_cmd_get(int sd, char *arg) {
    return CA_Continue;
}

enum ClientAction client_cmd_ls(int sd, char *arg) {
    return CA_Continue;
}

enum ClientAction client_cmd_pwd(int sd) {
    send_ftp_cmd_pwd(sd);
    return CA_Continue;
}

enum ClientAction client_cmd_help(int sd, char *cmdname) {
    send_ftp_cmd_help(sd, cmdname);
    return CA_Continue;
}

enum ClientAction client_cmd_rhelp(int sd, char *cmdname) {
    send_ftp_cmd_help(sd, cmdname);
    return CA_Continue;
}

enum ClientAction client_cmd_size(int sd, char *arg) {
    return CA_Continue;
}
