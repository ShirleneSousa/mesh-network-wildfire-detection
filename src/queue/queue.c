#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

static QueueNode *create_node(Message msg)
{
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));

    node->msg = msg;
    node->next = NULL;

    return node;
}

Queue *create_queue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->first = q->last = NULL;

    return q;
}

bool is_empty(Queue *q)
{
    return (q->first == NULL);
}

void enqueue(Queue *q, Message msg)
{
    QueueNode *node = create_node(msg);

    if (is_empty(q))
    {
        q->first = q->last = node;
    }
    else
    {
        q->last->next = node;
        q->last = node;
    }
}

Message dequeue(Queue *q)
{
    Message msg;
    QueueNode *aux;

    if (is_empty(q))
    {
        perror("Fila vazia");
        exit(EXIT_FAILURE);
    }

    aux = q->first;

    q->first = q->first->next;
    msg = aux->msg;

    // free(aux);

    return msg;
}

int queue_size(Queue *q)
{
    int size = 0;
    QueueNode *aux = q->first;

    while (aux != NULL)
    {
        size++;
        aux = aux->next;
    }

    return size;
}

void destroy_queue(Queue *q)
{
    while (!is_empty(q))
        dequeue(q);

    free(q);
}