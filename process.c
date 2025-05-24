#include "process.h"
#include <time.h>

void new_processes(Process *ps, int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        ps[i].pid = i + 1;
        ps[i].arrival_time = rand() % ???;
        ps[i].cpu_burst_time = (rand() % ???) + 1;
        ps[i].io_burst_time = (rand() % ???);
        ps[i].io_request_time = (rand() % ps[i].cpu_burst_time) + 1;
        ps[i].priority = rand() % ???;
    }
}