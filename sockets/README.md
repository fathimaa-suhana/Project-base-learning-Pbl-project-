# Sockets

> **Phase 1 – Topic Study: Sockets**

## What is a Socket?
A **socket** is one endpoint of a two-way communication link between two programs. A program uses it to send and receive data, on the same machine or over a network.

**Analogy: a phone call 📞** — the socket is the phone, the address is the phone number, `connect()` is dialing, `accept()` is picking up, and `close()` is hanging up.

## Key Concepts
- **IP address:** identifies a device (e.g. `192.168.1.10`). `127.0.0.1` means "this computer".
- **Port:** identifies a program on that device (0–65535). Use ports above `1024` for your own programs.
- **Socket address = IP + port** (e.g. `127.0.0.1:5000`).
- **Client–server model:** the server waits for connections, the client starts them.

## Types of Sockets
| Type | Protocol | Behaviour |
|---|---|---|
| `SOCK_STREAM` | TCP | Reliable, ordered, connection-based |
| `SOCK_DGRAM` | UDP | Fast, no connection, delivery not guaranteed |

Address families: `AF_INET` (IPv4 network) and `AF_UNIX` (same machine, uses a file path).

## TCP vs UDP
| | TCP | UDP |
|---|---|---|
| Connection | Yes (handshake) | No |
| Reliable and ordered | Yes | No |
| Speed | Slower | Faster |
| Used for | Web, email, file transfer | Video calls, games, DNS |

Use **TCP** when correctness matters, **UDP** when speed matters more.

## How a TCP Connection Works
```
Server: socket() → bind() → listen() → accept() → recv()/send() → close()
Client: socket() → connect() → send()/recv() → close()
```
The server keeps one listening socket and gets a **new** socket from `accept()` for each client.

## Syntax (Python)
```python
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # create TCP socket
s.bind(("127.0.0.1", 5000))     # server: attach to address
s.listen(5)                     # server: wait for clients
conn, addr = s.accept()         # server: accept a client
s.connect(("127.0.0.1", 5000))  # client: connect to server
conn.sendall(b"hello")          # send bytes
data = conn.recv(1024)          # receive up to 1024 bytes
```
Sockets carry **bytes**, so use `.encode()` and `.decode()` for strings.

## Multiple Clients and Blocking
- `accept()` and `recv()` **block** (pause) by default. Use `s.settimeout(5)` or `s.setblocking(False)` to avoid hanging.
- To serve many clients, use **threads**, **`select`**, or **`asyncio`**.

## Real-World Uses
Web browsing, chat apps, online games, email, file transfer, video calls, and database connections.

## Common Problems
| Problem | Fix |
|---|---|
| `Address already in use` | `s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)` before `bind()` |
| `Connection refused` | Start the server first |
| Messages merge or split | TCP has no message boundaries, so add delimiters or length prefixes |

## Summary
- A socket is an endpoint for sending and receiving data.
- Socket address = IP + port.
- TCP is reliable, UDP is fast.
- Server: `bind → listen → accept`. Client: `connect`.
- Sockets transfer bytes, so encode and decode.

**References:** [Python socket docs](https://docs.python.org/3/library/socket.html) · [Socket HOWTO](https://docs.python.org/3/howto/sockets.html) · [Beej's Guide](https://beej.us/guide/bgnet/)
