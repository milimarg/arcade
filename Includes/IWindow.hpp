/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** IWindow
*/

#ifndef IWINDOW_HPP_
    #define IWINDOW_HPP_

namespace arcade
{
    class IPixels;
    class ITexts;

    /**
     * IWindow Class
     */
    class IWindow {
        public:
            virtual ~IWindow() = default;

            /**
             * Opens a window
             * @param width window width
             * @param height window height
             */
            virtual void openWindow(int width, int height) = 0;

            /**
             * Closes window
             */
            virtual void closeWindow() = 0;

            /**
             * Resizes window to a new resolution
             * @param width new window width
             * @param height new window height
             */
            virtual void resizeWindow(int width, int height) = 0;

            /**
             *
             * @return is window still open?
             */
            virtual bool isOpen() const = 0;

            /**
             * Clears window screen
             */
            virtual void clearScreen() = 0;

            /**
             * Displays pixels in pixels wrapper
             * @param pixels pixels wrapper
             */
            virtual void displayPixels(IPixels *pixels) = 0;

            /**
             * Displays texts in texts wrapper
             * @param texts texts wrapper
             */
            virtual void displayTexts(ITexts *texts) = 0;

            /**
             * Displays elements
             */
            virtual void display() = 0;
    };
}

#endif /* !IWINDOW_HPP_ */
