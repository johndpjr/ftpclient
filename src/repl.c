#include "repl.h"
#include "network/sockets.h"
#include "cmds/client_cmds.h"
#include "cmds/ftp_cmds.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

enum ResponseError {
    ErrInvalidCode,
    ErrNoSpaceOrHyphen,
};

void error(char *msg) {
    printf("%s\n", msg);
    exit(-1);
}

int parse_resp(int sd, char *resp) {
    // Read first 4 characters of server response
    size_t bytes_recv = socket_recv(sd, resp, 4);

    // Parse the first 3 characters as a 3-digit status out_code
    for (int i = 0; i < 3; ++i) {
        if (!isdigit(resp[i])) {
            sprintf(resp, "Parsing error: 3-digit status code is not formatted correctly\n");
            return -ErrInvalidCode;
        }
    }
    int code;
    sscanf(resp, "%03d", &code);

    // The 4th character must be a space or hyphen
    char c4 = resp[3];
    if (c4 != ' ' && c4 != '-') {
        sprintf(resp, "Parsing error: status code is not followed by a space or hyphen\n");
        return -ErrNoSpaceOrHyphen;
    }

    size_t rc;
    char endstr[5];
    sprintf(endstr, "%d ", code);

    while (bytes_recv < REPL_RESP_BUFSIZE - 1) {
        // Read the remaining bytes
        rc = socket_recv(sd, &resp[bytes_recv], REPL_RESP_BUFSIZE - bytes_recv - 1);
        // Check for end line conditions
        if (c4 == ' ' && strstr(resp, "\r\n") != NULL)
            break;
        if (c4 == '-' && strstr(&resp[bytes_recv - 3], endstr) != NULL)
            break;
        bytes_recv += rc;
    }
    bytes_recv += rc;
    resp[bytes_recv] = '\0';

    return code;
}

void prompt(char *prompt, char *buf) {
    printf("%s", prompt);
    fgets(buf, REPL_CMD_BUFSIZE, stdin);
}

void start_repl(int sd) {
    char *inputbuf = malloc(REPL_CMD_BUFSIZE);
    char *respbuf = malloc(REPL_RESP_BUFSIZE);
    if (inputbuf == NULL || respbuf == NULL)
        error("malloc failed");

    // Initiate login sequence
    prompt("Username: ", inputbuf);
    send_ftp_cmd_user(sd, inputbuf);
    // TODO: validate server response to login seq

    do {
        // Read in client command
        prompt("ftp> ", inputbuf);
        // Parse client command
        struct ClientInput clientin = parse_client_input(inputbuf);
        if (clientin.ccmd == INVALID_CCMD)
            continue;  // invalid command; prompt user again
        // Handle client command
        handle_client_cmd(clientin);
        // Interpret server response
        int code = parse_resp(sd, respbuf);
        if (code <= 0) {
            printf("ERROR: %s\n", respbuf);
            exit(-1);
        }
        // Print server response
        printf("%s", respbuf);
        // Handle server response
    } while (1);
}
