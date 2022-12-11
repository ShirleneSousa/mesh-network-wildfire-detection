#if !defined(MAPA_H)
#define MAPA_H

#include <stdbool.h>
#include "../constants.h"

extern char mapa[MAP_SIZE][MAP_SIZE];

void init_mapa();
void print_mapa();

bool is_cell_empty(int x, int y);
bool is_cell_on_fire(int x, int y);
bool is_cell_a_sensor(int x, int y);
bool is_in_bounds(int x, int y);

#endif // MAPA_H
