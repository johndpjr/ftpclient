#ifndef FTPCLIENT_CLIENT_CMDS_H
#define FTPCLIENT_CLIENT_CMDS_H

enum ClientAction {
    CA_NextCommand,
    CA_End,
    CA_Parse,
};

enum ClientCommand {
    CCMD_cd,
    CCMD_exit,
    CCMD_quit,
    CCMD_get,
    CCMD_ls,
    CCMD_pwd,
    CCMD_help,
    CCMD_rhelp,
    CCMD_size,
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

// NOTE: this must match the order of commands in enum ClientCommand
static const char *CCMD_HELP[] = {
        "cd\tchange directory",
        "exit\tclose connection and quit program",
        "quit\tclose connection and quit program",
        "get\tdownload file from remote server",
        "ls\tlist files in working directory",
        "pwd\tprint working directory",
        "help\tshow help for a command",
        "rhelp\tshow supported commands from remote server",
        "size\tget the size of a remote file (in bytes)",
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
enum ClientAction handle_client_cmd(int sd, struct ClientInput clientin);

enum ClientAction client_cmd_cd(int sd, char *arg);
enum ClientAction client_cmd_quit(int sd);
enum ClientAction client_cmd_get(int sd, char *arg);
enum ClientAction client_cmd_ls(int sd, char *arg);
enum ClientAction client_cmd_pwd(int sd);
enum ClientAction client_cmd_help(char *arg);
enum ClientAction client_cmd_rhelp(int sd, char *arg);
enum ClientAction client_cmd_size(int sd, char *arg);

#endif //FTPCLIENT_CLIENT_CMDS_H
