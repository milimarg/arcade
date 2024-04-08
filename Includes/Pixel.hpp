/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** Pixel
*/

#ifndef PIXEL_HPP
    #define PIXEL_HPP
    #include "IPixel.hpp"

namespace arcade
{
    /**
     * Pixel Class
     */
    class Pixel : public IPixel {
        public:
            Pixel();

            /**
             * Creates pixel
             * @param red red color value
             * @param green green color value
             * @param blue blue color value
             * @param alpha alpha color value
             * @param pixelType type of pixel
             * @param charValue character displayed
             * @param texturePath texture path
             * @param rotation rotation of pixel (in degrees)
             * @param rectSize texture rectangle size
             * @param rectPosition texture rectangle position
             */
            Pixel(
                Color red,
                Color green,
                Color blue,
                Color alpha = 255,
                PixelType pixelType = PixelType::DEFAULT,
                char charValue = ' ',
                const std::string &texturePath = "",
                Rotation rotation = Rotation::R0,
                std::pair<int, int> rectSize = std::make_pair(0, 0),
                std::pair<int, int> rectPosition = std::make_pair(0, 0)
            );

            /**
             *
             * @return red color value
             */
            Color getRed() const override;

            /**
             *
             * @return green color value
             */
            Color getGreen() const override;

            /**
             *
             * @return blue color value
             */
            Color getBlue() const override;

            /**
             *
             * @return alpha color value
             */
            Color getAlpha() const override;

            /**
             *
             * @return char displayed for this pixel
             */
            char getChar() const override;

            /**
             *
             * @return texture path
             */
            std::string getTexturePath() const override;

            /**
             *
             * @return rotation of pixel (in degrees)
             */
            Rotation getRotation() const override;

            /**
             *
             * @return type of pixel
             */
            PixelType getType() const override;

            /**
             *
             * @return texture rectangle size
             */
            std::pair<int, int> getRectSize() const override;

            /**
             *
             * @return texture rectangle position
             */
            std::pair<int, int> getRectPosition() const override;

            /**
             * Sets red color value
             * @param red red value to apply
             */
            void setRed(Color red) override;

            /**
             * Sets green color value
             * @param green green value to apply
             */
            void setGreen(Color green) override;

            /**
             * Sets blue color value
             * @param blue blue value to apply
             */
            void setBlue(Color blue) override;

            /**
             * Sets alpha color value
             * @param alpha alpha value to apply
             */
            void setAlpha(Color alpha) override;

            /**
             * Sets character for this pixel
             * @param charValue character to display
             */
            void setChar(char charValue) override;

            /**
             * Sets pixel texture path
             * @param path path of texture to apply
             */
            void setTexturePath(const std::string &path) override;

            /**
             * Sets pixel rotation (in degrees)
             * @param rotation pixel rotation to apply
             */
            void setRotation(Rotation rotation) override;

            /**
             * Sets Pixel Type
             * @param type pixel type to apply
             */
            void setType(PixelType type) override;

            /**
             * Sets texture rectangle size
             * @param rectSize texture rectangle size
             */
            void setRectSize(std::pair<int, int> rectSize) override;

            /**
             * Sets texture rectangle position
             * @param rectPosition texture rectangle position
             */
            void setRectPosition(std::pair<int, int> rectPosition) override;

        private:
            Color _red;
            Color _green;
            Color _blue;
            Color _alpha;
            PixelType _type;
            char _char;
            std::string _texturePath;
            Rotation _rotation;
            std::pair<int, int> _rectSize;
            std::pair<int, int> _rectPosition;
    };
}

#endif /* !PIXEL_HPP */
