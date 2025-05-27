#include <stdio.h>
#include "process.h"
#include "scheduler.h"

#define NUM_PROCESS 3

int main() {
    Process ps[NUM_PROCESS];
    new_processes(ps, NUM_PROCESS);

    printf("%-5s %-8s %-6s %-7s %-9s %-9s\n", 
           "PID", "Arrival", "Burst", "IO_Req", "IO_Burst", "Priority");

    for (int i = 0; i < NUM_PROCESS; i++) {
        printf("P%-4d %-8d %-6d %-7d %-9d %-9d\n",
            ps[i].pid,
            ps[i].arrival_time,
            ps[i].cpu_burst_time,
            ps[i].io_request_time,
            ps[i].io_burst_time,
            ps[i].priority);
    }

    // FCFS
    printf("\n=== [1] FCFS ===\n");
    scheduler_np(ps, NUM_PROCESS, NONPREEMPT_FCFS);

    // SJF (Non-Preemptive)
    printf("\n=== [2] SJF (Non-Preemptive) ===\n");
    new_processes(ps, NUM_PROCESS);
    scheduler_np(ps, NUM_PROCESS, NONPREEMPT_SJF);

    // Priority (Non-Preemptive)
    printf("\n=== [3] Priority (Non-Preemptive) ===\n");
    new_processes(ps, NUM_PROCESS);
    scheduler_np(ps, NUM_PROCESS, NONPREEMPT_PRIORITY);

    // SJF (Preemptive)
    printf("\n=== [4] SJF (Preemptive) ===\n");
    new_processes(ps, NUM_PROCESS);
    scheduler_p(ps, NUM_PROCESS, PREEMPT_SJF);

    // Priority (Preemptive)
    printf("\n=== [5] Priority (Preemptive) ===\n");
    new_processes(ps, NUM_PROCESS);
    scheduler_p(ps, NUM_PROCESS, PREEMPT_PRIORITY);

    // Round Robin
    printf("\n=== [6] Round Robin ===\n");
    new_processes(ps, NUM_PROCESS);
    scheduler_rr(ps, NUM_PROCESS);

    return 0;
}
