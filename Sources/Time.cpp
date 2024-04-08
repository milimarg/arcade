/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** Time
*/

#include "Time.hpp"

namespace arcade {
    Time::Time() : _startTime(std::chrono::steady_clock::now()), _previousTime(_startTime)
    {
        update();
    }

    void Time::update()
    {
        _currentTime = std::chrono::steady_clock::now();
        _deltaTime = std::chrono::duration_cast<std::chrono::duration<float>>(_currentTime - _previousTime).count();
        _previousTime = _currentTime;
    }

    float Time::getTime() const
    {
        return std::chrono::duration_cast<std::chrono::duration<float>>(_currentTime - _startTime).count();
    }

    float Time::getDeltaTime() const
    {
        return _deltaTime;
    }
}
