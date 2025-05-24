#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "process.h"

void scheduler_FCFS(Process ps[], int n);
void scheduler_SJF_np(Process ps[], int n);
void scheduler_SJF_p(Process ps[], int n);
void scheduler_Priority_np(Process ps[], int n);
void scheduler_Priority_p(Process ps[], int n);
void scheduler_RB(Process ps[], int n, int qt);

#endif