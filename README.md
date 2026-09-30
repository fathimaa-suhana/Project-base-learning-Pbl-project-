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

| Technique       | Description                                              | Assigned To |
|-----------------|-----------------------------------------------------------|-------------|
| Pipes           | One-way communication channel between related processes  | Siddhartha G |
| Message Queues  | Messages stored in a queue, read by other processes       | Suhana      |
| Shared Memory   | Common memory segment accessed by multiple processes       | [Name 3]    |
| Sockets         | Communication over network-style endpoints                | [Name 4]    |

## Project Structure
ipc-project/
├── pipes/
├── msgqueue/
├── sharedmem/
└── sockets/

Each folder contains:
- A `README.md` explaining that technique
- Source code for two processes (sender/writer and receiver/reader) 
  demonstrating that IPC mechanism in action

## Team
| Name        | Role       | IPC Technique |
|-------------|------------|---------------|
| Siddhartha G | Team Lead  | Pipes        |
| Suhana      | Member     | Message Queues|
| [Name 3]    | Member     | Shared Memory |
| [Name 4]    | Member     | Sockets       |

## How to Run
Instructions for running each demo are inside that technique's own folder.
