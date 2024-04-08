/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Map.hpp
*/

#ifndef B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_MAP_HPP
    #define B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_MAP_HPP
    #include <unordered_map>
    #include "Pair.hpp"

typedef std::unordered_map<std::pair<int, int>, bool> collectiblesMap;

/**
 * Map Class
 */
class Map {
public:
    Map() :
        _racksSizeX(0),
        _racksSizeY(0),
        _number(0) {}
    ~Map() {}

    /**
     *
     * @return collectibles wrapper
     */
    collectiblesMap &getCollectiblesMap() { return _collectibles; }

    /**
     *
     * @return width of collectibles grid
     */
    int getRacksSizeX() const { return _racksSizeX; }

    /**
     *
     * @return height of collectibles grid
     */
    int getRacksSizeY() const { return _racksSizeY; }

    /**
     *
     * @return number of collectibles
     */
    int getNumber() const { return _number; }

    /**
     * Sets a new collectibles wrapper
     * @param map collectibles wrapper
     */
    void setCollectiblesMap(collectiblesMap &map) { _collectibles = map; }

    /**
     * Sets width of collectibles grid
     * @param racksSizeX collectibles grid
     */
    void setRacksSizeX(int racksSizeX) { _racksSizeX = racksSizeX; }

    /**
     * Sets height of collectible grid
     * @param racksSizeY collectibles grid
     */
    void setRacksSizeY(int racksSizeY) { _racksSizeY = racksSizeY; }

    /**
     * Sets number of collectibles
     * @param number number of collectibles
     */
    void setNumber(int number) { _number = number; }

private:
    collectiblesMap _collectibles;
    int _racksSizeX;
    int _racksSizeY;
    int _number;
};

#endif //B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_MAP_HPP
