#include "scheduler.h"

void round_robin(Process p[], int n, int quantum) {
    static int timeline[MAX_T];
    int queue[5000], head = 0, tail = 0;
    int added[100] = {0};
    int t = 0, done = 0;
    for (int i = 0; i < n; i++) p[i].remaining = p[i].burst;

    while (done < n) {
        for (int i = 0; i < n; i++)
            if (!added[i] && p[i].arrival <= t) { queue[tail++] = i; added[i] = 1; }

        if (head == tail) { timeline[t++] = -1; continue; }

        int i = queue[head++];
        int run = p[i].remaining < quantum ? p[i].remaining : quantum;
        for (int k = 0; k < run; k++) timeline[t++] = p[i].pid;
        p[i].remaining -= run;

        // processes that arrived during this slice go in before the preempted one
        for (int j = 0; j < n; j++)
            if (!added[j] && p[j].arrival <= t) { queue[tail++] = j; added[j] = 1; }

        if (p[i].remaining > 0) queue[tail++] = i;
        else done++;
    }
    report(p, n, timeline, t, "Round Robin");
}