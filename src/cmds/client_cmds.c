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
        // Remove newline '\n' after arg
        char *newline = strchr(clientin.arg, '\n');
        if (newline != NULL) *newline = '\0';
    }
    clientin.ccmd = match_client_cmd(input);
    return clientin;
}

void handle_client_cmd(int sd, struct ClientInput clientin) {
    switch (clientin.ccmd) {
        case Cd:
            client_cmd_cd(sd, clientin.arg);
            break;
        case Exit:
        case Quit:
            client_cmd_quit(sd);
            break;
        case Get:
            client_cmd_get(sd, clientin.arg);
            break;
        case Ls:
            client_cmd_ls(sd, clientin.arg);
            break;
        case Pwd:
            client_cmd_pwd(sd);
            break;
        case Help:
            client_cmd_help(sd);
            break;
        case Rhelp:
            client_cmd_rhelp(sd);
            break;
        case Size:
            client_cmd_size(sd, clientin.arg);
            break;
    }
}

void client_cmd_cd(int sd, char *arg) {
}

void client_cmd_quit(int sd) {
    send_ftp_cmd_quit(sd);
}

void client_cmd_get(int sd, char *arg) {
}

void client_cmd_ls(int sd, char *arg) {
}

void client_cmd_pwd(int sd) {
}

void client_cmd_help(int sd) {
}

void client_cmd_rhelp(int sd) {
}

void client_cmd_size(int sd, char *arg) {
}
