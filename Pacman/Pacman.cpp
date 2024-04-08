/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Pacman
*/


#include "Pacman.hpp"

namespace arcade
{
    Pacman::Pacman() :
        AGameModule("Pacman"),
        _score(0),
        _isGameOver(false),
        _timeBankPacman(0.0f),
        _pacmanDirection(Direction::NONE),
        _nextPacmanDirection(Direction::NONE),
        _timeBankGhost(0.0f),
        _timeNewGhost(0.0f),
        _timeAfterWin(0.0f),
        _accelerator(1.0f),
        _gumgumTime(0.0f),
        _ghostsSpeed(0.1f),
        _gumgumEat(false),
        _ghostNbr(0),
        _toReload(false),
        _pacmanTextureIndex(0)
    {
        std::srand(std::time(nullptr));
    }

    Pacman::~Pacman() {}

    void Pacman::init()
    {
        _map = std::ifstream("Maps/Pacman/pacman.map");

        _score = 0;
        _isGameOver = false;
        _timeBankPacman = 0;
        _timeBankGhost = 0;
        _timeNewGhost = 0;
        _ghostNbr = 0;
        _pacmanDirection = Direction::NONE;
        _nextPacmanDirection = Direction::NONE;

        createPixelsObject();
        createTextsObject();

        int y = 0;
        int x = 0;
        std::string line;

        _map.seekg(0, std::ios::beg);
        while (std::getline(_map, line)) {
            x = 0;
            for (char c : line) {
                if (c == '#')
                    _wallPositions.push_back({x, y});
                if (c == '-')
                    _foodPositions.push_back({x, y});
                if (c == 'C')
                    _pacman = {x, y};
                if (c == 'G')
                    _ghosts.push_back({GhostState::WAITING, {x, y}, Direction::NONE, {{x, y}}, 0, 0});
                if (c == 'o')
                    _gumgums.push_back({GumGumState::NONE, {x, y}, 0});
                x++;
            }
            y++;
        }
        _gameSettings["arenaWidth"] = x;
        _gameSettings["arenaHeight"] = y;
    }

    void Pacman::stop()
    {
        _gameSettings.clear();
        _foodPositions.clear();
        _gumgums.clear();
        _ghosts.clear();
        _timeBankPacman = 0.0f;
        _timeBankGhost = 0.0f;
        _timeNewGhost = 0.0f;
        _ghostNbr = 0;
    }

    void Pacman::applyEvents(IEvent *eventWrapper)
    {
        Key key = Key::KEY_LIST_END;

        while (1) {
            std::unique_ptr<IEventInfo> tempEventInfo = eventWrapper->getEvent();
            key = tempEventInfo->getKey();
            if (key == Key::KEY_LIST_END || key == Key::NONE)
                break;
            applyEvent(key);
        }
    }

