# ftpclient

File Transfer Protocol (FTP) is a protocol for client-server file transfer.

Implementation details are found in RFC 959.

My basic implementation follows the minimum required implementation in RFC 959:

- TYPE: ASCII Non-print
- MODE: Stream
- STRUCTURE: File, Record
- COMMANDS:
  - USER, QUIT, PORT
  - TYPE, MODE, STRU, for the default values
  - RETR, STOR, NOOP
- Default values for transfer parameters: TYPE (ASCII Non-print), MODE (Stream), STRU (File)
