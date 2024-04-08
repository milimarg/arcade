/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** SolarFox
*/

#include "SolarFox.hpp"

namespace arcade
{
    SolarFox::SolarFox() :
        AGameModule("SolarFox"),
        _score(0),
        _isGameOver(false),
        _timeBank(0.0f),
        _toReload(false),
        _playerBullet(),
        _moveFaster(false),
        _canShoot(false),
        _mapIndex(0),
        _mapsFilepaths({
            "./Maps/SolarFox/level1.map",
            "./Maps/SolarFox/level2.map",
            "./Maps/SolarFox/level3.map",
            "./Maps/SolarFox/level4.map",
            "./Maps/SolarFox/challenge.map",
            "./Maps/SolarFox/level5.map",
            "./Maps/SolarFox/level6.map",
            "./Maps/SolarFox/level7.map",
            "./Maps/SolarFox/level8.map",
            "./Maps/SolarFox/challenge.map",
            "./Maps/SolarFox/level9.map",
            "./Maps/SolarFox/level10.map",
            "./Maps/SolarFox/level11.map",
            "./Maps/SolarFox/level12.map",
            "./Maps/SolarFox/challenge.map",
            "./Maps/SolarFox/level13.map",
            "./Maps/SolarFox/level14.map",
            "./Maps/SolarFox/level15.map",
            "./Maps/SolarFox/level16.map",
            "./Maps/SolarFox/challenge.map",
            "./Maps/SolarFox/level17.map",
            "./Maps/SolarFox/level18.map",
            "./Maps/SolarFox/level19.map",
            "./Maps/SolarFox/level20.map",
            "./Maps/SolarFox/challenge.map"
        })
    {}

    SolarFox::~SolarFox() {}

    void SolarFox::init()
    {
        createPixelsObject();
        createTextsObject();

        _gameSettings["windowWidth"] = 50;
        _gameSettings["windowHeight"] = 50;

        _gameSettings["walkableAreaMinX"] = _mod;
        _gameSettings["walkableAreaMinY"] = _mod * 3;
        _gameSettings["walkableAreaMaxX"] = _gameSettings["windowWidth"] / 1.125;
        _gameSettings["walkableAreaMaxY"] = _gameSettings["windowHeight"] * 1.125;

        _gameSettings["pointsNumberX"] = _gameSettings["walkableAreaMaxX"] - _gameSettings["walkableAreaMinX"] + (_mod / 2);
        _gameSettings["pointsNumberX"] /= _mod;
        _gameSettings["pointsNumberY"] = _gameSettings["walkableAreaMaxY"] - _gameSettings["walkableAreaMinY"] + (_mod / 2);
        _gameSettings["pointsNumberY"] /= _mod;

        _gameSettings["waitGameOver"] = 3;

        _gameSettings["pointsLeft"] = 0;

        for (auto &filepath : _mapsFilepaths)
            _mapWrapper.parseMap(filepath);
        setCurrentMap();
        initEnemies();
        initPlayer();

        _beforeReload = -1.0f;
        _beforeReload = (float)_gameSettings["waitGameOver"];

        latest = 0;
        latestPlayer = 0;
        latestBullet = 0;
        latestPlayerBullet = 0;
    }

    void SolarFox::stop()
    {
        _gameSettings.clear();
        _timeBank = 0.0f;
    }

    void SolarFox::applyEvents(IEvent *eventWrapper)
    {
        Key key = Key::KEY_LIST_END;

        while (1) {
            std::unique_ptr<IEventInfo> tempEventInfo = eventWrapper->getEvent();
            if (!tempEventInfo.get())
                break;
            key = tempEventInfo->getKey();
            if (key == Key::KEY_LIST_END || key == Key::NONE)
                break;
            applyEvent(key);
        }
    }

    void SolarFox::updatePlayer()
    {
        switch (_player.getDirection()) {
            case Entity::Direction::UP:
                _player.setY(_player.getY() - 1);
                break;
            case Entity::Direction::DOWN:
                _player.setY(_player.getY() + 1);
                break;
            case Entity::Direction::LEFT:
                _player.setX(_player.getX() - 1);
                break;
            case Entity::Direction::RIGHT:
                _player.setX(_player.getX() + 1);
                break;
            default:
                break;
        }
    }

