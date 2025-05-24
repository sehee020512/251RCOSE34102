#include <stdio.h>
#include "process.h"
#include "queue.h"
#include "scheduler.h"

#define NUM_PROCESS 10

int main() {
    Process ps[NUM_PROCESS];
    new_processes(ps, NUM_PROCESS);
    
    Queue ready_q;
    // Queue waiting_q;
    init_queue(&ready_q);
    // init_queue(&waiting_q);

    int time = 0; // running time of computer
    int completed = 0; // number of completed processes
    int run_pid = -1; // currently running process
    int gantt_chart[1000];

    // non-preemptive
    while (completed < NUM_PROCESS) {
        // check arrival
        for (int i = 0; i < NUM_PROCESS; i++) {
            if (ps[i].arrival_time == time && ps[i].state == READY)
                enqueue(&ready_q, ps[i].pid); }
        
        for (int i = 0; i < NUM_PROCESS; i++) {
            if (ps[i].state == WAITING) ps[i].io_timer--;
            if (ps[i].io_timer <= 0) {
                ps[i].state = READY;
                enqueue(&ready_q, ps[i].pid);
            }
        }

        if (run_pid != -1) {
            Process *p = &ps[run_pid -1];
            p->remain_time--;

            if (p->remain_time == (p->cpu_burst_time - p->io_request_time)) {
                p->state = WAITING;
                p->io_timer = p->io_burst_time;
                // enqueue(&waiting_q, p->pid);
                run_pid = -1;
            }
            else if (p->remain_time == 0) {
                p->state = TERMINATED;
                p->completion_time = time + 1;
                completed ++;
                run_pid = -1;
            }
        }

        if (run_pid == -1 && !is_empty(&ready_q)) {
            int next_pid = dequeue(&ready_q);
            Process *p = &ps[next_pid - 1];
            p->state = RUNNING;
            if (p->start_time == -1) p->start_time = time;
            run_pid = p->pid;
        }

        gantt_chart[time] = run_pid;

        time++; // check every tick
    }

    return 0;
}