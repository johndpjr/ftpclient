#ifndef FTPCLIENT_REPL_H
#define FTPCLIENT_REPL_H

static void error(char *msg);
static int parse_resp(int sd, char *resp);
// Prints prompt and then reads user input from stdin into buf
static void prompt(char *prompt, char *buf);
// Begins the REPL flow
void start_repl(int sd);

#endif //FTPCLIENT_REPL_H
