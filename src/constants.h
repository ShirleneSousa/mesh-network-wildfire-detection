#if !defined(CONSTANTS_H)
#define CONSTANTS_H

#define MAP_SIZE 15
#define N_THREADS ((MAP_SIZE / 3) * (MAP_SIZE / 3))

#define QUEUE_MAX_SIZE (MAP_SIZE * MAP_SIZE)
#define TTL MAP_SIZE

/* Delays */
#define DELAY_SENSOR 1
#define DELAY_FOGO 2
#define DELAY_BOMBEIRO 2

/* Paths */
#define LOG_PATH "incendios.log"

#endif // CONSTANTS_H
