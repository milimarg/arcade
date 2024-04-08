/*
** EPITECH PROJECT, 2023
** doom
** File description:
** walls.c
*/

#include "../include/my.hpp"

void set_surface_type(my_idt1 &world, int s)
{
    if (world.player.z < world.sectors[s].z1) {
        world.sectors[s].surface = BOTTOM;
    } else if (world.player.z > world.sectors[s].z2) {
        world.sectors[s].surface = TOP;
    } else {
        world.sectors[s].surface = SIDE;
    }
}

void set_wpos_values(std::array<id_Vec3, 4> &wpos, std::array<id_Vec2, 2> &one_two,
int s, my_idt1 &world)
{
    float current_cos = world.pre_cos[world.player.angle];
    float current_sin = world.pre_sin[world.player.angle];

    wpos[0].x = one_two[0].x * current_cos - one_two[0].y * current_sin;
    wpos[1].x = one_two[1].x * current_cos - one_two[1].y * current_sin;
    wpos[2].x = wpos[0].x;
    wpos[3].x = wpos[1].x;
    wpos[0].y = one_two[0].y * current_cos + one_two[0].x * current_sin;
    wpos[1].y = one_two[1].y * current_cos + one_two[1].x * current_sin;
    wpos[2].y = wpos[0].y;
    wpos[3].y = wpos[1].y;
    world.sectors[s].d += calc_dist(0, 0, (wpos[0].x + wpos[1].x) / 2,
    (wpos[0].y + wpos[1].y) / 2);
    wpos[0].z = world.sectors[s].z1 - world.player.z +
    ((world.player.look * wpos[0].y) / 32.0);
    wpos[1].z = world.sectors[s].z1 - world.player.z +
    ((world.player.look * wpos[1].y) / 32.0);
    wpos[2].z = wpos[0].z + world.sectors[s].z2;
    wpos[3].z = wpos[1].z + world.sectors[s].z2;
}
