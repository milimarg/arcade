/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** ATexts
*/

#include "ATexts.hpp"

namespace arcade
{
    ATexts::ATexts() : _textMap({}) {}

    ATexts::~ATexts() {}

    TextMap &ATexts::getTextMap()
    {
        return _textMap;
    }

    void ATexts::updateTextMap(const TextMap &texts)
    {
        for (auto &value : texts) {
            _textMap[value.first] = value.second;
        }
    }
}
