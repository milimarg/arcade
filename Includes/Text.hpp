/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Text
*/

#ifndef TEXT_HPP_
    #define TEXT_HPP_
    #include "IText.hpp"

namespace arcade
{
    /**
     * Class Text
     */
    class Text : public IText {
        public:
            Text();

            /**
             * Creates text giving only string
             * @param str string value
             */
            Text(const std::string &str);

            /**
             * Creates text giving string and color
             * @param str string value
             * @param red red value
             * @param green green value
             * @param blue blue value
             * @param alpha alpha value
             */
            Text(
                const std::string &str,
                Color red,
                Color green,
                Color blue,
                Color alpha = 255
            );

            /**
             *
             * @return red value
             */
            Color getRed() const override;

            /**
             *
             * @return green value
             */
            Color getGreen() const override;

            /**
             *
             * @return blue value
             */
            Color getBlue() const override;

            /**
             *
             * @return alpha value
             */
            Color getAlpha() const override;

            /**
             *
             * @return string
             */
            std::string getStr() const override;

            /**
             * Sets red value
             * @param red new red value
             */
            void setRed(Color red) override;

            /**
             * Sets green value
             * @param green new green value
             */
            void setGreen(Color green) override;

            /**
             * Sets blue value
             * @param blue new blue value
             */
            void setBlue(Color blue) override;

            /**
             * Sets alpha value
             * @param alpha new alpha value
             */
            void setAlpha(Color alpha) override;

            /**
             * Sets string
             * @param str string to assign
             */
            void setStr(const std::string &str) override;

        private:
            std::string _str;
            Color _red;
            Color _green;
            Color _blue;
            Color _alpha;
    };
}

#endif /* !TEXT_HPP_ */
