/*
** EPITECH PROJECT, 2023
** doom
** File description:
** move_strafe.c
*/

#include "../../include/my.hpp"

void strafe_left(my_idt1 &world, id_Vec2 *delta)
{
    world.player.x += delta->x;
    world.player.y -= delta->y;
}

void strafe_right(my_idt1 &world, id_Vec2 *delta)
{
    world.player.x -= delta->x;
    world.player.y += delta->y;
}
