#if !defined(LINKED_LIST_H)
#define LINKED_LIST_H

#include <stdbool.h>

typedef struct node
{
    char sensor_id[5];
    struct node *next;
} node_t;

typedef struct _linked_list
{
    node_t *head;
    node_t *tail;
    int length;
} List;

List *create_list();

void add_node(List *l, char *sensor_id);

bool contains(List *l, char *sensor_id);

void free_list(List *l);

#endif // LINKED_LIST_H
