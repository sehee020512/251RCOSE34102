#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdbool.h>

#define MAX 100 // ???

typedef struct {
    int pid;
    int prior; // lower number, higher priority
    int order; // for stable priority queue regarding enqueue order
} Node;

typedef struct {
    Node data[MAX];
    int size; // current size
    int id; // pointer
} Queue;

void init_queue(Queue *q);
bool is_empty(Queue *q);
void enqueue(Queue *q, Node node);
Node dequeue(Queue *q);

#endif