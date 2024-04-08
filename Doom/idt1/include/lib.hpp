/*
** EPITECH PROJECT, 2023
** prototype-raycasting-and-doom_old
** File description:
** library_utils.h
*/
#ifndef LIB_H_
    #define LIB_H_
void my_put_nbr_fd(int nb, unsigned int fd);
int fix_angle(int angle);
int calc_dist(int x1,int y1, int x2,int y2);
void my_swap(int *a, int *b);
int my_array_len(char **array);
void sort_sectors(my_idt1 &world);
#endif /*LIB_H_*/
