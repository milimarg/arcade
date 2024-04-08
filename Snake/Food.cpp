/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Food
*/

#include "Food.hpp"

namespace arcade
{
    Food::Food(FoodType type, std::pair<int, int> position)
    {
        std::unordered_map<FoodType, std::pair<int, int>> foodTypesTextureCoords =
        {
            {FoodType::DEFAULT, {48, 24}},
            {FoodType::RED_FRUIT, {48, 0}},
            {FoodType::GREEN_FRUIT, {48, 32}},
            {FoodType::YELLOW_FRUIT, {48, 8}},
            {FoodType::COOKIE, {56, 24}}
        };

        std::unordered_map<FoodType, int> foodTypeScore =
        {
            {FoodType::DEFAULT, 1},
            {FoodType::RED_FRUIT, 10},
            {FoodType::GREEN_FRUIT, 25},
            {FoodType::YELLOW_FRUIT, 2},
            {FoodType::COOKIE, 10}
        };

        std::vector<FoodType> foodTypeList =
        {
                FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT, FoodType::DEFAULT,
                FoodType::RED_FRUIT,
                FoodType::GREEN_FRUIT,
                FoodType::YELLOW_FRUIT,
                FoodType::COOKIE
        };

        std::unordered_map<FoodType, std::array<int, 4>> foodTypeColor =
        {
            {FoodType::DEFAULT, {255, 0, 77, 255}},
            {FoodType::RED_FRUIT, {127, 37, 83, 255}},
            {FoodType::GREEN_FRUIT, {0, 135, 81, 255}},
            {FoodType::YELLOW_FRUIT, {255, 163, 0, 255}},
            {FoodType::COOKIE, {171, 82, 54, 255}}
        };

        if (type == FoodType::RANDOM)
            _type = foodTypeList[(rand() % foodTypeList.size())];

        _textureCoords = foodTypesTextureCoords[_type];
        _score = foodTypeScore[_type];
        _position = position;
        _color = foodTypeColor[_type];
    }


    Food::~Food() {}

    Food::FoodType Food::getType() const
    {
        return _type;
    }

    std::pair<int, int> Food::getTextureCoords() const
    {
        return _textureCoords;
    }

    int Food::getScore() const
    {
        return _score;
    }

    std::pair<int, int> Food::getPosition() const
    {
        return _position;
    }

    std::array<int, 4> Food::getColor() const
    {
        return _color;
    }

    void Food::applyEffect(Player &snake)
    {
        switch (_type) {
            case FoodType::DEFAULT:
                snake.addBodyPart(1);
                break;
            case FoodType::RED_FRUIT:
                snake.addBodyPart(1);
                snake.setMoveSpeed(snake.getMoveSpeed() / 1.5, 10.0f);
                break;
            case FoodType::GREEN_FRUIT:
                snake.addBodyPart(1);
                snake.setIsReversed(!snake.getIsReversed());
                break;
            case FoodType::YELLOW_FRUIT:
                snake.addBodyPart(3);
                break;
            case FoodType::COOKIE:
                snake.addBodyPart(1);
                break;
            default:
                snake.addBodyPart(1);
                break;
        }
    }

    bool Food::operator==(const Food &food) const
    {
        return (_type == food._type && _textureCoords == food._textureCoords
        && _score == food._score && _position == food._position);
    }
}
