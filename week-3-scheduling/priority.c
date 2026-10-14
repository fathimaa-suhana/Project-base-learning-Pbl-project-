#include <stdio.h>
#include "scheduler.h"

void priority_sched(Process p[], int n, int preemptive) {
    static int timeline[MAX_T];
    int t = 0;
    int done = 0;

    /* Validate input */
    if (p == NULL || n <= 0 || n > MAX_T) {
        printf("Error: Invalid process input.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        if (p[i].pid < 0 || p[i].arrival < 0 || p[i].burst <= 0) {
            printf("Error: Invalid process details.\n");
            return;
        }
    }

    /* Initialize remaining burst time */
    for (int i = 0; i < n; i++) {
        p[i].remaining = p[i].burst;
    }

    /* Priority scheduling */
    while (done < n) {
        int idx = -1;

        /* Find the highest-priority available process.
           Lower priority number means higher priority.
           Equal priorities are resolved by earlier arrival. */
        for (int i = 0; i < n; i++) {
            if (p[i].remaining > 0 && p[i].arrival <= t) {
                if (idx == -1 ||
                    p[i].priority < p[idx].priority ||
                    (p[i].priority == p[idx].priority &&
                     p[i].arrival < p[idx].arrival)) {
                    idx = i;
                }
            }
        }

        /* CPU is idle if no process has arrived */
        if (idx == -1) {
            if (t >= MAX_T) {
                printf("Error: Timeline limit exceeded.\n");
                return;
            }

            timeline[t++] = -1;
            continue;
        }

        /* Run one time unit if preemptive,
           otherwise run until the process finishes */
        int run = preemptive ? 1 : p[idx].remaining;

        if (run > MAX_T - t) {
            printf("Error: Timeline limit exceeded.\n");
            return;
        }

        for (int k = 0; k < run; k++) {
            timeline[t++] = p[idx].pid;
        }

        p[idx].remaining -= run;

        if (p[idx].remaining == 0) {
            done++;
        }
    }

    /* Display results using the existing report function */
    report(p, n, timeline, t,
           preemptive
               ? "Priority (Preemptive)"
               : "Priority (Non-preemptive)");
}
