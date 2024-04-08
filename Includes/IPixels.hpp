/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** IPixels
*/

#ifndef IPIXELS_HPP_
    #define IPIXELS_HPP_
    #include <unordered_map>
    #include "Pixel.hpp"

namespace arcade
{
    typedef std::unordered_map<std::pair<int, int>, Pixel> PixelsMap;

    /**
     * IPixels Class
     */
    class IPixels {
        public:
            virtual ~IPixels() = default;

            /**
             *
             * @return pixels wrapper
             */
            virtual PixelsMap &getPixelMap() = 0;

            /**
             * Updates pixels wrapper content
             * @param pixels pixels wrapper
             */
            virtual void updatePixelMap(const PixelsMap &pixels) = 0;
    };
}

#endif /* !IPIXELS_HPP_ */
