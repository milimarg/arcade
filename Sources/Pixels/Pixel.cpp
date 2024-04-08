/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Pixel
*/

#include "Pixel.hpp"

namespace arcade
{
    Pixel::Pixel() :
        _red(0),
        _green(0),
        _blue(0),
        _alpha(255),
        _type(PixelType::DEFAULT),
        _char(' '),
        _texturePath(""),
        _rotation(Rotation::R0),
        _rectSize(0, 0),
        _rectPosition(0, 0)
    {
    }

    Pixel::Pixel(
        Color red,
        Color green,
        Color blue,
        Color alpha,
        PixelType pixelType,
        char charValue,
        const std::string &texturePath,
        Rotation rotation,
        std::pair<int, int> rectSize,
        std::pair<int, int> rectPosition
    ) :
        _red(red),
        _green(green),
        _blue(blue),
        _alpha(alpha),
        _type(pixelType),
        _char(charValue),
        _texturePath(texturePath),
        _rotation(rotation),
        _rectSize(rectSize),
        _rectPosition(rectPosition)
    {
    }

    Pixel::Color Pixel::getRed() const
    {
        return _red;
    }

    Pixel::Color Pixel::getGreen() const
    {
        return _green;
    }

    Pixel::Color Pixel::getBlue() const
    {
        return _blue;
    }

    Pixel::Color Pixel::getAlpha() const
    {
        return _alpha;
    }

    char Pixel::getChar() const
    {
        return _char;
    }

    std::string Pixel::getTexturePath() const
    {
        return _texturePath;
    }

    Pixel::Rotation Pixel::getRotation() const
    {
        return _rotation;
    }

    Pixel::PixelType Pixel::getType() const
    {
        return _type;
    }

    std::pair<int, int> Pixel::getRectSize() const
    {
        return _rectSize;
    }

    std::pair<int, int> Pixel::getRectPosition() const
    {
        return _rectPosition;
    }

    void Pixel::setRed(Color red)
    {
        _red = red;
    }

    void Pixel::setGreen(Color green)
    {
        _green = green;
    }

    void Pixel::setBlue(Color blue)
    {
        _blue = blue;
    }

    void Pixel::setAlpha(Color alpha)
    {
        _alpha = alpha;
    }

    void Pixel::setChar(char charValue)
    {
        _char = charValue;
    }

    void Pixel::setTexturePath(const std::string &path)
    {
        _texturePath = path;
    }

    void Pixel::setRotation(Rotation rotation)
    {
        _rotation = rotation;
    }

    void Pixel::setType(PixelType pixelType)
    {
        _type = pixelType;
    }

    void Pixel::setRectSize(std::pair<int, int> rectSize)
    {
        _rectSize = rectSize;
    }

    void Pixel::setRectPosition(std::pair<int, int> rectPosition)
    {
        _rectPosition = rectPosition;
    }
}
