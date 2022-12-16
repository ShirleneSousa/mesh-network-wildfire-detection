#include "message.h"
#include "../utils/utils.h"
#include "../constants.h"
#include <string.h>
#include <stdbool.h>
#include <pthread.h>

static int _time_diff(Message m1, char aux_time[9])
{
    struct tm *t1 = string_to_tm(m1.time);
    struct tm *t2 = string_to_tm(aux_time);

    int t1_sec = t1->tm_hour * 3600 + t1->tm_min * 60 + t1->tm_sec;
    int t2_sec = t2->tm_hour * 3600 + t2->tm_min * 60 + t2->tm_sec;

    int diff = t1_sec - t2_sec;

    return diff;
}

Message create_message(char *source_id, int x, int y)
{
    Message msg;

    strcpy(msg.source_id, source_id);
    msg.x = x;
    msg.y = y;
    strcpy(msg.time, tm_to_string(now()));

    msg.visits = create_list();

    return msg;
}

void write_message(FILE *fp, Message msg)
{
    fprintf(fp, "%s | %s detectou um incêndio em (%d,%d) as %s\n",
            tm_to_string(now()),
            msg.source_id,
            msg.x,
            msg.y,
            msg.time);
}

int read_message(FILE *fp, char *log_timestamp, Message *msg)
{
    int res = fscanf(fp, "%s | %s detectou um incêndio em (%d,%d) as %s\n",
                     log_timestamp,
                     msg->source_id,
                     &msg->x,
                     &msg->y,
                     msg->time);

    return res;
}

/* Verifica se a mensagem informando do incêndio é a primeira recebida pela central */
bool is_mensagem_inedita(FILE *fp, Message msg)
{
    Message aux;
    char aux_log_timestamp[9];


    while (read_message(fp, aux_log_timestamp, &aux) != EOF)
    {
        bool is_same_position = (aux.x == msg.x) && (aux.y == msg.y);

        int time_diff = _time_diff(msg, aux_log_timestamp);

        if (is_same_position && (time_diff <= DELAY_BOMBEIRO))
            return false;
    }

    return true;
}

void add_visit(Message msg, char *sensor_id)
{
    add_node(msg.visits, sensor_id);
}

bool was_visited(Message msg, char *sensor_id)
{
    return contains(msg.visits, sensor_id);
}