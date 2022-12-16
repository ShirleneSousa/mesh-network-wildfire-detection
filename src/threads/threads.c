#include "threads.h"
#include "../sensor/sensor.h"
#include "../utils/utils.h"
#include "../data_structures/queue/queue.h"

#include <stdlib.h>
#include <unistd.h>

Queue central_queue;

void create_threads()
{
    pthread_t T[N_THREADS], incendio, central, bombeiro;

    for (int i = 1, k = 0; i < MAP_SIZE; i += 3)
        for (int j = 1; j < MAP_SIZE; j += 3)
        {
            pthread_create(&T[k], NULL, &thread_sensor, sensors[k]);
            k++;
        }

    pthread_create(&incendio, NULL, &thread_incendio, NULL);
    pthread_create(&central, NULL, &thread_central, NULL);
    pthread_create(&bombeiro, NULL, &thread_bombeiro, NULL);
}

static void _send_message_to_central(Message msg)
{
    enqueue(&central_queue, msg); // manda mensagem pra thread central
}

void *thread_sensor(void *arg)
{
    Sensor *T = (Sensor *)arg;
    Message msg;

    while (is_operational(T))
    {
        /* Checar por incendios nos elementos vizinhos */
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
            {
                int cellX = T->x + i;
                int cellY = T->y + j;

                if (is_cell_on_fire(cellX, cellY))
                {
                    msg = create_message(T->id, cellX, cellY);

                    if (is_on_border(T))
                        _send_message_to_central(msg);
                    else
                        broadcast_message(T, msg);
                }
            }

        /* Checar se recebeu mensagens e repassa ela pros vizinhos ou pra central */
        while (!is_empty(T->message_queue))
        {
            msg = dequeue(T->message_queue);

            if (is_on_border(T))
                _send_message_to_central(msg);
            else
                broadcast_message(T, msg);
        }

        sleep(DELAY_SENSOR);
    }

    destroy_sensor(T);
    pthread_exit(NULL);
}

/* Recebe alertas de incêncio e loga os que são inéditos */
void *thread_central(void *arg)
{
    Message msg;
    FILE *fp;

    while (true)
    {
        while (!is_empty(&central_queue))
        {
            msg = dequeue(&central_queue);

            fp = fopen(LOG_PATH, "a+");

            if (is_mensagem_inedita(fp, msg))
                write_message(fp, msg);

            fclose(fp);
        }

    }

    destroy_queue(&central_queue);
    pthread_exit(NULL);
}

/* Apaga incendios indicados pela central após 2 segundos */
void *thread_bombeiro(void *arg)
{
    char log_timestamp[9];
    int x, y;
    FILE *fp;
    int offset = 0;

    /* Checa mensagens da central */
    while (true)
    {
        if (file_exists(LOG_PATH))
        {
            fp = fopen(LOG_PATH, "r");
            fseek(fp, offset, SEEK_SET); // Pula para última posição lida

            while (fscanf(fp, "%s | %*s detectou um incêndio em (%d,%d) as %*s\n", log_timestamp, &x, &y) != EOF)
            {
                int time_diff = time_diff_in_seconds(now(), string_to_tm(log_timestamp));

                if (time_diff == DELAY_BOMBEIRO)
                {
                    mapa[x][y] = '-';   // Apaga incendio
                    offset = ftell(fp); // Salva última posição lida
                }
            }

            fclose(fp);
        }
    }

    pthread_exit(NULL);
}

/* Cria um incendio aleatorio no mapa a cada 5 segundos */
void *thread_incendio(void *arg)
{
    int x, y;
    srand(time(NULL));

    while (true)
    {
        x = rand() % MAP_SIZE;
        y = rand() % MAP_SIZE;

        sleep(DELAY_FOGO);
        mapa[x][y] = '@';
    }
}
