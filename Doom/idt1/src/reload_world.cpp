/*
** EPITECH PROJECT, 2023
** doom
** File description:
** reload_world.c
*/

#include "../include/my.hpp"

int reload_world(my_idt1 &world, char *filepath, bool isReloadKeyPressed)
{
    if (isReloadKeyPressed && !world.no_spam_key) {
        world.no_spam_key = 1;
        std::cout << "Updating world's matrix..." << std::endl;
        world.filepath = filepath;
        convert_dante_to_config(world.filepath);
        if (parse_file(world) == 1)
            return 1;
    }
    if (!isReloadKeyPressed && world.no_spam_key) {
        world.no_spam_key = 0;
    }
    return 0;
}
