#if !defined(THREADS_H)
#define THREADS_H

void create_threads();

void *thread_sensor(void *arg);

void *thread_central(void *arg);

void *thread_bombeiro(void *arg);

void *thread_incendio(void *arg);

#endif // THREADS_H
