#if !defined(MENSAGEM_H)
#define MENSAGEM_H

#include "../constants.h"
#include "../data_structures/linked_list/linked_list.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct _message
{
    char source_id[5];
    int x, y;
    char time[9];
    List *visits;
} Message;

Message create_message(char *source_id, int x, int y);

void write_message(FILE *fp, Message msg);

int read_message(FILE *fp, char *log_timestamp, Message *msg);

bool is_mensagem_inedita(FILE *fp, Message msg);

void add_visit(Message msg, char *sensor_id);

bool was_visited(Message msg, char *sensor_id);

#endif // MENSAGEM_H
