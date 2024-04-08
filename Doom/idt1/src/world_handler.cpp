/*
** EPITECH PROJECT, 2023
** doom
** File description:
** world_handler.c
*/

#include "../include/my.hpp"

static void set_map_infos(my_idt1 &world, map_type type, int pixel_scale,
    id_Vec2 win_size)
{
    world.pixel_scale = pixel_scale;
    world.win_size = win_size;
    world.opengl_size.x = world.win_size.x * world.pixel_scale;
    world.opengl_size.y = world.win_size.y * world.pixel_scale;
    world.type = type;
    if (world.type == DANTE)
        convert_dante_to_config(world.filepath);
    world.points_len = world.win_size.x * (world.win_size.x - 1) + world.win_size.y;
}

std::unique_ptr<my_idt1> create_world(char *filepath, map_type type, int pixel_scale,
    id_Vec2 win_size)
{
    std::unique_ptr<my_idt1> world = std::make_unique<my_idt1>();
    for (size_t i = 0; i < 360; i++) {
        world->pre_cos[i] = cos(deg_to_rad(i));
        world->pre_sin[i] = sin(deg_to_rad(i));
    }
    world->player = (my_idt1_player){0, 0, 30, 0, 0};
    world->no_spam_key = 0;
    world->filepath = filepath;
    set_map_infos(*world, type, pixel_scale, win_size);
    if (parse_file(*world) == 1)
        return nullptr;
    return (world);
}

void display_world(my_idt1 &world)
{
    std::array<id_Vec3, 4> wpos;

    sort_sectors(world);
    for (int s = 0; s < world.sectors_nb; s++) {
        world.sectors[s].d = 0;
        set_surface_type(world, s);
        for (int loop = 0; loop < 2; loop++) {
            draw_one_wall(world, loop, s, wpos);
            world.sectors[s].d /= world.sectors[s].walls_nb;
            world.sectors[s].surface *= -1;
        }
    }
}
