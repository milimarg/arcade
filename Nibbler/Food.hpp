/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Food
*/

#ifndef FOOD_HPP_
    #define FOOD_HPP_

    #include <unordered_map>
    #include <iostream>
    #include <string>
    #include <vector>
    #include <array>
    #include "Player.hpp"

namespace arcade
{
    /**
     * Food Class
     */
    class Food {
        public:
            /**
             * Food Type
             */
            enum class FoodType {
                DEFAULT,
                RED_FRUIT,
                GREEN_FRUIT,
                YELLOW_FRUIT,
                COOKIE,
                RANDOM
            };

        /**
         * Creates a food
         * @param type type of food
         * @param position position of food on the window
         */
        Food(FoodType type = FoodType::DEFAULT, std::pair<int, int> position = {0, 0});
        ~Food();

            /**
             *
             * @return food type
             */
            FoodType getType() const;

            /**
             *
             * @return food texture coordinates
             */
            std::pair<int, int> getTextureCoords() const;

            /**
             *
             * @return food score
             */
            int getScore() const;

            /**
             *
             * @return food position
             */
            std::pair<int, int> getPosition() const;

            /**
             *
             * @return food color (RGBA)
             */
            std::array<int, 4> getColor() const;

            /**
             * Apply food effect on snake
             * @param snake snake object to apply effect on
             */
            void applyEffect(Player &snake);

            /**
             * Compare 2 Food objects
             * @param food food object to compare with
             * @return is given food object equal?
             */
            bool operator==(const Food &food) const;

        private:
            FoodType _type;
            std::pair<int, int> _textureCoords;
            int _score;
            std::pair<int, int> _position;
            std::array<int, 4> _color;
    };
}

#endif /* !FOOD_HPP_ */
