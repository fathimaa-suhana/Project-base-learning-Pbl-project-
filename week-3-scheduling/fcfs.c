#include "scheduler.h"

void fcfs(Process p[], int n) {
    static int timeline[MAX_T];
    int t = 0, done = 0;
    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;

    while (done < n) {
        int idx = -1;
        for (int i = 0; i < n; i++)
            if (p[i].remaining > 0 && p[i].arrival <= t &&
                (idx == -1 || p[i].arrival < p[idx].arrival))
                idx = i;
        if (idx == -1) { timeline[t++] = -1; continue; }
        for (int k = 0; k < p[idx].burst; k++) timeline[t++] = p[idx].pid;
        p[idx].remaining = 0;
        done++;
    }
    report(p, n, timeline, t, "FCFS");
}