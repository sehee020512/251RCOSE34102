#include <stdio.h>
#include "process.h"
#include "priority_queue.h"
#include "report.h"

#define QUANTUM 2

void scheduler_rr(Process ps[], int n) {

    // initialization
    Queue ready_q;
    init_queue(&ready_q);

    int time = 0;
    int completed = 0;
    int run_pid = -1;
    int time_slice = 0; // time that current process consumes
    int gantt_chart[1000];

    Node node = {-1, -1, -1};

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (ps[i].arrival_time == time && ps[i].state == READY) {
                node.pid = ps[i].pid;
                node.prior = 0;
                enqueue(&ready_q, node);
            }
        }

        // I/O handling
        for (int i = 0; i < n; i++) {
            if (ps[i].state == WAITING) {
                ps[i].io_timer--; // I/O processes
                if (ps[i].io_timer <= 0) {
                    // push back to ready queue
                    ps[i].state = READY;
                    ps[i].io_timer = -1;
                    node.pid = ps[i].pid;
                    node.prior = 0;
                    enqueue(&ready_q, node);
                }
            }
        }

        // run current process
        if (run_pid != -1) {
            Process *p = &ps[run_pid - 1];
            p->remain_time--;
            time_slice++;

            // I/O occurs, push into waiting queue
            if (p->remain_time == (p->cpu_burst_time - p->io_request_time)) {
                p->state = WAITING;
                p->io_timer = p->io_burst_time;
                run_pid = -1;
                time_slice = 0;
            // process ends
            } else if (p->remain_time == 0) {
                p->state = TERMINATED;
                p->completion_time = time;
                completed++;
                run_pid = -1;
                time_slice = 0;
            // consumes all the quantum, push into ready queue
            } else if (time_slice == QUANTUM) {
                p->state = READY;
                node.pid = p->pid;
                node.prior = 0;
                enqueue(&ready_q, node);
                run_pid = -1;
                time_slice = 0;
            }
        }

        // no running process
        if (run_pid == -1 && !is_empty(&ready_q)) {
            // run next process in ready queue
            int next_pid = dequeue(&ready_q).pid;
            Process *p = &ps[next_pid - 1];
            p->state = RUNNING;
            if (p->start_time == -1) p->start_time = time;
            run_pid = p->pid;
            time_slice = 0;
        }

        gantt_chart[time] = run_pid;
        time++;
    }

    print_gantt_chart(gantt_chart, time);
    print_evaluation(ps, n);
}