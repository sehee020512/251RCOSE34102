#include "priority_queue.h"
#include <stdio.h>

void init_queue(Queue *q) {
    q->size = 0;
    q->id = 0;
}

bool is_empty(Queue *q) {
    return q->size == 0;
}

void enqueue(Queue *q, Node node) {
    if (q->size >= MAX) {
        fprintf(stderr, "error: queue overflow\n");
        return; }

    node.order = q->id++;

    int i = q->size - 1; // last id

    while (i >= 0 &&
          // compare prority
          (q->data[i].prior > node.prior ||
          // if priority is same, compare order
          (q->data[i].prior == node.prior && q->data[i].order > node.order))) {
        q->data[i + 1] = q->data[i];
        i--;
    }

    q->data[i + 1] = node;
    q->size++;

    //
    //printf("Enqueue: pid=%d, prior=%d, order=%d\n", node.pid, node.prior, node.order);
    //

    return;
}

Node dequeue(Queue *q) {
    if (is_empty(q)) {
        fprintf(stderr, "error : queue underflow\n");
        Node dummy = {-1, -1, -1};
        return dummy;
    }
    Node top = q->data[0]; // highest priority

    // shift
    for (int i = 1; i < q->size; i++) {
        q->data[i - 1] = q->data[i]; }

    q->size--;

    //
    //printf("Dequeue: pid=%d, prior=%d, order=%d\n", top.pid, top.prior, top.order);
    //

    return top;
}
