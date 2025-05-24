#include <stdio.h>
#include "process.h"
#include "scheduler.h"

#define NUM_PROCESS 10

int main() {

    Process ps[NUM_PROCESS];
    new_processes(ps, NUM_PROCESS);

    int choice;

    printf("Choose Scheduling Algorithm\n");
    printf("1. FCFS 2. SJF(NP) 3. Priority(NP) 4. SJF(P) 5. Priority(P) 6. RR\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            scheduler_FCFS(ps, NUM_PROCESS);
            break;
        default:
            printf("Invalid\n");
    }

    return 0;
}