#include <stdio.h>
#include "process.h"
#include "priority_queue.h"
#include "report.h"
#include "scheduler.h"

void scheduler_np(Process ps[], int n, PriorMode mode) {
    
    Queue ready_q;
    init_queue(&ready_q);

    int time = 0; // running time of computer
    int completed = 0; // number of completed processes
    int run_pid = -1; // currently running process
    int gantt_chart[1000];

    Node node = {-1, -1, -1};

    while (completed < n) {
        // push into ready queue
        for (int i = 0; i < n; i++) {
            if (ps[i].arrival_time == time && ps[i].state == READY) {
                node.pid = ps[i].pid;
                switch (mode) {
                    case 0: node.prior = ps[i].arrival_time; break; // FCFS
                    case 1: node.prior = ps[i].cpu_burst_time; break; // SJF
                    case 2: node.prior = ps[i].priority; break; } // Priority           
                enqueue(&ready_q, node);
            }
        }
        
        // handle I/O
        for (int i = 0; i < n; i++) {
            if (ps[i].state == WAITING) {
                ps[i].io_timer--;
                if (ps[i].io_timer <= 0) {
                    ps[i].state = READY;
                    ps[i].io_timer = -1;
                    node.pid = ps[i].pid;
                    switch (mode) {
                        case 0: node.prior = ps[i].arrival_time; break;
                        case 1: node.prior = ps[i].cpu_burst_time; break;
                        case 2: node.prior = ps[i].priority; break; } 
                    enqueue(&ready_q, node);
                }
            }
        }

        // run process
        if (run_pid != -1) {
            Process *p = &ps[run_pid -1];
            p->remain_time--;

            if (p->remain_time == (p->cpu_burst_time - p->io_request_time)) {
                p->state = WAITING;
                p->io_timer = p->io_burst_time;
                run_pid = -1;
            }

            else if (p->remain_time == 0) {
                p->state = TERMINATED;
                p->completion_time = time + 1;
                completed ++;
                run_pid = -1;
            }
        }

        // allocate process to cpu
        if (run_pid == -1 && !is_empty(&ready_q)) {
            int next_pid = dequeue(&ready_q).pid;
            Process *p = &ps[next_pid - 1];
            p->state = RUNNING;
            if (p->start_time == -1)
                p->start_time = time;
            run_pid = p->pid; }

        gantt_chart[time] = run_pid;

        time++; // check every tick
    }

    print_gantt_chart(gantt_chart, time);
    print_evaluation(ps, n);

    return;
}