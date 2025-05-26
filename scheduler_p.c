#include <stdio.h>
#include "process.h"
#include "priority_queue.h"
#include "report.h"
#include "scheduler.h"

void scheduler_p(Process ps[], int n, PreemptMode mode) {

    Queue ready_q;
    init_queue(&ready_q);

    int time = 0;
    int completed = 0;
    int run_pid = -1;
    int gantt_chart[1000];

    Node node = {-1, -1, -1};

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (ps[i].arrival_time == time && ps[i].state == READY) {
                node.pid = ps[i].pid;
                switch (mode) {
                    case 0: node.prior = ps[i].remain_time; break;
                    case 1: node.prior = ps[i].priority; break; }
                enqueue(&ready_q, node);
            }
        }

        // I/O handling
        for (int i = 0; i < n; i++) {
            if (ps[i].state == WAITING) {
                ps[i].io_timer--;
                if (ps[i].io_timer <= 0) {
                    ps[i].state = READY;
                    ps[i].io_timer = -1;
                    node.pid = ps[i].pid;
                    switch (mode) {
                        case 0: node.prior = ps[i].remain_time; break;
                        case 1: node.prior = ps[i].priority; break; }
                    enqueue(&ready_q, node);
                }
            }
        }

        // preempt condition
        if (!is_empty(&ready_q)) {
            Node top = ready_q.data[0];
            int top_prio, curr_prio;

            switch (mode) {
                case PREEMPT_SJF:
                    top_prio = ps[top.pid - 1].remain_time;
                    curr_prio = (run_pid == -1) ? 9999 : ps[run_pid - 1].remain_time;
                    break;
                case PREEMPT_PRIORITY:
                    top_prio = ps[top.pid - 1].priority;
                    curr_prio = (run_pid == -1) ? 9999 : ps[run_pid - 1].priority;
                    break;
            }

            if (run_pid == -1 || top_prio < curr_prio) {
                if (run_pid != -1) {
                    Process *old = &ps[run_pid - 1];
                    old->state = READY;
                    node.pid = old->pid;
                    switch (mode) {
                        case 0: node.prior = old->remain_time; break;
                        case 1: node.prior = old->priority; break; }
                    enqueue(&ready_q, node);
                }

                Node next = dequeue(&ready_q);
                Process *p = &ps[next.pid - 1];
                p->state = RUNNING;
                if (p->start_time == -1)
                    p->start_time = time;
                run_pid = p->pid;
            }
        }

        // run current process
        if (run_pid != -1) {
            Process *p = &ps[run_pid - 1];
            p->remain_time--;

            if (p->remain_time == (p->cpu_burst_time - p->io_request_time)) {
                p->state = WAITING;
                p->io_timer = p->io_burst_time;
                run_pid = -1;
            } else if (p->remain_time == 0) {
                p->state = TERMINATED;
                p->completion_time = time + 1;
                completed++;
                run_pid = -1;
            }
        }

        gantt_chart[time] = run_pid;
        time++;
    }

    print_gantt_chart(gantt_chart, time);
    print_evaluation(ps, n);
}