/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Score
*/

#include "Score.hpp"

namespace arcade
{
    Score::Score(const std::string &playerName, int scoreValue) : _playerName(playerName), _scoreValue(scoreValue) {}

    std::string Score::getPlayerName() const
    {
        return _playerName;
    }

    void Score::setPlayerName(const std::string &newName)
    {
        _playerName = newName;
    }

    int Score::getScoreValue() const
    {
        return _scoreValue;
    }

    void Score::setScoreValue(int newValue)
    {
        _scoreValue = newValue;
    }
}
