
#include <stdio.h>
#include "scheduler.h"

#define MAX_PROCESSES 100

int main(void) {
    Process p[MAX_PROCESSES];
    int n, choice, quantum;

    printf("====================================\n");
    printf("   CPU PROCESS SCHEDULING SIMULATOR\n");
    printf("====================================\n");

    printf("Enter number of processes (1-%d): ",
           MAX_PROCESSES);

    if (scanf("%d", &n) != 1 ||
        n < 1 || n > MAX_PROCESSES) {
        printf("Invalid number of processes.\n");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;

        printf("\nProcess P%d\n", p[i].pid);

        printf("Arrival Time: ");
        if (scanf("%d", &p[i].arrival) != 1 ||
            p[i].arrival < 0) {
            printf("Invalid arrival time.\n");
            return 1;
        }

        printf("Burst Time: ");
        if (scanf("%d", &p[i].burst) != 1 ||
            p[i].burst <= 0) {
            printf("Burst time must be positive.\n");
            return 1;
        }

        printf("Priority (smaller number = higher priority): ");
        if (scanf("%d", &p[i].priority) != 1) {
            printf("Invalid priority.\n");
            return 1;
        }
    }

    printf("\nEnter Round Robin time quantum: ");
    if (scanf("%d", &quantum) != 1 || quantum <= 0) {
        printf("Time quantum must be positive.\n");
        return 1;
    }

    printf("\n========== SCHEDULING MENU ==========\n");
    printf("1. First Come First Serve (FCFS)\n");
    printf("2. Shortest Job First (Non-preemptive)\n");
    printf("3. Shortest Remaining Time First (SRTF)\n");
    printf("4. Priority Scheduling (Non-preemptive)\n");
    printf("5. Priority Scheduling (Preemptive)\n");
    printf("6. Round Robin (RR)\n");
    printf("=====================================\n");

    printf("Choose an algorithm (1-6): ");

    if (scanf("%d", &choice) != 1 ||
        choice < 1 || choice > 6) {
        printf("Invalid menu choice.\n");
        return 1;
    }

    printf("\n");

    switch (choice) {
        case 1:
            fcfs(p, n);
            break;

        case 2:
            sjf(p, n, 0);
            break;

        case 3:
            sjf(p, n, 1);
            break;

        case 4:
            priority_sched(p, n, 0);
            break;

        case 5:
            priority_sched(p, n, 1);
            break;

        case 6:
            round_robin(p, n, quantum);
            break;
    }

    return 0;
}
