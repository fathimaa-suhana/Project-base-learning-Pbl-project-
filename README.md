# Inter-Process Communication (IPC) — PBL Project

## About
This project is part of our college's Project Based Learning (PBL) curriculum. 
The topic assigned to our team is **Inter-Process Communication (IPC)** — the 
mechanisms operating systems use to allow separate processes to communicate 
and share data with each other.

## What is IPC?
Processes in an operating system are isolated from each other by default — 
they don't share memory space. IPC refers to the set of techniques that let 
independent processes exchange data and synchronize their actions. It's a 
core concept in operating systems, used in everything from shell pipelines 
to client-server applications.

## Techniques Covered
Our team has split the topic into 4 major IPC techniques, with each member 
implementing one:

| Technique       | Description                                              | Assigned To     |
|-----------------|-----------------------------------------------------------|------------------|
| Pipes           | One-way communication channel between related processes  | Siddhartha G     |
| Message Queues  | Messages stored in a queue, read by other processes       | Suhana           |
| Shared Memory   | Common memory segment accessed by multiple processes       | Rishab Salian    |
| Sockets         | Communication over network-style endpoints                | Pratyush         |

## Week 2 — Multi-Process Simulator
On top of the 4 core techniques, we also built a small multi-process simulator 
to apply IPC in a more practical setup — a CPU/Stack simulator split into 3 
separate processes that talk to each other using Message Queues.

**Flow:** UI → Core → Logger

| Process | What it does                                   | Assigned To     |
|---------|-------------------------------------------------|------------------|
| UI      | Takes user commands, sends them to Core         | Suhana           |
| Core    | Executes the commands (stack ops, add, etc.)    | Pratyush          |
| Logger  | Receives results/events, writes them to log.txt | Rishab Salian    |

We also built a baseline single-process version (`simulator.c`) to compare 
against — showing single process is faster for small tasks but less modular, 
while splitting into 3 processes adds IPC overhead but improves separation 
of concerns and scalability.

## Project Structure

├── pipes/
├── msgqueue/
├── sharedmem/
├── sockets/
└── week-2-simulator/
├── simulator.c (baseline single-process version)
├── ui/
├── core/
└── logger/


Each of the 4 technique folders contains:
- A `README.md` explaining that technique
- Source code for two processes (sender/writer and receiver/reader) 
  demonstrating that IPC mechanism in action

## Team
| Name          | Role       | IPC Technique  |
|---------------|------------|----------------|
| Siddhartha G  | Team Lead  | Pipes          |
| Suhana        | Member     | Message Queues |
| Rishab Salian | Member     | Shared Memory  |
| Pratyush      | Member     | Sockets        |

## How to Run
Instructions for running each demo are inside that technique's own folder.
