/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Pair.hpp
*/

#ifndef B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_PAIR_HPP
    #define B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_PAIR_HPP
    #include <iostream>

namespace std {
    template <>
    /**
     * Custom struct for hash function
     */
    struct hash<std::pair<int, int>> {
        /**
         * Custom hash function to let unordered map have std::pair as key.
         */
        size_t operator()(const std::pair<int, int>& p) const {
            return hash<int>()(p.first) ^ hash<int>()(p.second);
        }
    };
}

#endif //B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_PAIR_HPP
