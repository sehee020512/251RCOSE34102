#include <stdio.h>
#include <stdbool.h>
#include "scheduler.h"

void scheduler_FCFS(Process ps[], int n) {
    int current_time = 0;
    int completed = 0;
    int cpu = -1;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (ps[j].arrival_time > ps[j + 1].arrival_time) {
                Process temp = ps[j];
                ps[j] = ps[j + 1];
                ps[j + 1] = temp;
            }
        }
    }
    return;
}