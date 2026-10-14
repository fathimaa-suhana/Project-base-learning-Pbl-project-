#ifndef SCHEDULER_H
#define SCHEDULER_H

#define MAX_T 1000

typedef struct {
    int pid;
    int arrival;
    int burst;      // never modify this
    int priority;   // lower number = higher priority
    int remaining;  // algorithms work on this
} Process;

void fcfs(Process p[], int n);
void sjf(Process p[], int n, int preemptive);
void priority_sched(Process p[], int n, int preemptive);
void round_robin(Process p[], int n, int quantum);

// timeline[t] = pid running at time t, or -1 if idle
void report(Process p[], int n, int timeline[], int total_time, const char *name);

#endif