    void Pacman::update(float deltaTime)
    {
        if (_foodPositions.size() == 0) {
            _timeAfterWin += deltaTime;
            if (_timeAfterWin >= 5.0f) {
                _toReload = true;
                _timeAfterWin = 0.0f;
                _accelerator = (_accelerator > 0.2f) ? _accelerator - 0.2f : 0.2f;
            }
        }
        if (_toReload) {
            _toReload = false;
            reload();
        }
        _timeBankPacman += deltaTime;
        if (_pacmanDirection != Direction::NONE) {
            _timeBankGhost += deltaTime;
            _timeNewGhost += deltaTime;
        }
        if (_timeNewGhost >= 3.0f * _accelerator) {
            if (_ghostNbr < 4) {
                _ghosts[_ghostNbr].direction = Direction::UP;
                _ghosts[_ghostNbr].state = GhostState::ALIVE;
                _ghostNbr++;
            }
            _timeNewGhost -= 3.0f * _accelerator;
        }

        for (auto it = _ghosts.begin(); it != _ghosts.end(); ++it) {
            if (it->state == GhostState::WAITING) {
                it->timeBeforeRespawn -= deltaTime;
                if (it->timeBeforeRespawn <= 0.0f) {
                    it->state = GhostState::ALIVE;
                    it->timeBeforeRespawn = 0.0f;
                }
            }
        }

        for (auto it = _gumgums.begin(); it != _gumgums.end(); ++it) {
            if (it->state == GumGumState::NONE) {
                it->timeBeforeRespawn -= deltaTime;
                if (it->timeBeforeRespawn <= 0.0f) {
                    it->state = GumGumState::VISIBLE;
                    it->timeBeforeRespawn = 0.0f;
                }
            }
        }
        if (_gumgumEat) {
            _gumgumTime += deltaTime;
            if (_gumgumTime >= 15.0f * _accelerator) {
                _gumgumEat = false;
                _ghostsSpeed = 0.1f;
            }
        }
        if (_isGameOver) {
            _isGameOver = false;
            reload();
        }
        if (_pixels == nullptr)
            throw arcade::Error("Pacman - update - Failed to render: Pixels object is null.");

        if (!_isGameOver && _timeBankPacman >= 0.1f * _accelerator) {
            updatePacmanPosition();
            _timeBankPacman -= 0.1f * _accelerator;
        }
        handleCollisions();
        if (!_isGameOver && _timeBankGhost >= _ghostsSpeed * _accelerator) {
            updateGhostsPosition();
            _timeBankGhost -= _ghostsSpeed * _accelerator;
        }
        handleCollisions();
        for (int y = 0; y < _gameSettings["arenaHeight"]; y++) {
            for (int x = 0; x < _gameSettings["arenaWidth"]; x++) {
                _pixels->getPixelMap()[{x, y}] =
                Pixel(
                    0,
                    0,
                    0,
                    0,
                    Pixel::PixelType::DEFAULT,
                    ' '
                );
            }
        }
        renderScore();
        renderBackground();
        renderArena();
        renderFood();
        renderGhost();
        renderPacman();
    }

    void Pacman::reload()
    {
        stop();
        init();
    }

    int Pacman::getScore()
    {
        return _score;
    }

    void Pacman::draw(IGraphicalModule *graphicalModule)
    {
        graphicalModule->updatePixelsWrapper(_pixels.get());
        graphicalModule->updateTextsWrapper(_texts.get());
        graphicalModule->display();
    }

    void Pacman::applyEvent(const Key &key)
    {
        switch (key) {
            case Key::UP_ARROW:
                _nextPacmanDirection = Direction::UP;
                break;
            case Key::DOWN_ARROW:
                _nextPacmanDirection = Direction::DOWN;
                break;
            case Key::LEFT_ARROW:
                _nextPacmanDirection = Direction::LEFT;
                break;
            case Key::RIGHT_ARROW:
                _nextPacmanDirection = Direction::RIGHT;
                break;
            case Key::R_KEY:
                _toReload = true;
                break;
            default:
                break;
        }
    }

    void Pacman::renderPacman()
    {
        if (_pixels == nullptr)
            throw arcade::Error("Pacman - renderPacman - Failed to render pacman: Pixels object is null.");

        size_t textureX = 0;
        size_t textureY = 0;

        switch (_pacmanDirection) {
            case Direction::RIGHT:
                textureY = 0;
                break;
            case Direction::LEFT:
                textureY = 8;
                break;
            case Direction::UP:
                textureY = 16;
                break;
            case Direction::DOWN:
                textureY = 24;
                break;
            default:
                break;
        }

        switch (_pacmanTextureIndex) {
            case 0:
                textureX = 16;
                textureY = 0;
                break;
            case 1:
                textureX = 8;
                break;
            case 2:
                textureX = 0;
                break;
            default:
                break;
        }

        _pixels->getPixelMap()[_pacman] =
        Pixel(
            255,
            255,
            0,
            255,
            Pixel::PixelType::TEXTURED,
            'C',
            "Assets/Pacman/pacman-general.png",
            Pixel::Rotation::R0,
            {8, 8},
            {textureX, textureY}
        );
    }

