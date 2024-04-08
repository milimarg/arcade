/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Vec2.hpp
*/

#ifndef B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_VEC2_HPP
    #define B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_VEC2_HPP

/**
 * Vec2 Class
 */
class Vec2 {
public:
    Vec2();
    ~Vec2();

    /**
     *
     * @return x position
     */
    int getX() const { return _x; }

    /**
     *
     * @return y position
     */
    int getY() const { return _y; }

    /**
     * Sets x position
     * @param x new x position
     */
    void setX(int x) { _x = x; }

    /**
     * Sets y position
     * @param y new y position
     */
    void setY(int y) { _y = y; }

private:
    int _x;
    int _y;
};

#endif //B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_VEC2_HPP
