/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** GraphicalWindow
*/

#ifndef GRAPHICALWINDOW_HPP_
    #define GRAPHICALWINDOW_HPP_
    #include "IWindow.hpp"

namespace arcade
{
    /**
     * GraphicalWindow Class
     */
    class GraphicalWindow : public IWindow {
        public:
            GraphicalWindow();

            /**
             *
             * @return pixel size on X axis
             */
            int getCurrentPixelSizeX() const;

            /**
             *
             * @return pixel size on Y axis
             */
            int getCurrentPixelSizeY() const;

        protected:
            /**
             * Pixel size on X axis
             */
            int _currentPixelSizeX;

            /**
             * Pixel size on Y axis
             */
            int _currentPixelSizeY;
    };
}

#endif /* !GRAPHICALWINDOW_HPP_ */
