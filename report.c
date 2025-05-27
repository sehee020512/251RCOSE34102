#include <stdio.h>
#include "report.h"

void print_gantt_chart(int gantt_chart[], int time) {
    printf("\nGantt Chart:\n");
    for (int t = 0; t < time; t++) {
        if (gantt_chart[t] == -1)
            printf("| -- ");
        else
            printf("| P%d ", gantt_chart[t]);
    }
    printf("|\n\n");

    return;
}

void print_evaluation(Process ps[], int n) {
    printf("\n%-5s %-8s %-6s %-7s %-9s %-9s %-12s %-15s %-8s %-10s\n",
           "PID", "Arrival", "Burst", "IO_Req", "IO_Burst", "Priority", "Start_Time", "Completion_Time", "Waiting", "Turnaround");

    for (int i = 0; i < n; i++) {
        int tat = ps[i].completion_time - ps[i].arrival_time;
        int wt = tat - ps[i].cpu_burst_time - ps[i].io_burst_time;
        // if (wt < 0) wt = 0;

        printf("P%-4d %-8d %-6d %-7d %-9d %-9d %-12d %-15d %-8d %-10d\n",
               ps[i].pid,
               ps[i].arrival_time,
               ps[i].cpu_burst_time,
               ps[i].io_request_time,
               ps[i].io_burst_time,
               ps[i].priority,
               ps[i].start_time,
               ps[i].completion_time,
               wt,
               tat);
    }
}