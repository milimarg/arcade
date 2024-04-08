/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** Nibbler
*/

#ifndef NIBBLER_HPP_
    #define NIBBLER_HPP_

    #include "AGameModule.hpp"
    #include "IGraphicalModule.hpp"
    #include <vector>
    #include <deque>
    #include <cstdlib>
    #include <ctime>
    #include <algorithm>
    #include <array>
    #include <fstream>
    #include "Food.hpp"
    #include "Player.hpp"

namespace arcade
{
    /**
     * Nibbler Class
     */
    class Nibbler : public AGameModule {
        public:
            Nibbler();
            ~Nibbler();

            /**
             * Sets up snake entity, init gameSettings values and create objects (pixels and texts)
             */
            void init() override;

            /**
             * Resets gumgums and ghosts, clears gameSettings and resets timeBank
             */
            void stop() override;

            /**
             * Checks for events (i.e. pressed keys) sent by current graphics library.
             * @param eventWrapper wrapper containing getters to obtain events
             */
            void applyEvents(IEvent *eventWrapper) override;

            /**
             * Clears pixels wrapper, moves player and displays doom renderer.
             * @param deltaTime Time since last call of update() function
             */
            void update(float deltaTime) override;

            /**
             * Calls stop() then init().
             */
            void reload() override;

            /**
             * Returns the current score.
             * @return current score
             */
            int getScore() override;

            /**
             * Updates pixels wrapper, texts wrapper and call display() of the given module
             * @param module given graphical module
             */
            void draw(IGraphicalModule *module) override;

        protected:
            /**
             * Checks if key is in keyTable, if it does, it runs the associated action
             * @param key Pressed key to process
             */
            void applyEvent(const Key &key) override;

        private:
            int _score;
            bool _isGameOver;
            Player _snake;
            std::unordered_map<std::string, int> _gameSettings;
            float _timeBank;
            bool _toReload;
            std::unordered_map<std::pair<int, int>, std::pair<int, int>> _arenaTextureCoords;
            std::vector<Food> _foodMap;
            float _beforeReload;
            std::pair<std::array<int, 4>, std::array<int, 4>> _backgroundColors;
            std::unordered_map<std::pair<int, int>, bool> _walls;
            float _currentSpeedIncrease;

            void initSnake();
            void initWallMapFromFile(const std::string &fileName);
            void handleCollisions();
            void handleNibblerDirectionChange(const Key &key);
            void renderNibbler();
            bool checkFoodPosition(std::pair<int, int> checkedPos);
            void spawnFood();
            void renderFood();
            void renderArena();
            void renderBackground();
            void renderScore();

            static const std::unordered_map<Key, std::pair<Player::Direction, Player::Direction>> _playerDirection;
    };
}

extern "C" {
    std::string getType() {
        return "game";
    }

    std::unique_ptr<arcade::IGameModule> entryPoint() {
        return std::make_unique<arcade::Nibbler>();
    }
}

#endif /* !NIBBLER_HPP_ */
