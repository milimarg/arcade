/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Snake
*/

#include "Snake.hpp"

namespace arcade
{
    Snake::Snake() :
        AGameModule("Snake"),
        _score(0),
        _isGameOver(false),
        _gameSettings(),
        _timeBank(0.0f),
        _toReload(false),
        _arenaTextureCoords(),
        _foodMap(),
        _beforeReload(-1.0f),
        _backgroundColors({{169, 216, 81, 255}, {163, 208, 74, 255}}),
        _trueDirection(0),
        _isDevModeOn(false)
    {
        std::srand(std::time(nullptr));
    }

    Snake::~Snake() {}

    void Snake::init()
    {
        _score = 0;
        _isGameOver = false;

        _snake.setDirection(Player::Direction::RIGHT);
        _snake.setNextDirection(Player::Direction::RIGHT);

        _beforeReload = -1.0f;

        _gameSettings["arenaWidth"] = 50;
        _gameSettings["arenaHeight"] = 50;
        _gameSettings["foodQuantity"] = 50;
        _gameSettings["initialSnakeX"] = _gameSettings["arenaWidth"] / 2;
        _gameSettings["initialSnakeY"] = _gameSettings["arenaHeight"] / 2;

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

        int initialX = _gameSettings["initialSnakeX"];
        int initialY = _gameSettings["initialSnakeY"];

        _snake.init({initialX, initialY});
        _snake.addBodyPart(3);

        for (int i = 0; i < _gameSettings["foodQuantity"]; ++i)
            spawnFood();
    }

    void Snake::stop()
    {
        _snake.resetBody();
        _snake.resetMoveSpeed();
        _snake.setIsReversed(false);
        _gameSettings.clear();
        _foodMap.clear();
        _timeBank = 0.0f;
    }

    void Snake::applyEvents(IEvent *eventWrapper)
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

    void Snake::update(float deltaTime)
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

        if (_pixels == nullptr)
            throw arcade::Error("Snake - update - Failed to update pixels: Pixels object is null.");

        _pixels->getPixelMap().clear();

        _snake.updateTime(deltaTime);

        float moveSpeed = _snake.getMoveSpeed();

        if (_timeBank >= moveSpeed) {
            _snake.updatePosition();
            handleCollisions();
            _timeBank -= moveSpeed;
        }

