/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Enemy.hpp
*/

#ifndef B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_ENTITY_HPP
    #define B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_ENTITY_HPP
    #include "Pixel.hpp"

namespace arcade {
    /**
     * Entity Class
     */
    class Entity {
    public:
        /**
         * Entity Orientation
         */
        enum class Orientation {
            HORIZONTAL,
            VERTICAL
        };

        /**
         * Entity Direction
         */
        enum class Direction {
            LEFT,
            RIGHT,
            UP,
            DOWN,
            NONE
        };

        Entity() : _x(0), _y(0), _width(1), _height(1), _ref(Pixel(255, 255, 255)) {}
        ~Entity() {}

        /**
         *
         * @return X position
         */
        int getX() const { return _x; }

        /**
         *
         * @return Y position
         */
        int getY() const { return _y; }

        /**
         *
         * @return width size
         */
        int getWidth() const { return _width; }

        /**
         *
         * @return height size
         */
        int getHeight() const { return _height; }

        /**
         *
         * @return color
         */
        Pixel getRef() const { return _ref; }

        /**
         *
         * @return shift (old orientation)
         */
        int getShift() const { return _shift; }

        /**
         *
         * @return orientation
         */
        Orientation getOrientation() const { return _orientation; }

        /**
         *
         * @return direction
         */
        Direction getDirection() const { return _direction; }

        /**
         *
         * @param x Position X
         */
        void setX(int x) { _x = x; }

        /**
         *
         * @param y Position Y
         */
        void setY(int y) { _y = y; }

        /**
         *
         * @param width Width size
         */
        void setWidth(int width) { _width = width; }

        /**
         *
         * @param height Height size
         */
        void setHeight(int height) { _height = height; }

        /**
         *
         * @param pixel Color
         */
        void setRef(Pixel pixel) { _ref = pixel; }

        /**
         *
         * @param shift Shift (old orientation)
         */
        void setShift(int shift) { _shift = shift; }

        /**
         *
         * @param orientation Orientation
         */
        void setOrientation(Orientation orientation) { _orientation = orientation; }

        /**
         *
         * @param direction Direction
         */
        void setDirection(Direction direction) { _direction = direction; }
    private:
        int _x;
        int _y;
        int _width;
        int _height;
        Pixel _ref;
        int _shift;
        Orientation _orientation;
        Direction _direction;
    };
}

#endif /* B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_ENTITY_HPP */
