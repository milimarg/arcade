/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** MapWrapper.cpp
*/

#include "MapWrapper.hpp"

MapWrapper::MapWrapper()
{
}

MapWrapper::~MapWrapper()
{
}

void MapWrapper::parseMap(const std::string &filepath)
{
    std::ifstream in(filepath);
    std::string line;
    Map map;

    while (std::getline(in, line)) {
        int x = 0;
        for (auto &c : line) {
            if (c == '#') {
                map.getCollectiblesMap()[{x, map.getRacksSizeY()}] = true;
                map.setNumber(map.getNumber() + 1);
            }
            x += 1;
        }
        map.setRacksSizeX(x);
        map.setRacksSizeY(map.getRacksSizeY() + 1);
    }
    _maps.push_back(map);
    in.close();
}
