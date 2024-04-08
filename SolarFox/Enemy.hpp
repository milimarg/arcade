/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Enemy.h
*/

#ifndef B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_ENEMY_H
    #define B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_ENEMY_H
    #include "Entity.hpp"

namespace arcade
{
    /**
     * Enemy Class
     */
    class Enemy : public Entity {
    public:
        Enemy() {
            setShift(1);
        }
        ~Enemy() {}
    private:
    };
}

#endif /* B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_ENEMY_H */
