/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Bullet.hpp
*/

#ifndef B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_BULLET_HPP
    #define B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_BULLET_HPP
    #include "Enemy.hpp"

/**
 * Bullet Class
 */
class Bullet : public arcade::Enemy {
public:
    Bullet() : _status(false) {}
    ~Bullet() {}

    /**
     *
     * @return is bullet active?
     */
    bool isActive() const { return _status; }

    /**
     *
     * @return Bullet orientation
     */
    Orientation getOrientation() const { return _orientation; }

    /**
     *
     * @return bullet max X
     */
    int getMaxX() const { return max_x; }

    /**
     *
     * @return bullet max Y
     */
    int getMaxY() const { return max_y; }

    /**
     * Sets status of bullet
     * @param status status of bullet
     */
    void setStatus(bool status) { _status = status; }

    /**
     * Sets orientation of bullet
     * @param orientation orientation of bullet
     */
    void setOrientation(Orientation orientation) { _orientation = orientation; }

    /**
     * Sets max X of bullet
     * @param x max X of bullet
     */
    void setMaxX(int x) { max_x = x; }

    /**
     * Sets max Y of bullet
     * @param y max Y of bullet
     */
    void setMaxY(int y) { max_y = y; }

private:
    bool _status;
    Orientation _orientation;
    int max_x;
    int max_y;
};

#endif /* B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_BULLET_HPP */
