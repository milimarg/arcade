/*
** EPITECH PROJECT, 2023
** doom
** File description:
** utils.c
*/

#include "../../include/my.hpp"

int fix_angle(int angle)
{
    angle += (angle < 0) ? 360 : 0;
    angle -= (angle > 359) ? 360 : 0;
    return (angle);
}

int calc_dist(int x1, int y1, int x2,int y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

bool compare(sectors_t *a, sectors_t *b)
{
    return a->d >= b->d;
}

void sort_sectors(my_idt1 &world)
{
    for (int i = 0; i < world.sectors_nb - 1; i++) {
        for (int j = 0; j < world.sectors_nb - i - 1; j++) {
            sectors_t &a = world.sectors[j];
            sectors_t &b = world.sectors[j + 1];
            if (a.d >= b.d)
                continue;
            std::swap(world.sectors[j], world.sectors[j + 1]);
        }
    }
}
