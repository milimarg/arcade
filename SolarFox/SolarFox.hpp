/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** SolarFox
*/

#ifndef SolarFox_HPP_
    #define SolarFox_HPP_

    #include "AGameModule.hpp"
    #include "IGraphicalModule.hpp"
    #include <vector>
    #include <cstdlib>
    #include <array>
    #include <unordered_map>
    #include "Enemy.hpp"
    #include "Bullet.hpp"
    #include "Player.hpp"
    #include "MapWrapper.hpp"

namespace arcade
{
    /**
     * SolarFox Class
     */
    class SolarFox : public AGameModule {
        public:
            SolarFox();
            ~SolarFox();

            /**
             * Creates objects (pixels and texts), sets up useful values (like window size) in gameSettings,
             * parses maps and init entities (enemies and player)
             */
            void init() override;

            /**
             * Clears gameSettings and resets timeBank
             */
            void stop() override;

            /**
             * Checks for events (i.e. pressed keys) sent by current graphics library.
             * @param eventWrapper wrapper containing getters to obtain events
             */
            void applyEvents(IEvent *eventWrapper) override;

            /**
             * Clears pixels wrapper, moves player, check collisions (player and bullets) and
             * draw entities (player,  bullets and enemies).
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
             * @param graphicalModule given graphical module
             */
            void draw(IGraphicalModule *graphicalModule) override;

            /**
             * Draws current score.
             */
            void renderScore();
        protected:
            /**
             * Checks if key is in keyTable, if it does, it runs the associated action
             * @param key Pressed key to process
             */
            void applyEvent(const Key &key) override;

        private:

            void setCurrentMap();

            void initEnemies();
            void drawEnemies();
            void detectWallCollision(Enemy &enemy, bool isHorizontal);
            void detectPlayerBulletTooFar();

            void drawBullets();
            void spawnBullet(Bullet &bullet, Enemy &enemy, size_t i);
            void spawnPlayerBullet();
            void detectBulletOutside(Bullet &bullet);

            void initPlayer();
            void drawPlayer();
            void tryMovePlayer();
            void detectPlayerIsSafe();
            void updatePlayer();
            void updatePlayerBullet();

            void setPointsNumber(int minRacksSize);

            int _score;
            bool _isGameOver;
            std::vector<std::pair<int, int>> _playerPositions;
            std::unordered_map<std::string, int> _gameSettings;
            float _timeBank;

            std::array<Enemy, 4> _enemies;
            std::array<Bullet, 4> _bullets;

            Player _player;
            Entity::Direction _nextPlayerDirection;
            Bullet _playerBullet;

            const unsigned int _mod = 4;

            float _beforeReload;
            bool _toReload;

            bool _moveFaster;
            bool _canShoot;
            int _pointsValue;

            float latest = 0.0f;
            float latestBullet = 0.0f;
            float latestPlayer = 0.0f;
            float latestPlayerBullet = 0.0f;

            size_t _mapIndex;
            std::vector<std::string> _mapsFilepaths;
            MapWrapper _mapWrapper;
            Map _currentMap;
    };
}

extern "C" {
    std::string getType() {
        return "game";
    }

    std::unique_ptr<arcade::IGameModule> entryPoint() {
        return std::make_unique<arcade::SolarFox>();
    }
}

#endif /* !SolarFox_HPP_ */
