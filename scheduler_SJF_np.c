#include <stdio.h>
#include <stdbool.h>
#include "scheduler.h"

void shceduler_SJF_np(Process ps[], int n) {
    int completed = 0;
    int current_time = 0;
    bool is_done[n];

    for (int i = 0; i < n; i++) is_done[i] = false;

    while (completed < n) {
        int id = -1;
        int min_burst = 1e9;

        for (int i = 0; i < n; i++) {
            // compare burst_time
            if (!is_done[i] && ps[i].arrival_time <= current_time) {
                if (ps[i].cpu_burst_time < min_burst) {
                    min_burst = ps[i].cpu_burst_time;
                    id = i;
                }
            }
            // if burst time is same, compare arrival time
            else if (ps[i].cpu_burst_time == min_burst) {
                if (ps[i].arrival_time < ps[id].arrival_time) {
                    id = i;
                }
            }
        }
        
        // process whose burst time is min doesn't exist
        if (id != -1) {
            c
        }
        // no process to run
        else current_time ++;
    }
}