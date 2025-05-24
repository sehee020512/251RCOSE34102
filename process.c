#include "process.h"
#include <time.h>
#include <stdlib.h>

void new_processes(Process ps[], int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        // process ID
        ps[i].pid = i + 1;

        // CPU
        ps[i].arrival_time = rand() % 10; // [0, 9]
        ps[i].cpu_burst_time = (rand() % 6) + 5; // [5, 10]
        ps[i].remain_time = ps[i].cpu_burst_time;

        // I/O (only one I/O interrupt occurs in one process)
        ps[i].io_burst_time = (rand() % 4) + 1; // [1, 4] I/O is often shorter than cpu burst time
        ps[i].io_request_time = (rand() % (ps[i].cpu_burst_time - 1)) + 1; // [1, burst-1] I/O is requested during cpu burst

        // priority
        ps[i].priority = rand() % 5; // [0, 4] lower number, higher priority

        // for evaluation
        ps[i].waiting_time = 0;
        ps[i].turnaround_time = 0;

        ps[i].completion_time = -1;
        ps[i].io_timer = 0;

        ps[i].state = READY;
    }

    return;
}