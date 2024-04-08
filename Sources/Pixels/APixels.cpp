/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** APixels
*/

#include "APixels.hpp"

namespace arcade
{
    APixels::APixels() : _pixelMap({}) {}

    APixels::~APixels() {}

    PixelsMap &APixels::getPixelMap()
    {
        return _pixelMap;
    }

    void APixels::updatePixelMap(const PixelsMap &pixels)
    {
        for (auto &value : pixels) {
            _pixelMap[value.first] = value.second;
        }
    }
}