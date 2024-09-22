#ifndef FTPCLIENT_REPL_H
#define FTPCLIENT_REPL_H

#include <unistd.h>

#include "ftp.h"

static int parse_resp(int sd, char *resp);
static int get_first_digit(int num);
static ClientAction handle_resp(int code);
static size_t read_cmd(char *buf);
void start_repl(int sd);

#endif //FTPCLIENT_REPL_H
