#ifndef PROCESS_H
#define PROCESS_H

typedef enum { READY, RUNNING, WAITING, TERMINATED } State;

typedef struct {
    int pid; // process id
    int arrival_time; // time when process is arrived
    int cpu_burst_time; // time required for cpu to processed
    int remain_time; // preemptive method
    int io_burst_time;  // time required for i/o to processed
    int io_request_time; // time when i/o is requested
    int priority; // priority of process

    // for evaluation
    int waiting_time;
    int turnaround_time;

    // for calculate waiting time and turnaround time
    int start_time; // time process starts
    int completion_time; // time process is completed
    int io_timer; // remaining i/o time

    State state; // process state
} Process;

void new_processes(Process *ps, int n);

#endif