#include "client_cmds.h"

#include <stdio.h>
#include <string.h>

#define CMD_SIZE 16

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

void handle_client_cmd(struct ClientInput clientin) {
    switch (clientin.ccmd) {
        case Cd:
            client_cmd_cd(clientin.arg);
            break;
        case Exit:
        case Quit:
            client_cmd_quit();
            break;
        case Get:
            client_cmd_get(clientin.arg);
            break;
        case Ls:
            client_cmd_ls(clientin.arg);
            break;
        case Pwd:
            client_cmd_pwd();
            break;
        case Help:
            client_cmd_help();
            break;
        case Rhelp:
            client_cmd_rhelp();
            break;
        case Rmdir:
            client_cmd_rmdir(clientin.arg);
            break;
        case Size:
            client_cmd_size(clientin.arg);
            break;
    }
}

void client_cmd_cd(char *arg) {
}

void client_cmd_quit() {
}

void client_cmd_get(char *arg) {
}

void client_cmd_ls(char *arg) {
}

void client_cmd_pwd() {
}

void client_cmd_help() {
}

void client_cmd_rhelp() {
}

void client_cmd_rmdir(char *arg) {
}

void client_cmd_size(char *arg) {
}
