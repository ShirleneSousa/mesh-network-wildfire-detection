#include "map.h"
#include "../utils/utils.h"

void init_mapa()
{
    if (MAP_SIZE % 3 != 0)
    {
        perror("MAP_SIZE deve ser múltiplo de 3!");
        exit(1);
    }

    for (int i = 0; i < MAP_SIZE; i++)
        for (int j = 0; j < MAP_SIZE; j++)
        {
            if ((i % 3 == 1) && (j % 3 == 1))
                mapa[i][j] = 'T';
            else
                mapa[i][j] = '-';
        }
}

void print_mapa()
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            if (mapa[i][j] == '@')
                printf("\033[41m%-1c\033[48;5;28m  \033[0m", mapa[i][j]);
            else
                printf("\033[48;5;28m%-3c\033[0m", mapa[i][j]);
        }
        printf("\n");
    }
}

bool is_cell_empty(int x, int y)
{
    return mapa[x][y] == '-';
}

bool is_cell_on_fire(int x, int y)
{
    return mapa[x][y] == '@';
}

bool is_cell_a_sensor(int x, int y)
{
    return mapa[x][y] == 'T';
}

bool is_in_bounds(int x, int y)
{
    return (x >= 0 && x < MAP_SIZE) && (y >= 0 && y < MAP_SIZE);
}