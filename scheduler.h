#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

typedef enum {
    NONPREEMPT_FCFS,
    NONPREEMPT_SJF,
    NONPREEMPT_PRIORITY
} NonpreemptMode;

typedef enum {
    PREEMPT_SJF,
    PREEMPT_PRIORITY
} PreemptMode;

void scheduler_np(Process ps[], int n, NonpreemptMode mode);
void scheduler_p(Process ps[], int n, PreemptMode mode);
void scheduler_rr(Process ps[], int n);

#endif