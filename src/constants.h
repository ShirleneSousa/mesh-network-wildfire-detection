#if !defined(CONSTANTS_H)
#define CONSTANTS_H

#define MAP_SIZE 15
#define N_THREADS ((MAP_SIZE / 3) * (MAP_SIZE / 3))

#define TTL MAP_SIZE / 2

/* Delays */
#define DELAY_SENSOR 1
#define DELAY_FOGO 5
#define DELAY_BOMBEIRO 2

/* Paths */
#define LOG_PATH "incendios.log"

#endif // CONSTANTS_H