    void SolarFox::updatePlayerBullet()
    {
        if (!_playerBullet.isActive())
            return;
        switch (_playerBullet.getDirection()) {
            case Entity::Direction::LEFT:
                _playerBullet.setX(_playerBullet.getX() - _playerBullet.getShift());
                break;
            case Entity::Direction::RIGHT:
                _playerBullet.setX(_playerBullet.getX() + _playerBullet.getShift());
                break;
            case Entity::Direction::UP:
                _playerBullet.setY(_playerBullet.getY() - _playerBullet.getShift());
                break;
            case Entity::Direction::DOWN:
                _playerBullet.setY(_playerBullet.getY() + _playerBullet.getShift());
                break;
            default:
                break;
        }
    }

    void SolarFox::setPointsNumber(int minRacksSize)
    {
        if (minRacksSize >= 1 && minRacksSize <= 5) {
            _pointsValue = 100;
            return;
        }
        if (minRacksSize >= 6 && minRacksSize <= 10) {
            _pointsValue = 200;
            return;
        }
        if (minRacksSize >= 11 && minRacksSize <= 15) {
            _pointsValue = 300;
            return;
        }
        if (minRacksSize >= 16 && minRacksSize <= 20) {
            _pointsValue = 400;
            return;
        }
    }

    void SolarFox::renderScore()
    {
        if (_texts == nullptr) {
            std::cerr << "score - render issue - texts wrapper is null." << std::endl;
            return;
        }

        std::string scoreStr = "Score: " + std::to_string(_score);

        _texts->getTextMap()[{2, 2}] = Text(scoreStr, 255, 255, 255);
    }

    void SolarFox::tryMovePlayer()
    {
        switch (_nextPlayerDirection) {
            case Entity::Direction::UP:
                if (_player.getDirection() != Entity::Direction::DOWN && _player.getX() % _mod == 0) {
                    _player.setDirection(Entity::Direction::UP);
                    _player.setRef(
                        Pixel(
                            255,
                            255,
                            255,
                            255,
                            Pixel::PixelType::TEXTURED,
                            '@',
                            "Assets/Solarfox/shipup.png",
                            Pixel::Rotation::R0,
                            {8, 8},
                            {0, 0}
                        )
                    );
                }
                break;
            case Entity::Direction::DOWN:
                if (_player.getDirection() != Entity::Direction::UP && _player.getX() % _mod == 0) {
                    _player.setDirection(Entity::Direction::DOWN);
                    _player.setRef(
                        Pixel(
                            255,
                            255,
                            255,
                            255,
                            Pixel::PixelType::TEXTURED,
                            '@',
                            "Assets/Solarfox/shipdown.png",
                            Pixel::Rotation::R0,
                            {8, 8},
                            {0, 0}
                        )
                    );
                }
                break;
            case Entity::Direction::LEFT:
                if (_player.getDirection() != Entity::Direction::RIGHT && _player.getY() % _mod == 0) {
                    _player.setDirection(Entity::Direction::LEFT);
                    _player.setRef(
                        Pixel(
                            255,
                            255,
                            255,
                            255,
                            Pixel::PixelType::TEXTURED,
                            '@',
                            "Assets/Solarfox/shipleft.png",
                            Pixel::Rotation::R0,
                            {8, 8},
                            {0, 0}
                        )
                    );
                }
                break;
            case Entity::Direction::RIGHT:
                if (_player.getDirection() != Entity::Direction::LEFT && _player.getY() % _mod == 0) {
                    _player.setDirection(Entity::Direction::RIGHT);
                    _player.setRef(
                        Pixel(
                            255,
                            255,
                            255,
                            255,
                            Pixel::PixelType::TEXTURED,
                            '@',
                            "Assets/Solarfox/shipright.png",
                            Pixel::Rotation::R0,
                            {8, 8},
                            {0, 0}
                        )
                    );
                }
                break;
            default:
                break;
        }
    }

