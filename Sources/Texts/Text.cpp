/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Text
*/

#include "Text.hpp"

namespace arcade
{
    Text::Text() :
        _str(""),
        _red(0),
        _green(0),
        _blue(0),
        _alpha(255)
    {
    }

    Text::Text(
        const std::string &str) :
        _str(str),
        _red(0),
        _green(0),
        _blue(0),
        _alpha(255)
    {
    }

    Text::Text(
        const std::string &str,
        Color red,
        Color green,
        Color blue,
        Color alpha
    ) :
        _str(str),
        _red(red),
        _green(green),
        _blue(blue),
        _alpha(alpha)
    {
    }

    Text::Color Text::getRed() const
    {
        return _red;
    }

    Text::Color Text::getGreen() const
    {
        return _green;
    }

    Text::Color Text::getBlue() const
    {
        return _blue;
    }

    Text::Color Text::getAlpha() const
    {
        return _alpha;
    }

    std::string Text::getStr() const
    {
        return _str;
    }

    void Text::setRed(Color red)
    {
        _red = red;
    }

    void Text::setGreen(Color green)
    {
        _green = green;
    }

    void Text::setBlue(Color blue)
    {
        _blue = blue;
    }

    void Text::setAlpha(Color alpha)
    {
        _alpha = alpha;
    }

    void Text::setStr(const std::string &str)
    {
        _str = str;
    }
}
