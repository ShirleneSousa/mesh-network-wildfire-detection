#if !defined(SENSOR_H)
#define SENSOR_H

#include "../data_structures/queue/queue.h"
#include "../map/map.h"

typedef struct _sensor
{
    char id[5];
    int x, y;
    Queue *message_queue;
} Sensor;

extern Sensor *sensors[N_THREADS];

void init_sensors();

void destroy_sensor(Sensor *t);

Sensor *create_sensor(int x, int y);

void broadcast_message(Sensor *this, Message msg);

bool is_on_border(Sensor *t);

bool is_operational(Sensor *t);

#endif // SENSOR_H
