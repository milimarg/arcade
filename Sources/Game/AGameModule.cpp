/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** AGame
*/

#include "AGameModule.hpp"

namespace arcade
{
    AGameModule::AGameModule(std::string name) : _pixels(nullptr), _texts(nullptr), _name(name)
    {
    }

    AGameModule::~AGameModule()
    {
    }

    std::string AGameModule::getName() const
    {
        return _name;
    }

    IPixels *AGameModule::getPixelsWrapper()
    {
        return _pixels.get();
    }

    ITexts *AGameModule::getTextsWrapper()
    {
        return _texts.get();
    }

    IPixels *AGameModule::createPixelsObject()
    {
        _pixels = std::make_unique<Pixels>();
        return _pixels.get();
    }

    ITexts *AGameModule::createTextsObject()
    {
        _texts = std::make_unique<Texts>();
        return _texts.get();
    }
}
