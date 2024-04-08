/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** ITexts
*/

#ifndef ITEXTS_HPP_
    #define ITEXTS_HPP_
    #include <unordered_map>
    #include <string>
    #include "Text.hpp"

namespace arcade
{
    typedef std::unordered_map<std::pair<int, int>, Text> TextMap;

    /**
     * ITexts Class
     */
    class ITexts {
        public:
            virtual ~ITexts() = default;

            /**
             *
             * @return texts wrapper
             */
            virtual TextMap &getTextMap() = 0;

            /**
             * Updates texts wrapper content
             * @param texts texts wrapper
             */
            virtual void updateTextMap(const TextMap &texts) = 0;
    };
}

#endif /* !ITEXTS_HPP_ */
