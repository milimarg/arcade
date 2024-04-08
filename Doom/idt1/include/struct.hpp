/*
** EPITECH PROJECT, 2023
** prototype-raycasting-and-doom_old
** File description:
** struct.h
*/
#ifndef STRUCT_H_
    #define STRUCT_H_
    #include <stdbool.h>
    #include <array>
    #include <vector>
    #include <unordered_map>
    #include "Pair.hpp"
    #define KEY_ACTIONS_NUMBER 10

/* CUSTOM DATA TYPES */

/**
 * Custom Vector2 data type
 */
typedef struct {
    /**
     * x position
     */
    int x;

    /**
     * y position
     */
    int y;
} id_Vec2;

/**
 * Custom Vector3 data type
 */
typedef struct {
    /**
     * x position
     */
    int x;

    /**
     * y position
     */
    int y;

    /**
     * z position
     */
    int z;
} id_Vec3;

/**
 * Custom Color data type
 */
typedef struct {
    /**
     * red value
     */
    unsigned char r;

    /**
     * green value
     */
    unsigned char g;

    /**
     * blue value
     */
    unsigned char b;

    /**
     * alpha value
     */
    unsigned char a;
} id_Color;

/**
 * Custom rect data type
 */
typedef struct {
    /**
     * rect left position
     */
    int left;

    /**
     * rect top position
     */
    int top;

    /**
     * rect width size
     */
    int width;

    /**
     * rect top size
     */
    int height;
} id_rect;

/**
 * Custom vertex data type
 */
typedef struct {
    /**
     * vertex position
     */
    id_Vec2 position;

    /**
     * vertex color
     */
    id_Color color;
} id_vertex;

/* DATA TYPES ENUM */

/**
 * shape type
 */
typedef enum shape_type {
    RECTANGLE = 0,
    TRIANGLE,
} shape_type;

/**
 * wall type
 */
typedef enum wall_type {
    SIDE = 0,
    BOTTOM,
    TOP,
} wall_type;

/* misc */

/**
 * Wall in a sector
 */
typedef struct wall_s {
    /**
    * Point1 in wall
    */
    id_Vec2 point1;
    /**
     * Point2 in wall
     */
    id_Vec2 point2;
    /**
     * Color of wall
     */
    id_Color color;
} wall_t;

/**
* Element in a scene (i.e. a rectangular parallelepiped)
*/
typedef struct sectors_s {
    /**
     * walls number
     */
    int walls_nb;

    /**
     * bottom position on z axis
     */
    int z1;

    /**
     * top positions on z axis
     */
    int z2;

    /**
     * distance between sector and camera
     */
    int d;

    /**
     * top color
     */
    id_Color top;

    /**
     * bottom color
     */
    id_Color bottom;

    /**
     * points surface
     */
    std::unordered_map<int, int> points_surface;

    /**
     * surface value
     */
    int surface;

    /**
     * walls of sector
     */
    std::vector<wall_t> walls;
} sectors_t;

/**
 * map type
 */
typedef enum {
    RAW_CONFIG = 0,
    DANTE,
} map_type;

/**
 * player
 */
typedef struct my_idt1_player {
    /**
     * x position
     */
    float x;

    /**
     * y position
     */
    float y;

    /**
     * z position
     */
    float z;

    /**
     * angle
     */
    int angle;

    /**
     * if camera is bent to the ground (min value) or to the sky (max value)
     */
    int look;
} my_idt1_player;


/**
 * my_idt1
 */
typedef struct my_idt1 {
    /**
     * All pre-calculated values of cos from 0 to 359
     */
    std::array<double, 360> pre_cos;

    /**
     * All pre-calculated values of sin from 0 to 359
     */
    std::array<double, 360> pre_sin;

    /**
     * map filepath
     */
    char *filepath;

    /**
     * avoid spamming certain keys
     */
    int no_spam_key;

    /**
     * number of sectors
     */
    int sectors_nb;

    /**
     * vector of sectors
     */
    std::vector<sectors_t> sectors;

    /**
     * number of points to display
     */
    unsigned int points_len;

    /**
     * map of points to display
     */
    std::unordered_map<std::pair<int, int>, id_vertex> points;

    /**
     * player
     */
    my_idt1_player player;

    /**
     * pixel scale, to manage screen resolution
     */
    int pixel_scale;

    /**
     * input window size
     */
    id_Vec2 win_size;

    /**
     * final window size, scaled using pixel_scale
     */
    id_Vec2 opengl_size;

    /**
     * map type (either raw (from config file) or dante (from dante map))
     */
    map_type type;
} my_idt1;


/**
 * coordinates_wall
 */
typedef struct coordinates_wall {
    /**
     * x1
     */
    int x1;

    /**
     * x2
     */
    int x2;

    /**
     * bottom1
     */
    int bottom1;

    /**
     * bottom2
     */
    int bottom2;

    /**
     * top1
     */
    int top1;

    /**
     * top2
     */
    int top2;
} coordinates_wall;

#endif /*STRUCT_H_*/
