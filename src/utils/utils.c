#include "utils.h"
#include <stdlib.h>
#include <pthread.h>
#include <sys/stat.h>

/* |──────────────────────────────────────────────| File Manipulation |──────────────────────────────────────────────|*/

FILE *create_file(const char *path, const char *mode)
{
    remove(path);

    FILE *fp = fopen(path, mode);

    return fp;
}

bool file_exists(const char *path)
{
    struct stat buffer;
    return (stat(path, &buffer) == 0);
}

/* |─────────────────────────────────────────────────────| Time |────────────────────────────────────────────────────|*/

struct tm *now()
{
    time_t t = time(NULL);
    return localtime(&t);
}

char *tm_to_string(struct tm *tm)
{
    char *str = malloc(9 * sizeof(char));
    sprintf(str, "%.2d:%.2d:%.2d", tm->tm_hour, tm->tm_min, tm->tm_sec);

    return str;
}

struct tm *string_to_tm(char str[9])
{
    struct tm *tm = malloc(sizeof(struct tm));

    sscanf(str, "%d:%d:%d", &tm->tm_hour, &tm->tm_min, &tm->tm_sec);

    return tm;
}

int time_diff_in_seconds(struct tm *t1, struct tm *t2)
{
    return (t1->tm_sec - t2->tm_sec) +
           (t1->tm_min - t2->tm_min) * 60 +
           (t1->tm_hour - t2->tm_hour) * 3600;
}