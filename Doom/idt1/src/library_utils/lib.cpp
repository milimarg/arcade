/*
** EPITECH PROJECT, 2023
** doom
** File description:
** library_utils.c
*/

#include "../../include/my.hpp"

void my_put_nbr_fd(int nb, unsigned int fd)
{
    char c = 0;

    if (nb == 0) {
        write(fd, "0", 1);
        return;
    }
    if (nb < 0) {
        write(fd, "-", 1);
        nb *= -1;
    }
    if (nb > 9)
        my_put_nbr_fd(nb / 10, fd);
    c = nb % 10 + '0';
    write(fd, &c, 1);
}

void my_swap(int *a, int *b)
{
    int c = 0;

    c = *a;
    *a = *b;
    *b = c;
}

int my_array_len(char **array)
{
    int i = 0;

    for (; array[i] != NULL; i++);
    return (i);
}
