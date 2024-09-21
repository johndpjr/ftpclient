#include "repl.h"
#include "sockets.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define REPL_RESP_BUFSIZE (4096 + 1)
#define REPL_CMD_BUFSIZE 512

enum ResponseError {
    ErrInvalidCode,
    ErrNoSpaceOrHyphen,
};

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

size_t read_cmd(char *buf) {
    size_t bytes_read = read(STDIN_FILENO, buf, REPL_CMD_BUFSIZE - 1);
    buf[bytes_read] = '\0';
    return bytes_read;
}

size_t send_cmd(int sd, char *cmd, size_t cmdsize) {
    return socket_send(sd, cmd, cmdsize);
}

void start_repl(int sd) {
    char *respbuf = malloc(REPL_RESP_BUFSIZE);
    if (respbuf == NULL) {
        printf("ERROR: malloc failed\n");
        exit(-1);
    }
    char cmdbuf[REPL_CMD_BUFSIZE];
    do {
        // Interpret server response
        int code = parse_resp(sd, respbuf);
        if (code <= 0) {
            printf("ERROR: %s\n", respbuf);
            exit(-1);
        }
        // Print server response
        printf("%s", respbuf);
        // Handle server response
        // Read in user command
        size_t cmdsize = read_cmd(cmdbuf);
        if (send_cmd(sd, cmdbuf, cmdsize) == -1) {
            printf("ERROR: send failed\n");
            exit(-1);
        }
    } while (1);
}
