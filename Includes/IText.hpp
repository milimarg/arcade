/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** IText
*/

#ifndef ITEXT_HPP_
    #define ITEXT_HPP_
    #include <string>

namespace arcade
{
    /**
     * IText Class
     */
    class IText {
        public:
            /**
             * Color of Text
             */
            using Color = unsigned int;

            virtual ~IText() = default;

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
             * @return string value
             */
            virtual std::string getStr() const = 0;

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
             *
             * @param str string value
             */
            virtual void setStr(const std::string &str) = 0;
    };
}

#endif /* !ITEXT_HPP_ */
