/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** MapWrapper.hpp
*/

#ifndef B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_MAPWRAPPER_HPP
    #define B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_MAPWRAPPER_HPP
    #include "Map.hpp"
    #include <vector>
    #include <iostream>
    #include <fstream>

/**
 * MapWrapper Class
 */
class MapWrapper {
public:
    MapWrapper();
    ~MapWrapper();

    /**
     * Parse given map and store collectible positions
     * @param filepath map filepath
     */
    void parseMap(const std::string &filepath);

    /**
     *
     * @param index map index
     * @return map at given index
     */
    Map &at(const size_t index) { return _maps[index]; }

private:
    std::vector<Map> _maps;
};

#endif //B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_MAPWRAPPER_HPP
