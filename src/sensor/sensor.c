#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static Sensor *_get_sensor_from_coords(int x, int y)
{
    int flat_index = (x / 3) * (MAP_SIZE / 3) + (y / 3);

    Sensor *t = sensors[flat_index];

    return t;
}

static Sensor **_get_neighbors(Sensor *this)
{
    int x = this->x, y = this->y;

    Sensor **neighbours = (Sensor **)malloc(sizeof(Sensor *) * 4);

    if (is_in_bounds(x - 3, y)) // top
        neighbours[0] = _get_sensor_from_coords(x - 3, y);
    if (is_in_bounds(x, y + 3)) // right
        neighbours[1] = _get_sensor_from_coords(x, y + 3);
    if (is_in_bounds(x + 3, y)) // bottom
        neighbours[2] = _get_sensor_from_coords(x + 3, y);
    if (is_in_bounds(x, y - 3)) // left
        neighbours[3] = _get_sensor_from_coords(x, y - 3);

    return neighbours;
}

void broadcast_message(Sensor *this, Message msg)
{
    if (msg.ttl == 0)
        return;

    msg.ttl--;

    Sensor **neighbors = _get_neighbors(this);

    for (int i = 0; i < 4; i++)
    {
        Sensor *t = neighbors[i];

        if (t != NULL && is_in_bounds(t->x, t->y))
            enqueue(t->message_queue, msg);
    }
}

Sensor *create_sensor(int x, int y)
{
    Sensor *this = (Sensor *)malloc(sizeof(Sensor));

    sprintf(this->id, "T%d%d", x, y);
    this->x = x;
    this->y = y;

    this->message_queue = create_queue();

    return this;
}

void init_sensors()
{
    for (int i = 1, k = 0; i < MAP_SIZE; i += 3)
        for (int j = 1; j < MAP_SIZE; j += 3)
            sensors[k++] = create_sensor(i, j);
}

void destroy_sensor(Sensor *t)
{
    destroy_queue(t->message_queue);
    free(t);
}

bool is_on_border(Sensor *t)
{
    return (t->x == 1 || t->x == MAP_SIZE - 2) || (t->y == 1 || t->y == MAP_SIZE - 2);
}

bool is_operational(Sensor *t)
{
    return is_cell_a_sensor(t->x, t->y);
}
