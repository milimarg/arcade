/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Player
*/

#include "Player.hpp"

namespace arcade
{
    Player::Player([[maybe_unused]] std::size_t size, Player::Direction direction, float moveSpeed) :
        _body(),
        _isDead(false),
        _direction(direction),
        _nextDirection(direction),
        _defaultMoveSpeed(moveSpeed),
        _currentMoveSpeed(moveSpeed),
        _changedMoveSpeed(moveSpeed),
        _isReversed(false),
        _reversedTimeBank(-1.0f),
        _speedChangeTimeBank(-1.0f),
        _speedIncreaseTimeBank(0.0f)
    {
    }

    Player::~Player()
    {
    }

    void Player::init(std::pair<int, int> position)
    {
        _body.push_back({position.first, position.second});
        _currentMoveSpeed = _defaultMoveSpeed;
        _changedMoveSpeed = _currentMoveSpeed;
    }

    void Player::setIsDead(bool state)
    {
        _isDead = state;
    }

    void Player::setDirection(Direction direction)
    {
        _direction = direction;
    }

    void Player::setNextDirection(Direction direction)
    {
        _nextDirection = direction;
    }

    bool Player::getIsDead() const
    {
        return _isDead;
    }

    Player::Direction Player::getDirection() const
    {
        return _direction;
    }

    std::deque<std::pair<int, int>> Player::getBody() const
    {
        return _body;
    }

    std::pair<int, int> Player::getHead() const
    {
        return _body.front();
    }

    std::deque<std::pair<int, int>>::const_iterator Player::getTailIt() const
    {
        return std::next(_body.begin());
    }

    std::deque<std::pair<int, int>>::const_iterator Player::getEndIt() const
    {
        return _body.end();
    }

    float Player::getMoveSpeed() const
    {
        return _changedMoveSpeed;
    }

    bool Player::getIsReversed() const
    {
        return _isReversed;
    }

    void Player::addBodyPart(int n)
    {
        for (int i = 0; i < n; ++i)
            _body.push_back(_body.back());
    }

    void Player::resetBody()
    {
        _body.clear();
    }

    void Player::setMoveSpeed(float moveSpeed, float duration)
    {
        _changedMoveSpeed = moveSpeed;
        _speedChangeTimeBank = duration;
    }

    void Player::resetMoveSpeed()
    {
        _changedMoveSpeed = _currentMoveSpeed;
    }

    void Player::setIsReversed(bool isReversed)
    {
        _isReversed = isReversed;
        if (_isReversed == true)
            _reversedTimeBank = 5.0f;
    }

    void Player::updatePosition()
    {
        _direction = _nextDirection;

        int newHeadX = _body.front().first;
        int newHeadY = _body.front().second;

        switch (_direction) {
            case Direction::UP:
                newHeadY--;
                break;
            case Direction::DOWN:
                newHeadY++;
                break;
            case Direction::LEFT:
                newHeadX--;
                break;
            case Direction::RIGHT:
                newHeadX++;
                break;
            default:
                break;
        }

        _body.push_front({newHeadX, newHeadY});
        _body.pop_back();
    }

    void Player::updateTime(float deltaTime)
    {
        _speedIncreaseTimeBank += deltaTime;
        if (_speedIncreaseTimeBank >= 0.5f) {
            _speedIncreaseTimeBank -= 0.5f;
            _currentMoveSpeed -= 0.0001;
        }

        _reversedTimeBank -= deltaTime;
        if (_reversedTimeBank <= 0.0f)
            _isReversed = false;

        _speedChangeTimeBank -= deltaTime;
        if (_speedChangeTimeBank <= 0.0f)
            _changedMoveSpeed = _currentMoveSpeed;
    }

    bool Player::collideWithBody(std::pair<int, int> position) const
    {
        for (auto it = std::next(_body.begin()); it != _body.end(); ++it)
            if (*it == position)
                return true;
        return false;
    }
}
