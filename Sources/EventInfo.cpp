/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** EventInfo
*/

#include "EventInfo.hpp"

namespace arcade
{
    EventInfo::EventInfo() : _mouseCoords({}), _key(Key::NONE), _changeKey(ChangeKey::NONE) {}
    EventInfo::EventInfo(const Key &key) : _mouseCoords({}), _key(key), _changeKey(ChangeKey::NONE) {}
    EventInfo::EventInfo(const Key &key, const std::pair<int, int> &mouseCoords) : _mouseCoords(mouseCoords), _key(key), _changeKey(ChangeKey::NONE) {}
    EventInfo::EventInfo(const ChangeKey &key) : _mouseCoords({}), _key(Key::NONE), _changeKey(key) {}

    std::pair<int, int> EventInfo::getMouseCoords() const
    {
        return _mouseCoords;
    }

    Key EventInfo::getKey() const
    {
        return _key;
    }

    ChangeKey EventInfo::getChangeKey() const
    {
        return _changeKey;
    }

    void EventInfo::setMouseCoords(const std::pair<int, int> &coords)
    {
        _mouseCoords = coords;
    }

    void EventInfo::setKey(const Key &key)
    {
        _key = key;
    }

    void EventInfo::setChangeKey(const ChangeKey &key)
    {
        _changeKey = key;
    }
}
