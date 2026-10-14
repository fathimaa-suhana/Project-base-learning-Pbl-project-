#include "scheduler.h"

void priority_sched(Process p[], int n, int preemptive) {
    static int timeline[MAX_T];
    int t = 0, done = 0;
    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;

    while (done < n) {
        int idx = -1;
        for (int i = 0; i < n; i++)
            if (p[i].remaining > 0 && p[i].arrival <= t &&
                (idx == -1 || p[i].priority < p[idx].priority))
                idx = i;
        if (idx == -1) { timeline[t++] = -1; continue; }

        int run = preemptive ? 1 : p[idx].remaining;
        for (int k = 0; k < run; k++) timeline[t++] = p[idx].pid;
        p[idx].remaining -= run;
        if (p[idx].remaining == 0) done++;
    }
    report(p, n, timeline, t,
           preemptive ? "Priority (Preemptive)" : "Priority (Non-preemptive)");
}