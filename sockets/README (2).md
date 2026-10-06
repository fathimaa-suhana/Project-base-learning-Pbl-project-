# Sockets

## What is this?
A socket is a doorway a program uses to send and receive data. Unlike a pipe, a socket is **two-way**: both processes can send and receive on the same connection.

We use a **Unix domain socket** (`AF_UNIX`), which works between processes on the same machine and shows up as a file (`mysock`), similar to a FIFO.

## What's in this folder
- `server.c` - creates the socket, waits for a client, reads its message and replies
- `client.c` - connects to the server, sends a message and reads the reply

## How to run
Terminal 1:
```
gcc server.c -o server
./server
```
Terminal 2:
```
gcc client.c -o client
./client
```

## Flow
```
Server: socket() -> bind() -> listen() -> accept() -> read/write -> close()
Client: socket() -> connect() -> write/read -> close()
```

## Notes
- Two-way communication on one connection (pipes need two for that)
- Server can accept many clients (with threads or select)
- Good fit for our simulator: UI, Core and Logger can talk over one socket path

## Output
Server (Terminal 1):

![Server output](screenshots/server_output.png)

Client (Terminal 2):

![Client output](screenshots/client_output.png)
