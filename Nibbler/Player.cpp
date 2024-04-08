/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Player
*/

#include "Player.hpp"

namespace arcade
{
    Player::Player(std::size_t size, Player::Direction direction, float moveSpeed) :
        _body(),
        _isDead(false),
        _direction(direction),
        _nextDirection(direction),
        _baseMoveSpeed(moveSpeed),
        _moveSpeed(moveSpeed),
        _isReversed(false),
        _reversedTimeBank(-1.0f),
        _speedChangeTimeBank(-1.0f),
        _isStopped(false),
        _isBlocked(false)
    {
    }

    Player::~Player()
    {
    }

    void Player::init(std::pair<int, int> position)
    {
        _body.push_back({position.first, position.second});
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
        return _moveSpeed;
    }

    bool Player::getIsReversed() const
    {
        return _isReversed;
    }

    bool Player::getIsStopped() const
    {
        return _isStopped;
    }

    bool Player::getIsBlocked() const
    {
        return _isBlocked;
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
        _moveSpeed = moveSpeed;
        _speedChangeTimeBank = duration;
    }

    void Player::resetMoveSpeed()
    {
        _moveSpeed = _baseMoveSpeed;
    }

    void Player::setIsReversed(bool isReversed)
    {
        _isReversed = isReversed;
        if (_isReversed == true)
            _reversedTimeBank = 5.0f;
    }

    void Player::setIsStopped(bool isStopped)
    {
        _isStopped = isStopped;
    }

    void Player::increaseBaseMoveSpeed(float addedMoveSpeed)
    {
        _baseMoveSpeed -= addedMoveSpeed;
    }

    void Player::handleWallCollision(std::pair<int, int> snakePos, std::unordered_map<std::pair<int, int>, bool> &walls)
    {
        int headX = snakePos.first;
        int headY = snakePos.second;

        bool wallLeft = walls.contains({headX - 1, headY})
        || std::find_if(
                _body.begin(),
                _body.end(),
                [&](const auto& element) {
                    return element == std::make_pair(headX - 1, headY);
                }
            ) != _body.end();

        bool wallRight = walls.contains({headX + 1, headY})
        || std::find_if(
                _body.begin(),
                _body.end(),
                [&](const auto& element) {
                    return element == std::make_pair(headX + 1, headY);
                }
            ) != _body.end();

        bool wallUp = walls.contains({headX, headY - 1})
        || std::find_if(
                _body.begin(),
                _body.end(),
                [&](const auto& element) {
                    return element == std::make_pair(headX, headY - 1);
                }
            ) != _body.end();

        bool wallDown = walls.contains({headX, headY + 1})
        || std::find_if(
                _body.begin(),
                _body.end(),
                [&](const auto& element) {
                    return element == std::make_pair(headX, headY + 1);
                }
            ) != _body.end();

        Player::Direction newDirection;

        bool canTurnLeft = !wallLeft && _direction != Player::Direction::RIGHT;
        bool canTurnRight = !wallRight && _direction != Player::Direction::LEFT;
        bool canTurnUp = !wallUp && _direction != Player::Direction::DOWN;
        bool canTurnDown = !wallDown && _direction != Player::Direction::UP;

        if ((canTurnLeft && canTurnRight) || (canTurnDown && canTurnUp)) {
            setIsStopped(true);
            return;
        }

        if (canTurnLeft)
            newDirection = Player::Direction::LEFT;
        else if (canTurnRight)
            newDirection = Player::Direction::RIGHT;
        else if (canTurnDown)
            newDirection = Player::Direction::DOWN;
        else if (canTurnUp)
            newDirection = Player::Direction::UP;
        else {
            setIsStopped(true);
            _isBlocked = true;
            return;
        }

        setNextDirection(newDirection);
    }

    void Player::updatePosition(std::unordered_map<std::pair<int, int>, bool> &walls)
    {
        _direction = _nextDirection;

        if (_isStopped || _isBlocked)
            return;

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

        if (walls.contains({newHeadX, newHeadY})) {
            handleWallCollision(_body.front(), walls);

            if (!_isStopped) {
                updatePosition(walls);
                return;
            }
            newHeadX = _body.front().first;
            newHeadY = _body.front().second;
        }

        if (_isStopped)
            return;

        _body.push_front({newHeadX, newHeadY});
        _body.pop_back();
    }

    void Player::updateTime(float deltaTime)
    {
        _reversedTimeBank -= deltaTime;
        if (_reversedTimeBank <= 0.0f)
            _isReversed = false;

        _speedChangeTimeBank -= deltaTime;
        if (_speedChangeTimeBank <= 0.0f)
            _moveSpeed = _baseMoveSpeed;
    }

    bool Player::collideWithBody(std::pair<int, int> position) const
    {
        for (auto it = std::next(_body.begin()); it != _body.end(); ++it)
            if (*it == position)
                return true;
        return false;
    }
}