        renderBackground();
        renderArena();
        renderFood();
        renderSnake();
        renderScore();
    }

    void Snake::reload()
    {
        stop();
        init();
    }

    int Snake::getScore()
    {
        return _score;
    }

    void Snake::draw(IGraphicalModule *graphicalModule)
    {
        graphicalModule->updatePixelsWrapper(_pixels.get());
        graphicalModule->updateTextsWrapper(_texts.get());
        graphicalModule->display();
    }

    void Snake::applyEvent(const Key &key)
    {
        switch (key) {
            case Key::R_KEY:
                _toReload = true;
                break;
            case Key::D_KEY:
                _isDevModeOn = !_isDevModeOn;
                break;
            default:
                handleSnakeDirectionChange(key);
                break;
        }
    }

    void Snake::renderSnake()
    {
        if (_pixels == nullptr)
            throw arcade::Error("Snake - renderSnake - Failed to render pixels: Pixels object is null.");

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

    bool Snake::checkFoodPosition(std::pair<int, int> checkedPos)
    {
        for (const auto &food : _foodMap)
            if (food.getPosition() == checkedPos)
                return true;
        return false;
    }

    void Snake::spawnFood()
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
            checkFoodPosition({foodX, foodY})
        );

        _foodMap.push_back(Food(Food::FoodType::RANDOM, {foodX, foodY}));
    }

    void Snake::renderFood()
    {
        if (_pixels == nullptr)
            throw arcade::Error("Snake - renderFood - Failed to render pixels: Pixels object is null.");

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

    void Snake::renderArena()
    {
        if (_pixels == nullptr)
            throw arcade::Error("Snake - renderArena - Failed to render pixels: Pixels object is null.");

        int arenaWidth = _gameSettings["arenaWidth"];
        int arenaHeight = _gameSettings["arenaHeight"];

        for (int x = 0; x < arenaWidth; ++x) {
            _pixels->getPixelMap()[{x, 0}] =
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

            _pixels->getPixelMap()[{x, arenaHeight - 1}] =
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
                std::make_pair(64, 16)
            );
        }

        for (int y = 0; y < arenaHeight; ++y) {
            _pixels->getPixelMap()[{0, y}] =
            Pixel(
                255,
                0,
                77,
                255,
                Pixel::PixelType::TEXTURED,
                '|',
                "Assets/Snake/snake.png",
                Pixel::Rotation::R0,
                std::make_pair(8, 8),
                std::make_pair(56, 16)
            );

            _pixels->getPixelMap()[{arenaWidth - 1, y}] =
            Pixel(
                255,
                0,
                77,
                255,
                Pixel::PixelType::TEXTURED,
                '|',
                "Assets/Snake/snake.png",
                Pixel::Rotation::R0,
                std::make_pair(8, 8),
                std::make_pair(80, 16)
            );
        }
    }

    void Snake::renderBackground()
    {
        if (_pixels == nullptr)
            throw arcade::Error("Snake - renderBackground - Failed to render pixels: Pixels object is null.");

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

    void Snake::renderScore()
    {
        if (_texts == nullptr)
            throw arcade::Error("Snake - renderScore - Failed to render texts: Texts object is null.");


        std::string scoreStr = "Score: " + std::to_string(_score);

        _texts->getTextMap()[{2, 2}] = scoreStr;
    }

    void Snake::updateTrueDirection(int changeValue, Player::Direction snakeDirection)
    {
        _trueDirection = static_cast<int>(snakeDirection);
        _trueDirection += changeValue;
        if (_trueDirection < 0)
            _trueDirection = 3;
        else if (_trueDirection == 4)
            _trueDirection = 0;
        _snake.setNextDirection(static_cast<Player::Direction>(_trueDirection));
    }

    void Snake::handleSnakeDirectionChange(const Key &key)
    {
        Player::Direction snakeDirection = _snake.getDirection();
        int reversedOffset = 1;

        if (_snake.getIsReversed())
            reversedOffset = -1;

        if (!_isDevModeOn) {
            if (key == Key::LEFT_ARROW) {
                updateTrueDirection(-1 * reversedOffset, snakeDirection);
                return;
            }
            if (key == Key::RIGHT_ARROW) {
                updateTrueDirection(1 * reversedOffset, snakeDirection);
                return;
            }
            return;
        }

        if (!Snake::_playerDirection.contains(key))
            return;

        if (reversedOffset == -1) {
            if (Snake::_playerDirection.at(key).first != snakeDirection)
                _snake.setNextDirection(Snake::_playerDirection.at(key).second);
        } else {
            if (Snake::_playerDirection.at(key).second != snakeDirection)
                _snake.setNextDirection(Snake::_playerDirection.at(key).first);
        }
    }

    void Snake::handleCollisions()
    {
        std::pair<int, int> head = _snake.getHead();
        int headX = head.first;
        int headY = head.second;

        int arenaWidth = _gameSettings["arenaWidth"];
        int arenaHeight = _gameSettings["arenaHeight"];

        if (headX <= 0 || headX >= arenaWidth - 1 || headY <= 0 || headY >= arenaHeight - 1) {
            _isGameOver = true;
            _beforeReload = 3.0f;
            return;
        }

        for (auto &food : _foodMap) {
            if (food.getPosition() == std::make_pair(headX, headY)) {
                _score += food.getScore();

                food.applyEffect(_snake);

                const auto &foodPosition = std::find(_foodMap.begin(), _foodMap.end(), food);
                _foodMap.erase(foodPosition);

                spawnFood();

                return;
            }
        }

        if (_snake.collideWithBody(head)) {
            _isGameOver = true;
            _beforeReload = 3.0f;
            return;
        }
    }

    const std::unordered_map<Key, std::pair<Player::Direction, Player::Direction>> Snake::_playerDirection = {
        {Key::UP_ARROW, {Player::Direction::UP, Player::Direction::DOWN}},
        {Key::DOWN_ARROW, {Player::Direction::DOWN, Player::Direction::UP}},
        {Key::LEFT_ARROW, {Player::Direction::LEFT, Player::Direction::RIGHT}},
        {Key::RIGHT_ARROW, {Player::Direction::RIGHT, Player::Direction::LEFT}}
    };
}
