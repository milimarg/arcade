/*
** EPITECH PROJECT, 2023
** doom
** File description:
** move_player.c
*/

#include "../../include/my.hpp"

void move_player(my_idt1 &world, std::array<bool, KEY_ACTIONS_NUMBER> &key_actions)
{
    static void (*functions[])(my_idt1 &, id_Vec2 *) = {&move_front,
    &move_back, &turn_left, &turn_right, &go_up, &go_down, &lean_to_ground,
    &lean_to_sky, &strafe_left, &strafe_right};
    id_Vec2 delta = {
            (int)(world.pre_sin[world.player.angle] * 10.0),
            (int)(world.pre_cos[world.player.angle] * 10.0)
    };

    for (auto it = key_actions.begin(); it != key_actions.end(); it += 1) {
        size_t index = it - key_actions.begin();
        if (key_actions[index])
            functions[index](world, &delta);
    }
}
