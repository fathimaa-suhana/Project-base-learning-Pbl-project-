#include <stdio.h>
#include "scheduler.h"

void report(Process p[], int n, int timeline[], int T, const char *name) {
    printf("\n=== %s ===\nGantt chart:\n|", name);
    int s = 0;
    for (int t = 1; t <= T; t++) {
        if (t == T || timeline[t] != timeline[s]) {
            if (timeline[s] < 0) printf(" IDLE|");
            else printf(" P%-2d |", timeline[s]);
            s = t;
        }
    }
    printf("\n");
    s = 0;
    printf("%-6d", 0);
    for (int t = 1; t <= T; t++)
        if (t == T || timeline[t] != timeline[s]) { printf("%-6d", t); s = t; }
    printf("\n\n");

    printf("PID  AT  BT  PR  FT  WT  TAT  RT\n");
    float totalWT = 0, totalTAT = 0;
    int busy = 0;
    for (int t = 0; t < T; t++) if (timeline[t] >= 0) busy++;

    for (int i = 0; i < n; i++) {
        int start = -1, finish = 0;
        for (int t = 0; t < T; t++)
            if (timeline[t] == p[i].pid) {
                if (start < 0) start = t;
                finish = t + 1;
            }
        int tat = finish - p[i].arrival;
        int wt = tat - p[i].burst;
        int rt = start - p[i].arrival;
        totalWT += wt;
        totalTAT += tat;
        printf("P%-3d %-3d %-3d %-3d %-3d %-3d %-4d %-3d\n",
               p[i].pid, p[i].arrival, p[i].burst, p[i].priority, finish, wt, tat, rt);
    }
    printf("\nAvg WT = %.2f, Avg TAT = %.2f, CPU utilization = %.1f%%\n",
           totalWT / n, totalTAT / n, 100.0 * busy / T);
}