    void SolarFox::update(float deltaTime)
    {
        if (_toReload) {
            _toReload = false;
            reload();
        }

        _timeBank += deltaTime;

        tryMovePlayer();

        if (_isGameOver) {
            if (_beforeReload >= 0.0f) {
                _beforeReload -= deltaTime;
                return;
            }
            _isGameOver = false;
            reload();
        }

        _pixels->getPixelMap().clear();

        if (_timeBank - latest > 0.03125f) {
            latest = _timeBank;
            for (auto it = _enemies.begin(); it < _enemies.end(); it += 1)
                detectWallCollision(*it, (it - _enemies.begin()) % 2 == 0);
            for (Bullet &bullet : _bullets) {
                if (!bullet.isActive())
                    continue;
                if (bullet.getOrientation() == Entity::Orientation::HORIZONTAL)
                    bullet.setX(bullet.getX() + bullet.getShift());
                else
                    bullet.setY(bullet.getY() + bullet.getShift());
                detectBulletOutside(bullet);
                if (!bullet.isActive())
                    continue;
                if (bullet.getX() == _player.getX() && bullet.getY() == _player.getY()) {
                    _isGameOver = true;
                }
                if (_playerBullet.isActive() && bullet.getX() == _playerBullet.getX() &&
                    bullet.getY() == _playerBullet.getY())
                    bullet.setStatus(false);
            }
        }
        if (_timeBank - latestBullet > 1.0f) {
            latestBullet = _timeBank;
            for (auto it = _bullets.begin(); it < _bullets.end(); it += 1) {
                size_t index = it - _bullets.begin();
                spawnBullet(_bullets[index], _enemies[index], index);
            }
        }
        spawnPlayerBullet();
        if (_timeBank - latestPlayer > (_moveFaster ? 0.0625f : 0.125f)) {
            latestPlayer = _timeBank;
            updatePlayer();
        }

        if (_timeBank - latestPlayerBullet > 0.03125) {
            latestPlayerBullet = _timeBank;
            updatePlayerBullet();
        }

        detectPlayerBulletTooFar();

        for (int y = _gameSettings["walkableAreaMinY"]; y <= _gameSettings["walkableAreaMaxY"] - _gameSettings["walkableAreaMaxY"] % _mod; y++) {
            for (int x = _gameSettings["walkableAreaMinX"]; x <= _gameSettings["walkableAreaMaxX"] - _gameSettings["walkableAreaMaxX"] % _mod; x++) {
                if (x % _mod == 0 || y % _mod == 0) {
                    _pixels->getPixelMap()[{x, y}] = Pixel(0, 160, 0, 255, Pixel::PixelType::DEFAULT, '#');
                }
            }
        }

        for (int y = _gameSettings["walkableAreaMinY"]; y < _gameSettings["walkableAreaMaxY"]; y += 1) {
            int x = _gameSettings["walkableAreaMaxX"];
            _pixels->getPixelMap()[{x, y}] = Pixel(0, 160, 0, 255, Pixel::PixelType::DEFAULT, '#');
        }

        for (int x = _gameSettings["walkableAreaMinX"]; x < _gameSettings["walkableAreaMaxX"]; x += 1) {
            int y = _gameSettings["walkableAreaMaxY"];
            _pixels->getPixelMap()[{x, y}] = Pixel(0, 160, 0, 255, Pixel::PixelType::DEFAULT, '#');
        }

        int full_size_x = ((_gameSettings["walkableAreaMaxX"] - _gameSettings["walkableAreaMinX"]) / _mod) + 1;
        int full_size_y = ((_gameSettings["walkableAreaMaxY"] - _gameSettings["walkableAreaMinY"]) / _mod) + 1;
        int map_size_x = _currentMap.getRacksSizeX();
        int map_size_y = _currentMap.getRacksSizeY();

        for (auto &collectible : _currentMap.getCollectiblesMap()) {
            const int offsetX = (int)((full_size_x - map_size_x) / 2) * _mod;
            const int offsetY = (int)((full_size_y - map_size_y) / 2) * _mod;
            const int x = offsetX + _gameSettings["walkableAreaMinX"] + collectible.first.first * _mod;
            const int y = offsetY + _gameSettings["walkableAreaMinY"] + collectible.first.second * _mod;

            if (!collectible.second)
                continue;
            if (_playerBullet.isActive() && _playerBullet.getX() == x &&
            _playerBullet.getY() == y) {
                collectible.second = false;
                _gameSettings["pointsLeft"] -= 1;
                _score += _pointsValue;
                continue;
            }
            _pixels->getPixelMap()[{x, y}] =
            Pixel(
                255,
                0,
                0,
                255,
                Pixel::PixelType::TEXTURED,
                'o',
                "Assets/Solarfox/collectible.png",
                Pixel::Rotation::R0,
                {8, 8},
                {0, 0}
            );
        }

        detectPlayerIsSafe();

        drawEnemies();
        drawBullets();
        drawPlayer();
        renderScore();

        _pixels->getPixelMap()[{_gameSettings["windowWidth"] + _mod, 0}] = Pixel(0, 0, 0, 0, Pixel::PixelType::DEFAULT, ' ');
        _pixels->getPixelMap()[{0, _gameSettings["windowHeight"] + _mod}] = Pixel(0, 0, 0, 0, Pixel::PixelType::DEFAULT, ' ');

        if (_playerBullet.isActive()) {
            _pixels->getPixelMap()[{_playerBullet.getX(), _playerBullet.getY()}] =
            Pixel(
                255,
                255,
                0,
                255,
                Pixel::PixelType::TEXTURED,
                'H',
                _playerBullet.getOrientation() == Entity::Orientation::HORIZONTAL ? "Assets/Solarfox/shiplaservertical.png" : "Assets/Solarfox/shiplaserhorizontal.png",
                Pixel::Rotation::R0,
                {8, 8},
                {0, 0}
            );
        }
        if (_gameSettings["pointsLeft"] == 0) {
            _mapIndex += 1;
            _mapIndex = _mapIndex > _mapsFilepaths.size() - 1 ? 0 : _mapIndex;
            _isGameOver = true;
        }
    }

