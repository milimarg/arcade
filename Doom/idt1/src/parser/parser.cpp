/*
** EPITECH PROJECT, 2023
** doom
** File description:
** parser.c
*/

#include <sstream>
#include "../../include/my.hpp"

void get_line_info(int index, my_idt1 &world, char *buffer)
{
    std::stringstream stream;
    int pos_x = 0;
    int pos_y = 0;
    int pos_z = 0;
    int size_x = 0;
    int size_y = 0;
    int size_z = 0;
    std::string trash;

    if (index == 0) {
        world.sectors_nb = atoi(buffer);
        for (int i = 0; i < world.sectors_nb; i++) {
            world.sectors.push_back(sectors_t());
        }
    } else {
        stream << buffer;
        stream >> trash >> pos_x >> pos_y >> pos_z >> size_x >> size_y >> size_z;
        id_Vec3 pos = {pos_x, pos_y, pos_z};
        id_Vec3 size = {size_x, size_y, size_z};
        fill_sector(world.sectors[index - 1], RECTANGLE, &pos, &size);
    }
}

int parse_file(my_idt1 &world)
{
    FILE *fd = NULL;
    char *buffer = NULL;
    size_t s = 0;
    int index = 0;
    const char *types[] = {world.filepath, "3d_config"};

    fd = fopen(types[world.type], "r");
    if (fd == NULL) {
        std::cerr << "fd returns NULL" << std::endl;
        return 1;
    }
    while (getline(&buffer, &s, fd) != -1) {
        get_line_info(index, world, buffer);
        index++;
    }
    fclose(fd);
    return 0;
}
