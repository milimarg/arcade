/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Player
*/

#ifndef PLAYER_HPP_
    #define PLAYER_HPP_

    #include <deque>
    #include <iostream>
    #include <unordered_map>
    #include <vector>
    #include <string>
    #include "Pair.hpp"
    #include <algorithm>

namespace arcade
{
    class Player {
        public:
            /**
             * Player Direction
             */
            enum class Direction {
                UP,
                RIGHT,
                DOWN,
                LEFT,
            };

            /**
             * Creates a Player
             * @param size Start size (number of parts)
             * @param direction Start direction
             * @param moveSpeed Start moveSpeed
             */
            Player(std::size_t size = 4, Direction direction = Direction::RIGHT, float moveSpeed = 0.1f);
            ~Player();

            /**
             * Inits snake data and gameSettings values
             * @param position init snake to a given position
             */
            void init(std::pair<int, int> position);

            /**
             * Set life state (alive (0) or dead (1))
             * @param state new life state to apply
             */
            void setIsDead(bool state);

            /**
             * Set new direction of snake
             * @param direction new direction to apply
             */
            void setDirection(Direction direction);

            /**
             * Set new next direction of snake
             * @param direction new next direction to apply
             */
            void setNextDirection(Direction direction);

            /**
             *
             * @return is the snake dead?
             */
            bool getIsDead() const;

            /**
             *
             * @return current direction
             */
            Direction getDirection() const;

            /**
             *
             * @return snake body positions
             */
            std::deque<std::pair<int, int>> getBody() const;

            /**
             *
             * @return snake head position
             */
            std::pair<int, int> getHead() const;

            /**
             * Get iterator of first snake body part
             */
            std::deque<std::pair<int, int>>::const_iterator getTailIt() const;

            /**
             * Get iterator of last snake body part
             */
            std::deque<std::pair<int, int>>::const_iterator getEndIt() const;

            /**
             * current move speed
             */
            float getMoveSpeed() const;

            /**
             *
             * @return is snake reversed
             */
            bool getIsReversed() const;

            /**
             *
             * @return is the snake stopped?
             */
            bool getIsStopped() const;

            /**
             *
             * @return is the snake blocked?
             */
            bool getIsBlocked() const;

            /**
             * Let the snake grows more of n parts
             * @param n number of parts to add
             */
            void addBodyPart(int n = 1);

            /**
             * Clears double-ended queue (deque) containing snake body positions
             */
            void resetBody();

            /**
             * Sets snake speed as given moveSpeed
             * @param moveSpeed new moveSpeed to apply
             * @param duration time while new moveSpeed is active
             */
            void setMoveSpeed(float moveSpeed, float duration);

            /**
             * Sets snake speed as normal
             */
            void resetMoveSpeed();

            /**
             * Saves reversedState of snake
             * @param isReversed is the snake reversed?
             */
            void setIsReversed(bool isReversed);

            /**
             * Saves stoppedState of snake
             * @param isStopped is the snake stopped?
             */
            void setIsStopped(bool isStopped);

            /**
             * Increase moveSpeed by addedMoveSpeed
             * @param addedMoveSpeed speed to add to current move speed
             */
            void increaseBaseMoveSpeed(float addedMoveSpeed);

            /**
             * Update snake's head to next position, if snake is in front of wall, determine how to continue
             * @param walls map
             */
            void updatePosition(std::unordered_map<std::pair<int, int>, bool> &walls);

            /**
             * Updates timeBank
             * @param deltaTime time since last call of updateTime()
             */
            void updateTime(float deltaTime);

            /**
             * Checks if snake is colliding with its body
             * @param position position to check
             * @return has snake collided with itself?
             */
            bool collideWithBody(std::pair<int, int> position) const;

        private:
            std::deque<std::pair<int, int>> _body;
            bool _isDead;
            Direction _direction;
            Direction _nextDirection;
            float _baseMoveSpeed;
            float _moveSpeed;
            bool _isReversed;
            float _reversedTimeBank;
            float _speedChangeTimeBank;
            bool _isStopped;
            bool _isBlocked;

            void handleWallCollision(std::pair<int, int> snakePos, std::unordered_map<std::pair<int, int>, bool> &walls);
    };
}

#endif /* !PLAYER_HPP_ */
