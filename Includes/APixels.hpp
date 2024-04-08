/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** APixels
*/

#ifndef APIXELS_HPP_
    #define APIXELS_HPP_
    #include "Pair.hpp"
    #include "IPixels.hpp"

namespace arcade
{
    /**
     * Apixels Class
     */
    class APixels : public IPixels {
        public:
            APixels();
            ~APixels();

            /**
             *
             * @return pixels wrapper
             */
            PixelsMap &getPixelMap() override;

            /**
             * Update pixels wrapper (only content of wrapper will be copied)
             * @param pixels new pixels wrapper
             */
            void updatePixelMap(const PixelsMap &pixels) override;

        private:
            PixelsMap _pixelMap;
    };
}

#endif /* !APIXELS_HPP_ */
