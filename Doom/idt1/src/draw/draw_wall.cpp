/*
** EPITECH PROJECT, 2023
** doom
** File description:
** draw_wall.c
*/

#include "../../include/my.hpp"

static void update_wall_delimitations(coordinates_wall *wall,
int *delta_x, my_idt1 &world)
{
    *delta_x = (*delta_x == 0) ? 1 : *delta_x;
    wall->x1 = (wall->x1 < 1) ? 1 : wall->x1;
    wall->x2 = (wall->x2 < 1) ? 1 : wall->x2;
    wall->x1 = std::min(world.win_size.x - 1, wall->x1);
    wall->x2 = std::min(world.win_size.x - 1, wall->x2);
}

static void draw_surfaces(my_idt1 &world, int s_and_x[2], int y_array[2],
id_Color color)
{
    int s = s_and_x[0];
    int x = s_and_x[1];

    if (world.sectors[s].surface == BOTTOM * -1) {
        for (int y = world.sectors[s].points_surface[x]; y < y_array[0]; y++)
            draw_point(x, y, world.sectors[s].bottom, world);
    }
    if (world.sectors[s].surface == TOP * -1) {
        for (int y = y_array[1]; y < world.sectors[s].points_surface[x]; y++)
            draw_point(x, y, world.sectors[s].top, world);
    }
    for (int y = y_array[0]; y < y_array[1]; y++) {
        draw_point(x, y, color, world);
    }
}

static int skip_surface_bottom_top(my_idt1 &world, int s_and_x[], int y[2])
{
    int s = s_and_x[0];
    int x = s_and_x[1];

    if (world.sectors[s].surface == BOTTOM) {
        world.sectors[s].points_surface[x] = y[0];
        return (1);
    }
    if (world.sectors[s].surface == TOP) {
        world.sectors[s].points_surface[x] = y[1];
        return (1);
    }
    return (0);
}

void draw_wall(coordinates_wall *wall, id_Color color, int s, my_idt1 &world)
{
    int delta_bottom = wall->bottom2 - wall->bottom1;
    int delta_top = wall->top2 - wall->top1;
    int delta_x = wall->x2 - wall->x1;
    int voila = wall->x1;
    int y[2];

    update_wall_delimitations(wall, &delta_x, world);
    for (int x = wall->x1; x < wall->x2; x++) {
        y[0] = delta_bottom * (x - voila + 0.5) / delta_x + wall->bottom1;
        y[1] = delta_top * (x - voila + 0.5) / delta_x + wall->top1;
        y[0] = (y[0] < 1) ? 1 : y[0];
        y[1] = (y[1] < 1) ? 1 : y[1];
        y[0] = std::min(world.win_size.y - 1, y[0]);
        y[1] = std::min(world.win_size.y - 1, y[1]);
        int data[2] = {s, x};
        if (skip_surface_bottom_top(world, data, y))
            continue;
        draw_surfaces(world, data, y, color);
    }
}

void draw_one_wall(my_idt1 &world, int l, int s, std::array<id_Vec3, 4> &wpos)
{
    std::array<id_Vec2, 2> one_two;
    coordinates_wall wall;

    for (int w = 0; w < world.sectors[s].walls_nb; w++) {
        set_some_points_values(one_two, world, &world.sectors[s].walls[w], l);
        set_wpos_values(wpos, one_two, s, world);
        if (wpos[0].y < 1 && wpos[1].y < 1)
            continue;
        if (wpos[0].y < 1) {
            clip_behind_player(&wpos[0], &wpos[1]);
            clip_behind_player(&wpos[2], &wpos[3]);
        }
        if (wpos[1].y < 1) {
            clip_behind_player(&wpos[1], &wpos[0]);
            clip_behind_player(&wpos[3], &wpos[2]);
        }
        wall = set_walls_pos_depending_of_window_position(wpos, world);
        draw_wall(&wall, world.sectors[s].walls[w].color, s, world);
    }
}
