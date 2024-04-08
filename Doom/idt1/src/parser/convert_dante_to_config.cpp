/*
** EPITECH PROJECT, 2023
** doom
** File description:
** convert_dante_to_config.c
*/

#include "../../include/my.hpp"

static void error_handling_file(char *filepath, struct stat *st)
{
    if (stat(filepath, st) == -1) {
        std::cerr << "can't open dante file (stat)" << std::endl;
    }
    if (st->st_size == 0) {
        std::cerr << "dante file is empty" << std::endl;
    }
}

static void get_map_size(int *fd, char *buffer, id_Vec2 *map_size,
std::array<int, 2> &walls_sectors_nb)
{
    int count_width = 1;

    *fd = open("3d_config", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (*fd == -1) {
        std::cerr << "can't create/open 3d config" << std::endl;
    }
    for (int i = 0; buffer[i] != '\0'; i++) {
        if (count_width)
            map_size->x++;
        if (buffer[i] == '\n') {
            map_size->y++;
            count_width = 0;
        }
        if (buffer[i] == 'X')
            walls_sectors_nb[0] += 1;
    }
    map_size->y++;
}

static void print_config_wall(char char_to_check, id_Vec2 *index,
std::array<int, 2> &walls_sectors_nb, int fd)
{
    static int a = 0;
    static int texture_size = 8;
    static int texture_size_sq = 0;
    int values[] = {index->x * texture_size_sq, index->y * texture_size_sq, 0,
    texture_size_sq, texture_size_sq, texture_size_sq};

    if (!a) {
        a = 1;
        texture_size_sq = texture_size * texture_size;
    }
    if (char_to_check == 'X') {
        write(fd, "rectangle ", 10);
        for (int i = 0; i < 6; i++) {
            my_put_nbr_fd(values[i], fd);
            write(fd, " ", 1);
        }
        write(fd, (walls_sectors_nb[1] == walls_sectors_nb[0]) ? "" : "\n", 1);
        walls_sectors_nb[1]++;
    }
    a = (walls_sectors_nb[1] == walls_sectors_nb[0]) ? 0 : a;
}

static void print_config_lines(id_Vec2 *map_size, char *buffer, int fd,
std::array<int, 2> &walls_sectors_nb)
{
    int pos = 0;

    id_Vec2 index;
    my_put_nbr_fd(walls_sectors_nb[0], fd);
    write(fd, "\n", 1);
    for (index.y = 0; index.y < map_size->y; index.y++) {
        for (index.x = 0; index.x < map_size->x; index.x++) {
            pos = index.y * map_size->x + index.x;
            print_config_wall(buffer[pos], &index, walls_sectors_nb, fd);
        }
    }
}

void convert_dante_to_config(char *filepath)
{
    int fd = 0;
    struct stat st;
    id_Vec2 map_size;
    char buffer[131072] = {0};
    std::array<int, 2> walls_sectors_nb = {0};

    error_handling_file(filepath, &st);
    fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        std::cerr << "can't open dante file (open)" << std::endl;
    }
    read(fd, buffer, 131071);
    close(fd);
    get_map_size(&fd, buffer, &map_size, walls_sectors_nb);
    print_config_lines(&map_size, buffer, fd, walls_sectors_nb);
    close(fd);
}
