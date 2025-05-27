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
    int total_wt = 0;
    int total_tat = 0;

    printf("%-5s %-11s %-16s %-8s %-10s\n",
           "PID", "Start_Time", "Completion_Time", "Waiting", "Turnaround");

    for (int i = 0; i < n; i++) {
        // turnaround time = completion time - arrival time
        int tat = ps[i].completion_time - ps[i].arrival_time;
        // waiting time = turnaround time - cpu burst time - io burst time
        // time in waiting queue
        int wt = tat - ps[i].cpu_burst_time - ps[i].io_burst_time;

        total_wt += wt;
        total_tat += tat;

        printf("P%-4d %-11d %-16d %-8d %-10d\n",
               ps[i].pid,
               ps[i].start_time,
               ps[i].completion_time,
               wt,
               tat);
    }

    double avg_wt = (double)total_wt / n;
    double avg_tat = (double)total_tat / n;

    printf("\nAverage Waiting Time   : %.2f\n", avg_wt);
    printf("Average Turnaround Time: %.2f\n", avg_tat);
}