/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** Pacman
*/

#ifndef Pacman_HPP_
    #define Pacman_HPP_

    #include "AGameModule.hpp"
    #include "IGraphicalModule.hpp"
    #include <vector>
    #include <deque>
    #include <cstdlib>
    #include <ctime>
    #include <algorithm>
    #include <iostream>
    #include <fstream>
    #include <string>

namespace arcade
{
    /**
     * Pacman Class
     */
    class Pacman : public AGameModule {
        public:

            /**
             * Direction
             */
            enum class Direction {
                UP,
                RIGHT,
                DOWN,
                LEFT,
                NONE
            };

            /**
             * State of Ghost
             */
            enum class GhostState {
                WAITING,
                ALIVE,
                DEAD
            };

            /**
             * State of GumGum (pacman food)
             */
            enum class GumGumState {
                NONE,
                VISIBLE
            };

            Pacman();
            ~Pacman();

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
            struct Ghosts {
                GhostState state;
                std::pair<int, int> position;
                Direction direction;
                std::vector<std::pair<int, int>> path;
                float timeBeforeRespawn;
                int textureIndex;
            };

            struct GumGum {
                GumGumState state;
                std::pair<int, int> position;
                float timeBeforeRespawn;
            };

            int _score;
            bool _isGameOver;
            std::ifstream _map;
            std::unordered_map<std::string, int> _gameSettings;

            std::pair<int, int> _pacman;
            std::vector<Ghosts> _ghosts;
            float _timeBankPacman;
            Direction _pacmanDirection;
            Direction _nextPacmanDirection;

            float _timeBankGhost;
            float _timeNewGhost;
            float _timeAfterWin;
            float _accelerator;
            float _gumgumTime;
            float _ghostsSpeed;
            bool _gumgumEat;
            int _ghostNbr;

            std::vector<std::pair<int, int>> _wallPositions;
            std::vector<std::pair<int, int>> _foodPositions;
            std::vector<GumGum> _gumgums;
            bool _toReload;

            size_t _pacmanTextureIndex;

            bool pixelIsSpace(int x, int y);
            int tryUpdatePacman(int headX, int headY, Direction direction);
            void updatePacmanPosition();
            bool checkIfGhosts(int headX, int headY);
            Direction moveRandomlyGhost(int index);
            void tryUpdateGhost(int index);
            void makeComebackGhost(int index);
            void updateGhostsPosition();
            void handleCollisions();
            void renderPacman();
            void renderGhost();
            void renderFood();
            void renderArena();
            void renderBackground();
            void renderScore();
    };
}

extern "C" {
    std::string getType() {
        return "game";
    }

    std::unique_ptr<arcade::IGameModule> entryPoint() {
        return std::make_unique<arcade::Pacman>();
    }
}

#endif /* !Pacman_HPP_ */
