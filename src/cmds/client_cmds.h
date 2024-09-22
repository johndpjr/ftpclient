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
    Rmdir,
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
    "rmdir",
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
void handle_client_cmd(struct ClientInput);

void client_cmd_cd(char *arg);
void client_cmd_quit();
void client_cmd_get(char *arg);
void client_cmd_ls(char *arg);
void client_cmd_pwd();
void client_cmd_help();
void client_cmd_rhelp();
void client_cmd_rmdir(char *arg);
void client_cmd_size(char *arg);

#endif //FTPCLIENT_CLIENT_CMDS_H