    void Pacman::renderGhost()
    {
        size_t index = 0;

        if (_pixels == nullptr)
            throw arcade::Error("Pacman - renderGhost - Failed to render ghosts: Pixels object is null.");

        for (const auto &ghost : _ghosts) {
            size_t textureX = 0;
            size_t textureY = 0;

            if (ghost.state == GhostState::DEAD) {
                textureX = 8 * 8;
                textureY = 8 * 5;

                switch (ghost.direction) {
                    case Direction::RIGHT:
                        textureX += 0;
                        break;
                    case Direction::LEFT:
                        textureX += 8;
                        break;
                    case Direction::UP:
                        textureX += 8 * 2;
                        break;
                    case Direction::DOWN:
                        textureX += 8 * 3;
                        break;
                    default:
                        break;
                }

                _pixels->getPixelMap()[ghost.position] =
                Pixel(
                    255,
                    0,
                    255,
                    255,
                    Pixel::PixelType::TEXTURED,
                    'O',
                    "Assets/Pacman/pacman-general.png",
                    Pixel::Rotation::R0,
                    {8, 8},
                    {textureX, textureY}
                );
            } else  {
                if (_gumgumEat) {
                    textureX = 8 * 8;
                    textureY = 8 * 4;

                    if (ghost.textureIndex == 1)
                        textureX += 8;

                    _pixels->getPixelMap()[ghost.position] =
                    Pixel(
                        0,
                        255,
                        255,
                        255,
                        Pixel::PixelType::TEXTURED,
                        'G',
                        "Assets/Pacman/pacman-general.png",
                        Pixel::Rotation::R0,
                        {8, 8},
                        {textureX, textureY}
                    );
                } else {
                    textureX = 0;
                    textureY = 8 * 4;

                    switch (ghost.direction) {
                        case Direction::RIGHT:
                            textureX += 0;
                            break;
                        case Direction::LEFT:
                            textureX += 16;
                            break;
                        case Direction::UP:
                            textureX += 16 * 2;
                            break;
                        case Direction::DOWN:
                            textureX += 16 * 3;
                            break;
                        default:
                            break;
                    }

                    switch (ghost.textureIndex) {
                        case 0:
                            break;
                        case 1:
                            textureX += 8;
                            break;
                        default:
                            break;
                    }

                    textureY += 8 * index;

                    _pixels->getPixelMap()[ghost.position] =
                    Pixel(
                        255,
                        0,
                        0,
                        255,
                        Pixel::PixelType::TEXTURED,
                        'G',
                        "Assets/Pacman/pacman-general.png",
                        Pixel::Rotation::R0,
                        {8, 8},
                        {textureX, textureY}
                    );
                }
            }
            ++index;
        }
    }

    void Pacman::renderFood()
    {
        if (_pixels == nullptr)
            throw arcade::Error("Pacman - renderFood - Failed to render food: Pixels object is null.");

        size_t textureFoodX = 117;
        size_t textureFoodY = 18;

        size_t textureGumGumX = 126 + 9;
        size_t textureGumGumY = 18;

        for (const auto &foodPos : _foodPositions) {
            _pixels->getPixelMap()[foodPos] =
            Pixel(
                255,
                255,
                255,
                255,
                Pixel::PixelType::TEXTURED,
                '.',
                "Assets/Pacman/pacman-maze-parts.png",
                Pixel::Rotation::R0,
                {8, 8},
                {textureFoodX, textureFoodY}
            );
        }
        for (const auto &gumgumPos : _gumgums) {
            if (gumgumPos.state == GumGumState::VISIBLE)
                _pixels->getPixelMap()[gumgumPos.position] =
                Pixel(
                    0,
                    255,
                    0,
                    255,
                    Pixel::PixelType::TEXTURED,
                    '.',
                    "Assets/Pacman/pacman-maze-parts.png",
                    Pixel::Rotation::R0,
                    {8, 8},
                    {textureGumGumX, textureGumGumY}
                );
        }
    }

    bool Pacman::pixelIsSpace(int x, int y)
    {
        int r = _pixels->getPixelMap()[{x, y}].getRed();
        int g = _pixels->getPixelMap()[{x, y}].getGreen();
        int b = _pixels->getPixelMap()[{x, y}].getBlue();

        return !(r == 0 && g == 0 && b == 255);
    }

