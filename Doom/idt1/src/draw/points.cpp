/*
** EPITECH PROJECT, 2023
** doom
** File description:
** points.c
*/

#include "../../include/my.hpp"

void set_some_points_values(std::array<id_Vec2, 2> &one_two, my_idt1 &world,
wall_t *wall, int loop)
{
    one_two[0].x = wall->point1.x - world.player.x;
    one_two[0].y = wall->point1.y - world.player.y;
    one_two[1].x = wall->point2.x - world.player.x;
    one_two[1].y = wall->point2.y - world.player.y;
    if (loop == 0) {
        my_swap(&one_two[0].x, &one_two[1].x);
        my_swap(&one_two[0].y, &one_two[1].y);
    }
}

coordinates_wall set_walls_pos_depending_of_window_position(std::array<id_Vec3, 4> &wpos,
my_idt1 &world)
{
    int shift = 200;
    coordinates_wall wall;

    wpos[0].x = wpos[0].x * shift / wpos[0].y + (world.win_size.x / 2);
    wpos[0].y = wpos[0].z * shift / wpos[0].y + (world.win_size.y / 2);
    wpos[1].x = wpos[1].x * shift / wpos[1].y + (world.win_size.x / 2);
    wpos[1].y = wpos[1].z * shift / wpos[1].y + (world.win_size.y / 2);
    wpos[2].x = wpos[2].x * shift / wpos[2].y + (world.win_size.x / 2);
    wpos[2].y = wpos[2].z * shift / wpos[2].y + (world.win_size.y / 2);
    wpos[3].x = wpos[3].x * shift / wpos[3].y + (world.win_size.x / 2);
    wpos[3].y = wpos[3].z * shift / wpos[3].y + (world.win_size.y / 2);
    wall = (coordinates_wall){wpos[0].x, wpos[1].x, wpos[0].y, wpos[1].y,
    wpos[2].y, wpos[3].y};
    return (wall);
}
