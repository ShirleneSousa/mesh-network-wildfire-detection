#include "./map/map.h"
#include "./threads/threads.h"
#include "./sensor/sensor.h"

#include <unistd.h>
#include <stdlib.h>

char mapa[MAP_SIZE][MAP_SIZE];
Sensor *sensors[N_THREADS];

int main(int argc, char const *argv[])
{
    init_mapa();
    init_sensors();
    create_threads();

    while (true)
    {
        system("clear");
        print_mapa();

        sleep(DELAY_SENSOR);
    }

    pthread_exit(NULL);

    return 0;
}
