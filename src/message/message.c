#include "message.h"
#include "../utils/utils.h"
#include "../constants.h"
#include <string.h>

static int _time_diff(Message m1, Message m2)
{
    int m1_time = m1.time->tm_hour * 3600 + m1.time->tm_min * 60 + m1.time->tm_sec;
    int m2_time = m2.time->tm_hour * 3600 + m2.time->tm_min * 60 + m2.time->tm_sec;

    m1_time += (TTL - m1.ttl);
    m2_time += (TTL - m2.ttl);

    return m1_time - m2_time;
}

Message create_message(char *source_id, int x, int y)
{
    Message msg;

    strcpy(msg.source_id, source_id);
    msg.x = x;
    msg.y = y;
    msg.time = now();
    msg.ttl = TTL;

    return msg;
}

void write_message(FILE *fp, Message msg)
{

    fseek(fp, 0, SEEK_END);
    fprintf(fp, "%s | %s detectou um incêndio em (%d,%d) as %s\n",
            tm_to_string(now()),
            msg.source_id,
            msg.x,
            msg.y,
            tm_to_string(msg.time));
}

int read_message(FILE *fp, Message *msg)
{
    char time[9];

    int res = fscanf(fp, "%*s | %s detectou um incêndio em (%d,%d) as %s\n",
                     msg->source_id,
                     &msg->x,
                     &msg->y,
                     time);

    msg->time = string_to_tm(time);

    return res;
}

/* Verifica se a mensagem informando do incêndio é a primeira recebida pela central */
bool is_mensagem_inedita(FILE *fp, Message msg)
{
    Message aux;

    while (read_message(fp, &aux) != EOF)
    {
        bool is_same_position = (aux.x == msg.x) && (aux.y == msg.y);
        
        int time_diff = _time_diff(msg, aux);

        if (is_same_position && (time_diff <= DELAY_BOMBEIRO))
            return false;
    }

    return true;
}
