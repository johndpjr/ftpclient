#ifndef FTPCLIENT_FTP_H
#define FTPCLIENT_FTP_H

#define MAX_ARG_SIZE 512

#define FTP_REPLY_110 100
#define FTP_REPLY_120 120
#define FTP_REPLY_125 125
#define FTP_REPLY_150 150

#define FTP_REPLY_200 200
#define FTP_REPLY_202 202
#define FTP_REPLY_211 211
#define FTP_REPLY_212 212
#define FTP_REPLY_213 213
#define FTP_REPLY_214 214
#define FTP_REPLY_215 215
#define FTP_REPLY_220 220
#define FTP_REPLY_221 221
#define FTP_REPLY_225 225
#define FTP_REPLY_225 225
#define FTP_REPLY_227 227
#define FTP_REPLY_230 230
#define FTP_REPLY_250 250
#define FTP_REPLY_257 257

#define FTP_REPLY_331 331
#define FTP_REPLY_332 332
#define FTP_REPLY_350 350

#define FTP_REPLY_421 421
#define FTP_REPLY_425 425
#define FTP_REPLY_426 426
#define FTP_REPLY_450 450
#define FTP_REPLY_451 451
#define FTP_REPLY_452 452

typedef enum FTP_Command {
    USER,
    QUIT,
    PORT,
    TYPE,
    MODE,
    STRU,
    RETR,
    STOR,
    NOOP,
} FTP_Command;

typedef enum FTP_Outcome {
    Success,
    Failure,
    Error,
} FTP_Outcome;

typedef enum ClientAction {
    ReadNextCmd,
    QuitProgram,
} ClientAction;

#endif //FTPCLIENT_FTP_H
