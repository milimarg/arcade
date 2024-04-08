/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Rect.hpp
*/

#ifndef B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_RECT_HPP
    #define B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_RECT_HPP
    #include "Vec2.hpp"

/**
 * Rect Class
 */
class Rect {
public:
    Rect();

    /**
     * Creates rectangle
     * @param top top side
     * @param left left side
     * @param width width
     * @param height height
     */
    Rect(int top, int left, int width, int height)
        : _top(top), _left(left), _width(width), _height(height) {}

    /**
     * Creates rectangle
     * @param pos position vector
     * @param size size vector
     */
    Rect(const Vec2 &pos, const Vec2 &size)
        : _top(pos.getY()), _left(pos.getX()), _width(size.getX()), _height(size.getY()) {}
    ~Rect();

    /**
     *
     * @return top position
     */
    int getTop() const { return _top; }

    /**
     *
     * @return left position
     */
    int getLeft() const { return _left; }

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
     * Sets top position
     * @param top new top position
     */
    void setTop(int top) { _top = top; }

    /**
     * Sets left position
     * @param left new left position
     */
    void setLeft(int left) { _left = left; }

    /**
     * Sets width size
     * @param width new width size
     */
    void setWidth(int width) { _width = width; }

    /**
     * Sets height size
     * @param height new height size
     */
    void setHeight(int height) { _height = height; }

private:
    int _top;
    int _left;
    int _width;
    int _height;
};

#endif //B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_RECT_HPP
