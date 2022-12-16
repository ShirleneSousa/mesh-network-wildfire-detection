#include "linked_list.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

List *create_list()
{
    List *this = (List *)malloc(sizeof(List));

    this->head = NULL;
    this->tail = NULL;

    this->length = 0;

    return this;
}

static node_t *_create_node(char *sensor_id)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));

    strcpy(node->sensor_id, sensor_id);
    node->next = NULL;

    return node;
}

void add_node(List *l, char *sensor_id)
{
    node_t *new_node = _create_node(sensor_id);

    if (l->length == 0)
        l->head = new_node;
    else
        l->tail->next = new_node;

    l->tail = new_node;

    l->length++;
}

bool contains(List *l, char *sensor_id)
{
    node_t *current = l->head;

    while (current != NULL)
    {
        if (strcmp(current->sensor_id, sensor_id) == 0)
            return true;
        else
            current = current->next;
    }

    return false;
}

void free_list(List *l)
{
    node_t *current = l->head;
    node_t *next;

    while (current != NULL)
    {
        next = current->next;
        free(current);
        current = next;
    }

    free(l);
}