    bool Pacman::checkIfGhosts(int headX, int headY)
    {
        for (auto it = _ghosts.begin(); it != _ghosts.end(); ++it) {
            if (it->position == std::make_pair(headX, headY) && it->state == GhostState::ALIVE && !_gumgumEat) {
                return true;
            }
        }
        return false;
    }

    int Pacman::tryUpdatePacman(int headX, int headY, Direction direction)
    {
        int newX = headX;
        int newY = headY;

        switch (direction) {
            case Direction::UP:
                newY = (headY - 1 < 0) ? _gameSettings["arenaHeight"] - 1 : headY - 1;
                break;
            case Direction::DOWN:
                newY = (headY + 1 > _gameSettings["arenaHeight"] - 1) ? 0 : headY + 1;
                break;
            case Direction::LEFT:
                newX = (headX - 1 < 0) ? _gameSettings["arenaWidth"] - 1 : headX - 1;
                break;
            case Direction::RIGHT:
                newX = (headX + 1 > _gameSettings["arenaWidth"] - 1) ? 0 : headX + 1;
                break;
            default:
                break;
        }
         if (pixelIsSpace(newX, newY)) {
            if (checkIfGhosts(newX, newY))
                return 1;
            _pacmanDirection = direction;
            _pacman = {newX, newY};

            if (++_pacmanTextureIndex >= 3)
                _pacmanTextureIndex = 0;
            return 0;
        }
        return 1;
    }

    void Pacman::updatePacmanPosition()
    {
        int newHeadX = _pacman.first;
        int newHeadY = _pacman.second;

        if (_foodPositions.size() == 0)
            return;

        if (++_pacmanTextureIndex >= 3)
            _pacmanTextureIndex = 0;
        if (tryUpdatePacman(newHeadX, newHeadY, _nextPacmanDirection) == 0)
            return;
        if (tryUpdatePacman(newHeadX, newHeadY, _pacmanDirection) == 0)
            return;
    }

    Pacman::Direction Pacman::moveRandomlyGhost(int index)
    {
        int headX = _ghosts[index].position.first;
        int headY = _ghosts[index].position.second;
        int newY = 0;
        int newX = 0;
        Direction previousDirection = _ghosts[index].direction;
        std::vector<std::pair<Direction, Direction>> _ghostDirection = {
            {Pacman::Direction::UP, Pacman::Direction::DOWN},
            {Pacman::Direction::RIGHT, Pacman::Direction::LEFT},
            {Pacman::Direction::LEFT, Pacman::Direction::RIGHT},
            {Pacman::Direction::DOWN, Pacman::Direction::UP},
        };

        while (!_ghostDirection.empty()) {
            newX = headX;
            newY = headY;
            int random = std::rand() % _ghostDirection.size();
            if (previousDirection == _ghostDirection[random].second) {
                _ghostDirection.erase(_ghostDirection.begin() + random);
                continue;
            }
            switch (_ghostDirection[random].first) {
                case Direction::UP:
                    newY = (headY - 1 < 0) ? _gameSettings["arenaHeight"] - 1 : headY - 1;
                    break;
                case Direction::DOWN:
                    newY = (headY + 1 > _gameSettings["arenaHeight"] - 1) ? 0 : headY + 1;
                    break;
                case Direction::LEFT:
                    newX = (headX - 1 < 0) ? _gameSettings["arenaWidth"] - 1 : headX - 1;
                    break;
                case Direction::RIGHT:
                    newX = (headX + 1 > _gameSettings["arenaWidth"] - 1) ? 0 : headX + 1;
                    break;
                default:
                    break;
            }
            if (pixelIsSpace(newX, newY)) {
                if (checkIfGhosts(newX, newY))
                    return Direction::NONE;
                return _ghostDirection[random].first;
            }
            _ghostDirection.erase(_ghostDirection.begin() + random);
        }
        return Direction::NONE;
    }

