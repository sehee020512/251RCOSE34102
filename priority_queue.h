#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#define MAX 100 // ???

// circular queue
typedef struct {
    int data[MAX]; // data array
    int front; // front index
    int rear; // rear index
} Queue;

void init_queue(Queue *q);
bool is_empty(Queue *q);
bool is_full(Queue *q);
void enqueue(Queue *q, int value);
int dequeue(Queue *q);

#endif