    void SolarFox::reload()
    {
        stop();
        init();
    }

    int SolarFox::getScore()
    {
        return _score;
    }

    void SolarFox::draw(arcade::IGraphicalModule *graphicalModule)
    {
        graphicalModule->updatePixelsWrapper(_pixels.get());
        graphicalModule->updateTextsWrapper(_texts.get());
        graphicalModule->display();
    }

    /* CUSTOM */

    void SolarFox::setCurrentMap()
    {
        _currentMap = _mapWrapper.at(_mapIndex);
        setPointsNumber(std::max(_currentMap.getRacksSizeX(), _currentMap.getRacksSizeY()));
        _gameSettings["pointsLeft"] = _currentMap.getNumber();
    }

    void SolarFox::initEnemies()
    {
        const int windowWidth = _gameSettings["windowWidth"];
        const int windowHeight = _gameSettings["windowHeight"];
        static const std::array<int, 4> xs = {windowWidth / 3, windowWidth, windowWidth - (windowWidth / 3), 0};
        static const std::array<int, 4> ys = {0, windowHeight / 3, windowHeight + 2, windowHeight - (windowHeight / 3)};
        static const int enemyWidth = 2;
        static const int enemyHeight = 1;

        for (auto it = _enemies.begin(); it < _enemies.end(); it += 1) {
            int k = it - _enemies.begin();
            arcade::Enemy &enemy = _enemies[k];
            enemy.setRef(Pixel(255, 255, 255, 255, Pixel::PixelType::DEFAULT, '+'));
            enemy.setWidth(k % 2 == 0 ? enemyWidth : enemyHeight);
            enemy.setHeight(k % 2 == 0 ? enemyHeight : enemyWidth);
            enemy.setOrientation(k % 2 == 0 ? Entity::Orientation::HORIZONTAL :
                Entity::Orientation::VERTICAL);
            enemy.setX(xs[k]);
            enemy.setY(ys[k]);
            if (enemy.getOrientation() == Entity::Orientation::HORIZONTAL) {
                if (k != _enemies.size() - 1)
                    enemy.setY(enemy.getY() + 7);
            }
        }
    }

