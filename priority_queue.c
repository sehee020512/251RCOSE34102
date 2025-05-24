#include "priority_queue.h"
#include <stdbool.h>
#include <stdio.h>

/* circular queue 
enqueue from rear
dequeue from front
data out <- front ... data ... rear <- data in */

void init_queue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

bool is_empty(Queue *q) {
    return q->front == q->rear;
}

bool is_full(Queue *q) {
    return (q->rear + 1) % MAX == q->front;
}

void enqueue(Queue *q, int value) {
    // check whether queue is full
    // queue is not full
    if (!is_full(q)) {
        q->data[q->rear] = value;
        q->rear = (q->rear + 1) % MAX;
    }
    // queue is full
    fprintf(stderr, "error: queue is full\n");
}

int dequeue(Queue *q) {
    // check whether queue is empty
    // queue is not empty
    if (!is_empty(q)) {
        int value = q->data[q->front];
        q->front = (q->front + 1) % MAX;
        return value;
    }
    // queue is empty
    fprintf(stderr, "error: queue is empty\n");
    
    return -1;
}