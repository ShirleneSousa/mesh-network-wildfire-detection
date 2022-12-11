#if !defined(UTILS_H)
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

FILE *create_file(const char *path, const char *mode);

bool file_exists(const char *path);

struct tm *now();
char *tm_to_string(struct tm *tm);
struct tm *string_to_tm(char str[9]);

int time_diff_in_seconds(struct tm *t1, struct tm *t2);

#endif // UTILS_H
