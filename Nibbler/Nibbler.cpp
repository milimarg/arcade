/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Nibbler
*/

#include "Nibbler.hpp"

namespace arcade
{
    Nibbler::Nibbler() :
        AGameModule("Nibbler"),
        _score(0),
        _isGameOver(false),
        _gameSettings(),
        _timeBank(0.0f),
        _toReload(false),
        _arenaTextureCoords(),
        _foodMap(),
        _beforeReload(-1.0f),
        _backgroundColors({{169, 216, 81, 255}, {163, 208, 74, 255}}),
        _currentSpeedIncrease(0.0f)
    {
        std::srand(std::time(nullptr));

        _gameSettings["arenaWidth"] = 50;
        _gameSettings["arenaHeight"] = 50;
        _gameSettings["foodQuantity"] = 50;
        _gameSettings["initialNibblerX"] = _gameSettings["arenaWidth"] / 2;
        _gameSettings["initialNibblerY"] = _gameSettings["arenaHeight"] / 2;

        initWallMapFromFile("Maps/Nibbler/nibbler.map");
    }

    Nibbler::~Nibbler() {}

    void Nibbler::initSnake()
    {
        int initialX = _gameSettings["arenaWidth"] / 2;
        int initialY = _gameSettings["arenaHeight"] - 2;

        Player::Direction initialDirection = Player::Direction::RIGHT;

        _snake = Player(4, initialDirection);

        _snake.init({initialX, initialY});
        _snake.addBodyPart(3);
    }

    void Nibbler::initWallMapFromFile(const std::string &filename)
    {
        std::ifstream file(filename);
        std::string line;
        int row = 0;
        int col = 0;
        int arenaWidth = _gameSettings["arenaWidth"];
        int arenaHeight = _gameSettings["arenaHeight"];

        if (!file.is_open()) {
            std::cerr << "Error: Unable to open map file: " << filename << std::endl;
            return;
        }

        while (std::getline(file, line)) {
            col = 0;

            for (char &c : line) {
                if (c == 'X')
                    _walls[{col, row}] = false;
                ++col;
                if (col >= arenaWidth)
                    break;
            }
            ++row;
            if (row >= arenaHeight)
                break;
        }

        file.close();

        for (int x = 0; x < arenaWidth; ++x) {
            _walls[{x, 0}] = true;
            _walls[{x, arenaHeight - 1}] = true;
        }

        for (int y = 0; y < arenaHeight; ++y) {
            _walls[{0, y}] = true;
            _walls[{arenaWidth - 1, y}] = true;
        }
    }

    void Nibbler::init()
    {
        _score = 0;
        _isGameOver = false;

        _beforeReload = -1.0f;

        std::vector<std::pair<int, int>> tempArenaTextureCoords =
        {
            {72, 0},
            {80, 0},
            {88, 0},
            {72, 8},
            {80, 8},
            {88, 8},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
            {80, 80},
        };

        int textureCoordindex = 0;

        for (int x = 1; x < _gameSettings["arenaWidth"] - 1; ++x) {
            for (int y = 1; y < _gameSettings["arenaHeight"] - 1; ++y) {
                textureCoordindex = std::rand() % tempArenaTextureCoords.size();

                _arenaTextureCoords[{x, y}] = tempArenaTextureCoords[textureCoordindex];
            }
        }

        createPixelsObject();
        createTextsObject();

        initSnake();

        for (int i = 0; i < _gameSettings["foodQuantity"]; ++i)
            spawnFood();
    }

    void Nibbler::stop()
    {
        _foodMap.clear();
        _timeBank = 0.0f;
    }

    void Nibbler::applyEvents(IEvent *eventWrapper)
    {
        Key key = Key::KEY_LIST_END;

        while (1) {
            std::unique_ptr<IEventInfo> tempEventInfo = eventWrapper->getEvent();
            if (!tempEventInfo)
                break;
            key = tempEventInfo->getKey();
            if (key == Key::KEY_LIST_END || key == Key::NONE)
                break;
            applyEvent(key);
        }
    }