    void Pacman::tryUpdateGhost(int index)
    {
        int headX = _ghosts[index].position.first;
        int headY = _ghosts[index].position.second;

        if (_foodPositions.size() == 0)
            return;
        _ghosts[index].direction = moveRandomlyGhost(index);
        switch (_ghosts[index].direction) {
             case Direction::UP:
                headY = (headY - 1 < 0) ? _gameSettings["arenaHeight"] - 1 : headY - 1;
                break;
            case Direction::DOWN:
                headY = (headY + 1 > _gameSettings["arenaHeight"] - 1) ? 0 : headY + 1;
                break;
            case Direction::LEFT:
                headX = (headX - 1 < 0) ? _gameSettings["arenaWidth"] - 1 : headX - 1;
                break;
            case Direction::RIGHT:
                headX = (headX + 1 > _gameSettings["arenaWidth"] - 1) ? 0 : headX + 1;
                break;
            default:
                break;
        }
        bool found = false;
        for (auto it = _ghosts[index].path.begin(); it != _ghosts[index].path.end(); ++it) {
            if (*it == std::make_pair(headX, headY)) {
                found = true;
                _ghosts[index].path.erase(it, _ghosts[index].path.end());
                break;
            }
        }
        if (!found)
            _ghosts[index].path.push_back({headX, headY});
        _ghosts[index].position = {headX, headY};
        if (++(_ghosts[index].textureIndex) >= 2)
            _ghosts[index].textureIndex = 0;
    }

    void Pacman::makeComebackGhost(int index)
    {
        if (_ghosts[index].path.size() > 1) {
            _ghosts[index].position = _ghosts[index].path.back();
            _ghosts[index].path.pop_back();
        } else {
            _ghosts[index].state = GhostState::WAITING;
        }
    }

    void Pacman::updateGhostsPosition()
    {
        for (int i = 0; i < _ghostNbr; ++i) {
            if (_ghosts[i].state == GhostState::ALIVE)
                tryUpdateGhost(i);
            if (_ghosts[i].state == GhostState::DEAD)
                makeComebackGhost(i);
        }
    }

    void Pacman::renderArena()
    {
        if (_pixels == nullptr)
            throw arcade::Error("Pacman - renderArena - Failed to render arena: Pixels object is null.");

        for (const auto &foodPos : _wallPositions)
            _pixels->getPixelMap()[foodPos] =
            Pixel(
                0,
                0,
                255,
                255,
                Pixel::PixelType::DEFAULT,
                '#'
            );
    }

    void Pacman::renderBackground()
    {
        if (_pixels == nullptr)
            throw arcade::Error("Pacman - renderBackground - Failed to render background: Pixels object is null.");

        int arenaWidth = _gameSettings["arenaWidth"];
        int arenaHeight = _gameSettings["arenaHeight"];

        for (int x = 1; x < arenaWidth - 1; ++x)
            for (int y = 1; y < arenaHeight - 1; ++y)
                _pixels->getPixelMap()[{x, y}] = Pixel(0, 0, 0);
    }

    void Pacman::renderScore()
    {
        int arenaWidth = _gameSettings["arenaWidth"] / 2;

        if (_texts == nullptr)
            throw arcade::Error("Pacman - renderScore - Failed to render score: Texts object is null.");

        if (_foodPositions.size() == 0)
            _texts->getTextMap()[{arenaWidth + 5, 17}] = Text("You Won !");
        _texts->getTextMap()[{arenaWidth - 10, 17}] = "Score: " + std::to_string(_score);
    }

    void Pacman::handleCollisions()
    {
        for (auto it = _foodPositions.begin(); it != _foodPositions.end(); ++it) {
            if (*it == _pacman) {
                ++_score;
                _foodPositions.erase(it);
                return;
            }
        }
        for (auto it = _gumgums.begin(); it != _gumgums.end(); ++it) {
            if (it->position == _pacman && it->state == GumGumState::VISIBLE) {
                _gumgumEat = true;
                _gumgumTime = 0.2f;
                _ghostsSpeed = 0.2f;
                it->timeBeforeRespawn = 10.0f * _accelerator;
                it->state = GumGumState::NONE;
                _score += 10;
                return;
            }
        }
        for (auto it = _ghosts.begin(); it != _ghosts.end(); ++it) {
            if (it->position == _pacman) {
                if (_gumgumEat) {
                    it->state = GhostState::DEAD;
                    it->timeBeforeRespawn = 5.0f * _accelerator;
                } else {
                    _isGameOver = true;
                }
                return;
            }
        }
    }
}