    void SolarFox::initPlayer()
    {
        _player.setX(_gameSettings["windowWidth"] / 2 - _mod / 2);
        _player.setY(_gameSettings["windowHeight"] / 2 - _mod / 2 + 1);
        _player.setWidth(1);
        _player.setHeight(1);
        _player.setDirection(Entity::Direction::LEFT);
        _player.setRef(
            Pixel(
                255,
                255,
                255,
                255,
                Pixel::PixelType::TEXTURED,
                '@',
                "Assets/Solarfox/shipleft.png",
                Pixel::Rotation::R0,
                {8, 8},
                {0, 0}
            )
        );
        _playerBullet.setShift(1);
        _nextPlayerDirection = Entity::Direction::LEFT;
    }

    void SolarFox::drawEnemies()
    {
        for (auto &enemy : _enemies) {
            for (int j = enemy.getY(); j < enemy.getY() + enemy.getHeight(); j++) {
                for (int i = enemy.getX(); i < enemy.getX() + enemy.getWidth(); i++) {
                    _pixels->getPixelMap()[{i, j}] = enemy.getRef();
                }
            }
        }
    }

    void SolarFox::drawBullets()
    {
        for (auto &bullet : _bullets) {
            if (!bullet.isActive())
                continue;
            for (int j = bullet.getY(); j < bullet.getY() + bullet.getHeight(); j++) {
                for (int i = bullet.getX(); i < bullet.getX() + bullet.getWidth(); i++) {
                    _pixels->getPixelMap()[{i, j}] = bullet.getRef();
                }
            }
        }
    }

    void SolarFox::drawPlayer()
    {
        for (int j = _player.getY(); j < _player.getY() + _player.getHeight(); j++) {
            for (int i = _player.getX(); i < _player.getX() + _player.getWidth(); i++) {
                _pixels->getPixelMap()[{i, j}] = _player.getRef();
            }
        }
    }

    void SolarFox::detectPlayerIsSafe()
    {
        if (_player.getX() < _gameSettings["walkableAreaMinX"] ||
        _player.getX() > _gameSettings["walkableAreaMaxX"] ||
        _player.getY() < _gameSettings["walkableAreaMinY"] ||
        _player.getY() > _gameSettings["walkableAreaMaxY"]) {
            _isGameOver = true;
        }
    }

    int genRandom(int min, int max) {
        return min + std::rand() % (max - min + 1);
    }

    void SolarFox::spawnBullet(Bullet &bullet, Enemy &enemy, size_t i)
    {
        if (bullet.isActive())
            return;
        if (enemy.getOrientation() == Entity::Orientation::HORIZONTAL &&
            (enemy.getX() < (_gameSettings["windowWidth"] * 0.2) ||
            enemy.getX() > (_gameSettings["windowWidth"] * 0.8)))
            return;
        if (enemy.getOrientation() == Entity::Orientation::VERTICAL &&
            (enemy.getY() < (_gameSettings["windowHeight"] * 0.2) ||
            enemy.getY() > (_gameSettings["windowHeight"] * 0.8)))
            return;
        if (genRandom(1, 100) > 50)
            return;
        bullet.setStatus(true);
        bullet.setX(enemy.getX());
        bullet.setY(enemy.getY());
        bullet.setShift(i == 0 || i == 3 ? 1 : -1);
        bullet.setOrientation(i % 2 == 0 ? Entity::Orientation::VERTICAL :
            Entity::Orientation::HORIZONTAL);
        switch (bullet.getOrientation()) {
            case Entity::Orientation::VERTICAL:
                bullet.setRef(
                    Pixel(
                        127,
                        0,
                        0,
                        255,
                        Pixel::PixelType::TEXTURED,
                        '*',
                        "Assets/Solarfox/enemylaservertical.png",
                        Pixel::Rotation::R0,
                        {8, 8},
                        {0, 0}
                    )
                );
                break;
            case Entity::Orientation::HORIZONTAL:
                bullet.setRef(
                    Pixel(
                        127,
                        0,
                        0,
                        255,
                        Pixel::PixelType::TEXTURED,
                        '*',
                        "Assets/Solarfox/enemylaserhorizontal.png",
                        Pixel::Rotation::R0,
                        {8, 8},
                        {0, 0}
                    )
                );
                break;
            default:
                bullet.setRef(Pixel(127, 0, 0, 255, Pixel::PixelType::DEFAULT, '*'));
                break;
        }
        bullet.setWidth(1);
        bullet.setHeight(1);
    }

