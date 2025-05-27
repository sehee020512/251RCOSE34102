#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H
#include <stdbool.h>

#define MAX 100 // ???

typedef struct {
    int pid; // process id
    int prior; // lower number, higher priority
    int order; // for stable priority queue regarding enqueue order
} Node;

typedef struct {
    Node data[MAX]; // node array
    int size; // queue size
    int id; // enqueue order
} Queue;

void init_queue(Queue *q);
bool is_empty(Queue *q);
void enqueue(Queue *q, Node node);
Node dequeue(Queue *q);

#endif