#include <stdio.h>
#include "process.h"
#include "priority_queue.h"
#include "report.h"

#define QUANTUM 3

int global_order = 0;

void scheduler_rr(Process ps[], int n) {
    Queue ready_q;
    init_queue(&ready_q);

    int time = 0;
    int completed = 0;
    int run_pid = -1;
    int time_slice = 0;
    int gantt_chart[1000];

    Node node = {-1, -1, -1};

    while (completed < n) {
        // 프로세스 도착
        for (int i = 0; i < n; i++) {
            if (ps[i].arrival_time == time && ps[i].state == READY) {
                node.pid = ps[i].pid;
                node.prior = 0;
                node.order = global_order++;
                enqueue(&ready_q, node);
            }
        }

        // I/O 완료
        for (int i = 0; i < n; i++) {
            if (ps[i].state == WAITING) {
                ps[i].io_timer--;
                if (ps[i].io_timer <= 0) {
                    ps[i].state = READY;
                    ps[i].io_timer = -1;
                    node.pid = ps[i].pid;
                    node.prior = 0;
                    node.order = global_order++;
                    enqueue(&ready_q, node);
                }
            }
        }

        // 실행 중인 프로세스 처리
        if (run_pid != -1) {
            Process *p = &ps[run_pid - 1];
            p->remain_time--;
            time_slice++;

            if (p->remain_time == (p->cpu_burst_time - p->io_request_time)) {
                p->state = WAITING;
                p->io_timer = p->io_burst_time;
                run_pid = -1;
                time_slice = 0;
            } else if (p->remain_time == 0) {
                p->state = TERMINATED;
                p->completion_time = time + 1;
                completed++;
                run_pid = -1;
                time_slice = 0;
            } else if (time_slice == QUANTUM) {
                // quantum 소진 → 큐 뒤로 이동
                p->state = READY;
                node.pid = p->pid;
                node.prior = 0;
                node.order = global_order++;
                enqueue(&ready_q, node);
                run_pid = -1;
                time_slice = 0;
            }
        }

        // 새 프로세스 실행
        if (run_pid == -1 && !is_empty(&ready_q)) {
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