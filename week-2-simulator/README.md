# Week 2 — Multi-Process Simulator & IPC

## What this is
This week we had to take our simulator and actually split it into 3 separate 
processes that talk to each other using IPC, instead of just one program doing 
everything. Point is to learn how to design a system, not just write one big 
program.

## The 3 processes
- **UI Process** - handles user input and shows output
- **Core Process** - does the actual work, CPU execution, memory, stack, queue stuff
- **Logging Process** - logs whats happening, executions and errors

Flow goes: UI → Core → Logger

## Who did what
- UI Process - [Suhana]
- Core Process - [Pratyush]
- Logging Process - [Rishab]
- Integration (wiring everything together with IPC, testing, benchmarking) - Siddhartha G (Team Lead)

## IPC mechanism we picked
We went with **Message Queues** for this. Reason - the flow here is basically 
one direction (UI sends commands to Core, Core sends results/events to Logger), 
and message queues let us tag messages with a type, so we can separate normal 
execution events from error events easily. Didn't go with shared memory since 
that needs extra synchronization (mutex/semaphores) which adds complexity we 
didnt need here, and didnt go with sockets since this isnt really a client-server 
setup, its more of a pipeline.

## Folder structure

week-2-simulator/
├── simulator.c (baseline single-process version, for comparison)
├── ui/
├── core/
└── logger/


## Baseline vs Multi-process
We first built `simulator.c` as a single-process version (everything in one 
program) to use as a baseline. Then split it into the 3 processes above to 
compare performance between running it as one process vs three processes 
communicating via IPC.

## How to run
Instructions for running are inside each process's folder.

## Notes
- single process version is faster for small tasks since theres no IPC overhead, 
  but splitting into processes makes the system more modular and each part can 
  be scaled/debugged separately
- benchmark results and comparison are in [wherever you put them]