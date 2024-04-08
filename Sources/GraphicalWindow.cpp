/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** GraphicalWindow
*/

#include "GraphicalWindow.hpp"

namespace arcade
{
    GraphicalWindow::GraphicalWindow()
    :
    _currentPixelSizeX(1),
    _currentPixelSizeY(1)
    {}

    int GraphicalWindow::getCurrentPixelSizeX() const
    {
        return _currentPixelSizeX;
    }

    int GraphicalWindow::getCurrentPixelSizeY() const
    {
        return _currentPixelSizeY;
    }
}
