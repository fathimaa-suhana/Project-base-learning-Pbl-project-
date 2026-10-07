# Shared Memory Message Queues

This project demonstrates Inter-Process Communication (IPC) using System V message queues on Linux.

## What is this?

Message queues allow processes to communicate by sending messages through an OS-managed queue, unlike pipes which are direct FIFO data streams. The key differences:

- **Pipes**: FIFO data stream with no structure, read whatever comes first
- **Message Queues**: Send data in chunks called "messages" with a type/priority. The reading process can filter by message type

## Project Structure

- `sender.c` - Creates the message queue and sends a message into it
- `receiver.c` - Connects to the same queue and reads the message out

Both programs run as separate processes to demonstrate real IPC.

## How to Run

```bash
# Compile
gcc sender.c -o sender
gcc receiver.c -o receiver

# Start receiver in background
./receiver &

# Run sender
./sender
```

## Notes

- Messages have a "type" field; the receiver can filter by type if desired
- Unlike pipes, the queue persists even if one process ends. It stays until manually deleted with `ipcrm` or system reboot
- The queue has a maximum size; if it fills up, the sender blocks until space is freed
- Uses System V message queues (`msgget()`, `msgsnd()`, `msgrcv()`) requiring a "key" to identify the queue