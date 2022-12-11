#if !defined(MENSAGEM_H)
#define MENSAGEM_H

#include "../utils/utils.h"
#include <pthread.h>
#include <stdio.h>

typedef struct __message
{
    char source_id[5];
    int x, y;
    struct tm *time;
    int ttl;
} Message;

Message create_message(char *source_id, int x, int y);

void write_message(FILE *fp, Message msg);

int read_message(FILE *fp, Message *msg);

bool is_mensagem_inedita(FILE *fp, Message msg);

#endif // MENSAGEM_H
