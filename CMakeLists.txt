cmake_minimum_required(VERSION 3.29)
project(ftpclient C)

set(CMAKE_C_STANDARD 11)

add_executable(ftpclient main.c
        src/sockets.c
        src/sockets.h
        src/repl.c
        src/repl.h
        src/ftp.c
        src/ftp.h
)