    void Nibbler::update(float deltaTime)
    {
        if (_toReload) {
            _toReload = false;
            reload();
        }

        _timeBank += deltaTime;

        if (_isGameOver) {
            if (_beforeReload >= 0.0f) {
                _beforeReload -= deltaTime;
                return;
            }
            _isGameOver = false;
            reload();
        }

        if (_pixels == nullptr) {
            std::cerr << "update - render issue - Pixels is null" << std::endl;
            return;
        }

        _pixels->getPixelMap().clear();
        _snake.updateTime(deltaTime);

        float moveSpeed = _snake.getMoveSpeed();

        if (_timeBank >= moveSpeed) {
            _snake.updatePosition(_walls);
            handleCollisions();
            _timeBank -= moveSpeed;
        }

        renderBackground();
        renderArena();
        renderFood();
        renderNibbler();
        renderScore();
    }

    void Nibbler::reload()
    {
        stop();
        init();
    }

    int Nibbler::getScore()
    {
        return _score;
    }

    void Nibbler::draw(IGraphicalModule *graphicalModule)
    {
        graphicalModule->updatePixelsWrapper(_pixels.get());
        graphicalModule->updateTextsWrapper(_texts.get());
        graphicalModule->display();
    }

    void Nibbler::applyEvent(const Key &key)
    {
        switch (key) {
            case Key::R_KEY:
                _toReload = true;
                break;
            default:
                if (Nibbler::_playerDirection.contains(key))
                    handleNibblerDirectionChange(key);
                break;
        }
    }

    void Nibbler::renderNibbler()
    {
        if (_pixels == nullptr) {
            std::cerr << "snake - render issue - Pixels is null" << std::endl;
            return;
        }

        std::pair<int, int> snakeHeadPosition = {0, 24};

        switch (_snake.getDirection()) {
            case Player::Direction::UP:
                snakeHeadPosition.first = 8;
                break;
            case Player::Direction::LEFT:
                snakeHeadPosition.first = 16;
                break;
            case Player::Direction::DOWN:
                snakeHeadPosition.first = 24;
                break;
            case Player::Direction::RIGHT:
                snakeHeadPosition.first = 32;
                break;
            default:
                break;
        }

        _pixels->getPixelMap()[_snake.getHead()] =
        Pixel(
                32,
                50,
                0,
                255,
            Pixel::PixelType::TEXTURED,
            '$',
            "Assets/Snake/snake.png",
            Pixel::Rotation::R0,
            {8, 8},
            snakeHeadPosition
        );

        std::deque<std::pair<int, int>>::const_iterator it = _snake.getTailIt();

        for (; it != _snake.getEndIt(); ++it) {
            const auto &segment = *it;
            _pixels->getPixelMap()[segment] =
            Pixel(
                64,
                86,
                23,
                255,
                Pixel::PixelType::TEXTURED,
                'O',
                "Assets/Snake/snake.png",
                Pixel::Rotation::R0,
                {8, 8},
                {40, 24}
            );

        }
    }

    bool Nibbler::checkFoodPosition(std::pair<int, int> checkedPos)
    {
        for (const auto &food : _foodMap)
            if (food.getPosition() == checkedPos)
                return true;
        return false;
    }

    void Nibbler::spawnFood()
    {
        int arenaWidth = _gameSettings["arenaWidth"];
        int arenaHeight = _gameSettings["arenaHeight"];

        int foodX = 0;
        int foodY = 0;

        do {
            foodX = 1 + std::rand() % (arenaWidth - 2);
            foodY = 1 + std::rand() % (arenaHeight - 2);
        } while (
            _snake.collideWithBody({foodX, foodY}) ||
            _walls.contains({foodX, foodY}) ||
            checkFoodPosition({foodX, foodY})
        );

        _foodMap.push_back(Food(Food::FoodType::RANDOM, {foodX, foodY}));
    }

    void Nibbler::renderFood()
    {
        if (_pixels == nullptr) {
            std::cerr << "food - render issue - Pixels is null" << std::endl;
            return;
        }

        for (const auto &food : _foodMap) {
            std::array<int, 4> foodColor = food.getColor();

            _pixels->getPixelMap()[food.getPosition()] =
            Pixel(
                foodColor[0],
                foodColor[1],
                foodColor[2],
                foodColor[3],
                Pixel::PixelType::TEXTURED,
                'F',
                "Assets/Snake/snake.png",
                Pixel::Rotation::R0,
                std::make_pair(8, 8),
                food.getTextureCoords()
            );
        }
    }

