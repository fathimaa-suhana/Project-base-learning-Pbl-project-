# Message Queues

## What is this?
Message queue is another way processes can talk to each other, but instead 
of a direct pipe/tube like pipes, it's more like a mailbox. One process 
sends a message, it sits in the queue (managed by the OS), and another 
process picks it up whenever it's ready. They don't even need to be running 
at the same exact time necessarily.

Difference from pipes - pipes are basically FIFO (first in first out) data 
stream with no real structure, but message queues actually send stuff in 
chunks called "messages" with a type/priority attached. So the reading 
process can pick specific messages out of the queue instead of just reading 
whatever comes first.

There's two ways to do this on Linux:

**System V message queues** - older one, uses `msgget()`, `msgsnd()`, `msgrcv()`. 
Needs a "key" to identify the queue (kinda like an address so both processes 
know which queue they're talking about)

**POSIX message queues** - newer one, uses `mq_open()`, `mq_send()`, `mq_receive()`. 
Works more like normal files, a bit easier to use tbh

we're using System V

## What's in this folder
- `sender.c` - creates the message queue, sends a message into it
- `receiver.c` - connects to the same queue, reads the message out

sender and receiver run as two separate processes to prove real IPC, not 
just parent-child stuff

## How to run
gcc sender.c-o sender

gcc receiver.c-o receiver

./receiver &

./sender
## notes
- messages have a "type" field, receiver can filter by type if it wants
- unlike pipes, the queue doesn't disappear if one process ends, it stays 
  until someone deletes it (or system reboots) - need to clean up manually 
  using `ipcrm` or it'll just sit there
- queue has a max size, if it fills up, sender blocks until space is freed
