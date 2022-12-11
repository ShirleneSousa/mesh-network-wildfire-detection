#if !defined(SENSOR_H)
#define SENSOR_H

#include "../queue/queue.h"
#include "../map/map.h"
#include "../message/message.h"

typedef struct __sensor
{
    char id[5];
    int x, y;
    struct __sensor *neighbors[4];
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
