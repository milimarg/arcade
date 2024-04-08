/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** IPixel
*/

#ifndef IPIXEL_HPP_
    #define IPIXEL_HPP_
    #include <string>

namespace arcade
{
    /**
     * IPixel Class
     */
    class IPixel {
        public:
            /**
             * Pixel Color
             */
            using Color = unsigned int;

            /**
             * Pixel Type
             */
            enum class PixelType {
                DEFAULT,
                TEXTURED,
                NONE,
            };

            /**
             * Pixel Rotation (in degrees)
             */
            enum class Rotation {
                R0,
                R90,
                R180,
                R270
            };

            virtual ~IPixel() = default;

            /**
             *
             * @return red color value
             */
            virtual Color getRed() const = 0;

            /**
             *
             * @return green color value
             */
            virtual Color getGreen() const = 0;

            /**
             *
             * @return blue color value
             */
            virtual Color getBlue() const = 0;

            /**
             *
             * @return alpha color value
             */
            virtual Color getAlpha() const = 0;

            /**
             *
             * @return char displayed for this pixel
             */
            virtual char getChar() const = 0;

            /**
             *
             * @return texture path
             */
            virtual std::string getTexturePath() const = 0;

            /**
             *
             * @return rotation of pixel (in degrees)
             */
            virtual Rotation getRotation() const = 0;

            /**
             *
             * @return type of pixel
             */
            virtual PixelType getType() const = 0;

            /**
             *
             * @return texture rectangle size
             */
            virtual std::pair<int, int> getRectSize() const = 0;

            /**
             *
             * @return texture rectangle position
             */
            virtual std::pair<int, int> getRectPosition() const = 0;

            /**
             * Sets red color value
             * @param red red value to apply
             */
            virtual void setRed(Color red) = 0;

            /**
             * Sets green color value
             * @param green green value to apply
             */
            virtual void setGreen(Color green) = 0;

            /**
             * Sets blue color value
             * @param blue blue value to apply
             */
            virtual void setBlue(Color blue) = 0;

            /**
             * Sets alpha color value
             * @param alpha alpha value to apply
             */
            virtual void setAlpha(Color alpha) = 0;

            /**
             * Sets character for this pixel
             * @param charValue character to display
             */
            virtual void setChar(char charValue) = 0;

            /**
             * Sets pixel texture path
             * @param path path of texture to apply
             */
            virtual void setTexturePath(const std::string &path) = 0;

            /**
             * Sets pixel rotation (in degrees)
             * @param rotation pixel rotation to apply
             */
            virtual void setRotation(Rotation rotation) = 0;

            /**
             * Sets Pixel Type
             * @param type pixel type to apply
             */
            virtual void setType(PixelType type) = 0;

            /**
             * Sets texture rectangle size
             * @param rectSize texture rectangle size
             */
            virtual void setRectSize(std::pair<int, int> rectSize) = 0;

            /**
             * Sets texture rectangle position
             * @param rectPosition texture rectangle position
             */
            virtual void setRectPosition(std::pair<int, int> rectPosition) = 0;

    };
}

#endif /* !IPIXEL_HPP_ */
