#ifndef FTPCLIENT_CLIENT_CMDS_H
#define FTPCLIENT_CLIENT_CMDS_H

enum ClientCommand {
    Cd,
    Exit,
    Quit,
    Get,
    Ls,
    Pwd,
    Help,
    Rhelp,
    Size,
    N_CCMDS,
    INVALID_CCMD,
};

// NOTE: this must match the order of commands in enum ClientCommand
static const char *CCMDS[] = {
    "cd",
    "exit",
    "quit",
    "get",
    "ls",
    "pwd",
    "help",
    "rhelp",
    "size",
};

struct ClientInput {
    enum ClientCommand ccmd;
    char *arg;
};

// Returns the client command enum from the string cmd
static enum ClientCommand match_client_cmd(char *cmd);
// Returns the client input, with the command and arguments
struct ClientInput parse_client_input(char *input);
// Dispatches the client command to the corresponding command function
void handle_client_cmd(int sd, struct ClientInput);

void client_cmd_cd(int sd, char *arg);
void client_cmd_quit(int sd);
void client_cmd_get(int sd, char *arg);
void client_cmd_ls(int sd, char *arg);
void client_cmd_pwd(int sd);
void client_cmd_help(int sd);
void client_cmd_rhelp(int sd);
void client_cmd_size(int sd, char *arg);

#endif //FTPCLIENT_CLIENT_CMDS_H