    void SolarFox::spawnPlayerBullet()
    {
        if (!_canShoot || _playerBullet.isActive())
            return;
        _canShoot = false;
        _playerBullet.setStatus(true);
        _playerBullet.setX(_player.getX());
        _playerBullet.setY(_player.getY());
        _playerBullet.setMaxX(_player.getX());
        _playerBullet.setMaxY(_player.getY());
        _playerBullet.setDirection(_player.getDirection());
        _playerBullet.setRef(Pixel(127, 127, 0, 255, Pixel::PixelType::DEFAULT, '$'));
    }

    void SolarFox::detectWallCollision(Enemy &enemy, bool isHorizontal)
    {
        if (isHorizontal) {
            enemy.setX(enemy.getX() + enemy.getShift() *
                (enemy.getOrientation() == Entity::Orientation::HORIZONTAL ? 1 : -1));
            if (enemy.getX() < _mod || enemy.getX() > _gameSettings["windowWidth"] - enemy.getWidth() - _mod)
                enemy.setShift(-enemy.getShift());
        } else {
            enemy.setY(enemy.getY() + enemy.getShift() *
                (enemy.getOrientation() == Entity::Orientation::HORIZONTAL ? 1 : -1));
            if (enemy.getY() < _mod || enemy.getY() > _gameSettings["windowHeight"] - enemy.getHeight() - _mod)
                enemy.setShift(-enemy.getShift());
        }
    }

    void SolarFox::detectPlayerBulletTooFar()
    {
        if (!_playerBullet.isActive())
            return;
        if (_playerBullet.getX() < (_playerBullet.getMaxX() - _mod * 2))
            _playerBullet.setStatus(false);
        if (_playerBullet.getX() > (_playerBullet.getMaxX() + _mod * 2))
            _playerBullet.setStatus(false);
        if (_playerBullet.getY() < (_playerBullet.getMaxY() - _mod * 2))
            _playerBullet.setStatus(false);
        if (_playerBullet.getY() > (_playerBullet.getMaxY() + _mod * 2))
            _playerBullet.setStatus(false);
    }

    void SolarFox::detectBulletOutside(Bullet &bullet)
    {
        if (bullet.getOrientation() == Entity::Orientation::HORIZONTAL &&
            (bullet.getX() < 0 || bullet.getX() > _gameSettings["windowWidth"] + bullet.getWidth())) {
            bullet.setStatus(false);
        }
        if (bullet.getOrientation() == Entity::Orientation::VERTICAL &&
            (bullet.getY() < 0 || bullet.getY() > _gameSettings["windowHeight"] + bullet.getHeight())) {
            bullet.setStatus(false);
        }
    }

    void SolarFox::applyEvent(const Key &key)
    {
        switch (key) {
            case Key::UP_ARROW:
                _nextPlayerDirection = Entity::Direction::UP;
                break;
            case Key::DOWN_ARROW:
                _nextPlayerDirection = Entity::Direction::DOWN;
                break;
            case Key::LEFT_ARROW:
                _nextPlayerDirection = Entity::Direction::LEFT;
                break;
            case Key::RIGHT_ARROW:
                _nextPlayerDirection = Entity::Direction::RIGHT;
                break;
            case Key::C_KEY:
                if (!_canShoot)
                    _canShoot = true;
                break;
            case Key::R_KEY:
                _toReload = true;
                break;
            case Key::S_KEY:
                _moveFaster = !_moveFaster;
                break;
            default:
                break;
        }
    }
}