    void Nibbler::renderArena()
    {
        if (_pixels == nullptr) {
            std::cerr << "arena - render issue - Pixels is null" << std::endl;
            return;
        }

        for (auto &wall : _walls) {
            if (wall.second) {
                _pixels->getPixelMap()[wall.first] =
                Pixel(
                    255,
                    0,
                    77,
                    255,
                    Pixel::PixelType::TEXTURED,
                    '-',
                    "Assets/Snake/snake.png",
                    Pixel::Rotation::R0,
                    std::make_pair(8, 8),
                    std::make_pair(72, 16)
                );
            } else {
                _pixels->getPixelMap()[wall.first] =
                Pixel(
                    255,
                    0,
                    77,
                    255,
                    Pixel::PixelType::TEXTURED,
                    '-',
                    "Assets/Snake/snake.png",
                    Pixel::Rotation::R0,
                    std::make_pair(8, 8),
                    std::make_pair(72, 16)
                );

            }
        }
    }

    void Nibbler::renderBackground()
    {
        if (_pixels == nullptr) {
            std::cerr << "background - render issue - Pixels is null" << std::endl;
            return;
        }

        int arenaWidth = _gameSettings["arenaWidth"];
        int arenaHeight = _gameSettings["arenaHeight"];

        for (int x = 1; x < arenaWidth - 1; ++x) {
            for (int y = 1; y < arenaHeight - 1; ++y) {
                _pixels->getPixelMap()[{x, y}] =
                Pixel(
                    _backgroundColors.first[0],
                    _backgroundColors.first[1],
                    _backgroundColors.first[2],
                    _backgroundColors.first[3],
                    Pixel::PixelType::TEXTURED,
                    ' ',
                    "Assets/Snake/snake.png",
                    Pixel::Rotation::R0,
                    std::make_pair(8, 8),
                    _arenaTextureCoords[{x, y}]
                );
            }
        }
    }

    void Nibbler::renderScore()
    {
        if (_texts == nullptr) {
            std::cerr << "score - render issue - texts wrapper is null." << std::endl;
            return;
        }

        std::string scoreStr = "Score: " + std::to_string(_score);

        _texts->getTextMap()[{2, 2}] = scoreStr;
    }

    void Nibbler::handleNibblerDirectionChange(const Key &key)
    {
        Player::Direction snakeDirection = _snake.getDirection();

        if (_snake.getIsBlocked())
            return;

        if (_snake.getIsReversed()) {
            if (Nibbler::_playerDirection.at(key).first != snakeDirection)
                _snake.setNextDirection(Nibbler::_playerDirection.at(key).second);
        } else {
            if (Nibbler::_playerDirection.at(key).second != snakeDirection)
                _snake.setNextDirection(Nibbler::_playerDirection.at(key).first);
        }

        _snake.setIsStopped(false);
    }

    void Nibbler::handleCollisions()
    {
        std::pair<int, int> head = _snake.getHead();
        int headX = head.first;
        int headY = head.second;

        for (auto &food : _foodMap) {
            if (food.getPosition() == std::make_pair(headX, headY)) {
                _score += food.getScore();

                food.applyEffect(_snake);

                const auto &foodPosition = std::find(_foodMap.begin(), _foodMap.end(), food);
                _foodMap.erase(foodPosition);

                if (!_foodMap.size()) {
                    _gameSettings["foodQuantity"] += 1 + _gameSettings["foodQuantity"] / 10;
                    reload();
                    _snake.increaseBaseMoveSpeed(0.02f);
                }
                return;
            }
        }

        if (_snake.collideWithBody(head)) {
            _isGameOver = true;
            _beforeReload = 3.0f;
            return;
        }
    }

    const std::unordered_map<Key, std::pair<Player::Direction, Player::Direction>> Nibbler::_playerDirection = {
        {Key::UP_ARROW, {Player::Direction::UP, Player::Direction::DOWN}},
        {Key::DOWN_ARROW, {Player::Direction::DOWN, Player::Direction::UP}},
        {Key::LEFT_ARROW, {Player::Direction::LEFT, Player::Direction::RIGHT}},
        {Key::RIGHT_ARROW, {Player::Direction::RIGHT, Player::Direction::LEFT}}
    };
}
