cmake_minimum_required(VERSION 3.29)
project(ftpclient C)

set(CMAKE_C_STANDARD 11)

add_executable(ftpclient main.c
        src/network/sockets.c
        src/network/sockets.h
        src/repl.c
        src/repl.h
        src/cmds/client_cmds.c
        src/cmds/client_cmds.h
        src/cmds/ftp_cmds.c
        src/cmds/ftp_cmds.h
        src/network/server.c
        src/network/server.h
)
