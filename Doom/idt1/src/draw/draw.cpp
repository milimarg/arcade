/*
** EPITECH PROJECT, 2023
** doom
** File description:
** draw.c
*/

#include "../../include/my.hpp"

void clear_points(my_idt1 &world)
{
    world.points.clear();
}

void draw_point(int x, int y, id_Color color, my_idt1 &world)
{
    world.points[{x, y}] = (id_vertex){.position = {x, y}, .color = color};
}
