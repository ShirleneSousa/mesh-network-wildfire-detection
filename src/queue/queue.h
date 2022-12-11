#if !defined(FILA_H)
#define FILA_H

#include "../message/message.h"
#include "../constants.h"

typedef struct __queue_node
{
    Message msg;
    struct __queue_node *next;
} QueueNode;

typedef struct __queue
{
    QueueNode *first;
    QueueNode *last;
} Queue;

Queue *create_queue();

bool is_empty(Queue *q);

void enqueue(Queue *q, Message msg);

Message dequeue(Queue *q);

int queue_size(Queue *q);

void destroy_queue(Queue *q);

#endif // FILA_H
