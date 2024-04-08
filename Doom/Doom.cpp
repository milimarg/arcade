/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Doom
*/

#include "Doom.hpp"
#include <dlfcn.h>

namespace arcade
{
    Doom::Doom() :
        AGameModule("Doom"),
        _score(0),
        _isGameOver(false),
        _timeBank(0.0f),
        _keyTable ({
            Key::W_KEY,
            Key::S_KEY,
            Key::LEFT_ARROW,
            Key::RIGHT_ARROW,
            Key::P_KEY,
            Key::M_KEY,
            Key::UP_ARROW,
            Key::DOWN_ARROW,
            Key::B_KEY,
            Key::N_KEY
        })
    {
    }

    Doom::~Doom() {}

    void Doom::init()
    {
        createPixelsObject();
        createTextsObject();

        _filepath = "./Maps/Doom/example_config";
        _world = std::move(create_world((char *)_filepath.c_str(), RAW_CONFIG, 10, (id_Vec2){192, 168}));
        if (_world == nullptr)
            throw arcade::Error("Doom - init - world creation failed.");
    }

    void Doom::stop()
    {
    }

    void Doom::applyEvents(IEvent *eventWrapper)
    {
        Key key = Key::KEY_LIST_END;

        for (auto &element : _actions)
            element = false;

        while (1) {
            std::unique_ptr<IEventInfo> tempEventInfo = eventWrapper->getEvent();
            if (!tempEventInfo)
                break;
            key = tempEventInfo->getKey();
            if (key == Key::KEY_LIST_END || key == Key::NONE)
                break;
            applyEvent(key);
            reload_world(*_world, (char *)_filepath.c_str(), key == Key::R_KEY);
        }
    }

    void Doom::update(float deltaTime)
    {
        _timeBank += deltaTime;

        PixelsMap &map = getPixelsWrapper()->getPixelMap();

        map.clear();
        clear_points(*_world);

        move_player(*_world, _actions);
        display_world(*_world);

        for (auto &point : _world->points) {
            const int x = point.first.first;
            const int y = point.first.second;
            const id_vertex v = point.second;

            map[{x, y}] =
                Pixel(
                        v.color.r,
                        v.color.g,
                        v.color.b,
                        255,
                        Pixel::PixelType::DEFAULT,
                        '.'
                );
        }

        map[{_world->win_size.x, 0}] =
                Pixel(
                        0,
                        0,
                        0,
                        255,
                        Pixel::PixelType::DEFAULT,
                        '.'
                );

        map[{0, _world->win_size.y}] =
                Pixel(
                        0,
                        0,
                        0,
                        255,
                        Pixel::PixelType::DEFAULT,
                        '.'
                );
    }

    void Doom::reload()
    {
        stop();
        init();
    }

    int Doom::getScore()
    {
        return _score;
    }

    void Doom::draw(IGraphicalModule *graphicalModule)
    {
        graphicalModule->updatePixelsWrapper(_pixels.get());
        graphicalModule->updateTextsWrapper(_texts.get());
        graphicalModule->display();
    }

    void Doom::applyEvent(const Key &key)
    {
        auto it = std::find(_keyTable.begin(), _keyTable.end(), key);

        if (it == _keyTable.end())
            return;
        _actions[it - _keyTable.begin()] = true;
    }
}
