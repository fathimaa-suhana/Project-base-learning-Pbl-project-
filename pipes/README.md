# Pipes

## What is this?
Pipes are basically the simplest way two processes can talk to each other. 
One process writes some data into the pipe, the other one reads it out. 
Think of it like a tube — stuff goes in one end, comes out the other.

There's two types:

**Unnamed pipes** - only works if the processes are related (like a parent 
and a child process it created using fork()). Once the program ends, the 
pipe is gone too, it's not saved anywhere.

**Named pipes (FIFO)** - this one actually shows up as a file on your system 
(you make it using mkfifo()). Because it's an actual file, two totally 
separate programs can use it to talk to each other, they don't need to be 
related at all. This is the one we're mainly using since it actually proves 
two different processes are communicating.

## What's in this folder
- `unnamed_pipe.c` - parent process creates a child, sends it a message through a pipe
- `writer.c` - creates the FIFO and writes a msg into it
- `reader.c` - reads whatever writer.c sent

writer and reader are run separately (two different terminals) to actually 
show two processes talking to each other, not just parent-child stuff.

## How to run

FIFO version:
gcc writer.c -o writer
gcc reader.c -o reader

./reader &
./writer


Unnamed pipe version:
gcc unnamed_pipe.c -o unnamed_pipe
./unnamed_pipe

## notes
- pipes only go one direction at a time, need 2 if you want both ways
- unnamed pipes = related processes only
- named pipes (FIFO) = works with any processes

## Output
Screenshot below shows both the FIFO (named pipe) demo and the unnamed pipe demo running successfully:

![Pipes demo output](screenshots/pipes_combined_output.png)