#include <stdio.h>
#include "process.h"
#include "priority_queue.h"
#include "report.h"
#include "scheduler.h"

void scheduler_np(Process ps[], int n, NonpreemptMode mode) {
    
    // initialization
    Queue ready_q;
    init_queue(&ready_q);

    int time = 0; // running time of computer
    int completed = 0; // number of completed processes
    int run_pid = -1; // currently running process
    int gantt_chart[1000];

    Node node = {-1, -1, -1}; // dummy node

    // loop until all the processes are completed
    while (completed < n) {
        // push arriving process into ready queue
        for (int i = 0; i < n; i++) {
            if (ps[i].arrival_time == time && ps[i].state == READY) {
                node.pid = ps[i].pid; // set node process id
                // set node priority
                switch (mode) {
                    case NONPREEMPT_FCFS: node.prior = ps[i].arrival_time; break;
                    case NONPREEMPT_SJF: node.prior = ps[i].remain_time; break;
                    case NONPREEMPT_PRIORITY: node.prior = ps[i].priority; break; }     
                // enqueue node into ready queue    
                enqueue(&ready_q, node);
            }
        }
        
        // I/O handling
        for (int i = 0; i < n; i++) {
            // I/O handle
            if (ps[i].state == WAITING) {
                ps[i].io_timer--;
                // If I/O ends, go back to ready queue
                if (ps[i].io_timer <= 0) {
                    ps[i].state = READY;
                    ps[i].io_timer = -1;
                    
                    node.pid = ps[i].pid;
                    switch (mode) {
                        case NONPREEMPT_FCFS: node.prior = ps[i].arrival_time; break;
                        case NONPREEMPT_SJF: node.prior = ps[i].remain_time; break;
                        case NONPREEMPT_PRIORITY: node.prior = ps[i].priority; break; } 
                    enqueue(&ready_q, node);
                }
            }
        }

        // run process
        if (run_pid != -1) {
            Process *p = &ps[run_pid -1];
            p->remain_time--;

            // I/O occurs
            if (p->remain_time == (p->cpu_burst_time - p->io_request_time)) {
                p->state = WAITING; // go to waiting queue
                p->io_timer = p->io_burst_time; // set io_timer
                run_pid = -1; // no running process
            }

            // process ends
            else if (p->remain_time == 0) {
                p->state = TERMINATED;
                p->completion_time = time;
                completed ++;
                run_pid = -1; // no running process
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

        gantt_chart[time] = run_pid; // record gantt chart

        time++; // check every tick
    }

    print_gantt_chart(gantt_chart, time);
    print_evaluation(ps, n);

    return;
}