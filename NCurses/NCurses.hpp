/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** NCurses
*/

#ifndef NCurses_HPP_
    #define NCurses_HPP_

    #include "IGraphicalModule.hpp"
    #include "IGameModule.hpp"
    #include "Time.hpp"
    #include <queue>
    #include <ncurses.h>
    #include <string.h>
    #include <time.h>
    #include <cmath>
    #include "Pixels.hpp"
    #include "Texts.hpp"
    #define STB_IMAGE_IMPLEMENTATION
    #include "../Sources/Texture/Texture.hpp"
    #include <iostream>
    #include <fstream>
    #include <sstream>
    #include <unordered_map>
    #include <filesystem>

namespace arcade
{
    /**
     * NCurses Event
     */
    class Event : public IEvent {
        public:
            Event();
            ~Event();

            /**
             *
             * @return events info wrapper
             */
            std::unique_ptr<IEventInfo> getEvent() override;

            /**
             *
             * @return changeEvents info wrapper
             */
            std::unique_ptr<IEventInfo> getChangeEvent() override;

            /**
             * Push an event in the events queue
             * @param key event to push
             */
            void pushEvent(const Key &key) override;

            /**
             * Push an event in the events queue
             * @param key event to push
             * @param mouseCoords current mouse coordinates
             */
            void pushEvent(const Key &key, std::pair<int, int> mouseCoords) override;

            /**
             * Push a changeEvent in the changeEvents queue
             * @param changeKey changeEvent to push
             */
            void pushChangeEvent(const ChangeKey &changeKey) override;

            /**
             * Clears the events queue
             */
            void clearEventQueue() override;

            /**
             * Clears the ChangeEvents queue
             */
            void clearChangeEventQueue() override;

        private:
            std::queue<std::unique_ptr<IEventInfo>> _eventQueue;
            std::queue<std::unique_ptr<IEventInfo>> _changeEventQueue;
    };

    /**
     * NCurses Window
     */
    class Window : public IWindow {
        public:
            /**
             * View Mode
             */
            enum class ViewMode {
                STANDARD,
                DITHERING
            };

            Window();
            ~Window();

            /**
             * Init all colors and color pairs
             */
            void initColor();

            /**
             * Opens the window
             * @param width width of window
             * @param height height of window
             */
            void openWindow(int width, int height) override;

            /**
             * Closes the window
             */
            void closeWindow() override;

            /**
             * Resizes the window to a new resolution
             * @param width new width to apply
             * @param height new height to apply
             */
            void resizeWindow(int width, int height) override;

            /**
             *
             * @return is the window currently open?
             */
            bool isOpen() const override;

            /**
             * Clears the screen and the vertex array
             */
            void clearScreen() override;

            /**
             * Get distance between 2 colors
             * @param r red value of color 1
             * @param g blue value of color 1
             * @param b green value of color 1
             * @param pixel pixel representing color 2
             * @return distance between these 2 colors
             */
            double getDistanceColor(int r, int g, int b, Pixel pixel);

            /**
             * Get corresponding ncurses color with input color
             * @param r red value
             * @param g green value
             * @param b blue value
             * @return pair value corresponding to input color
             */
            int getPairColor(int r, int g, int b);

            /**
             * Display pixels in pixels wrapper
             * @param pixels pixels wrapper
             */
            void displayPixels(IPixels *pixels) override;

            /**
             * Displays a standard pixel
             * @param coords position of the pixel
             * @param pixel pixel to display
             * @param shiftX width of displayed pixel
             * @param shiftY height of displayed pixel
             */
            void displayDefaultPixel(const std::pair<int, int> &coords, const arcade::Pixel &pixel,
                                     int shiftX, int shiftY);

            /**
             * Displays a textured pixel
             * @param coords position of the pixel
             * @param pixel pixel to display
             */
            void displayTexturedPixel(const std::pair<int, int> &coords, const arcade::Pixel &pixel);

            /**
             * Displays texts in texts wrapper
             * @param texts texts wrapper
             */
            void displayTexts(ITexts *texts) override;

            /**
             * Displays one char
             * @param c char to display
             * @param currentX x position to start
             * @param currentY y position to start
             * @param x x position to move
             * @param y y position to move
             */
            void displayChar(char c, int &currentX, int &currentY, int &x, int &y);

            /**
             * Displays on screen
             */
            void display() override;

            /**
             *
             * @return view mode (standard or dithering)
             */
            ViewMode getViewMode() { return _viewMode; }

            /**
             *
             * @return can the screen be cleared?
             */
            bool getCanClear() { return _canClear; }

            /**
             * Sets viewMode status
             * @param viewMode view mode (standard or dithering)
             */
            void setViewMode(ViewMode viewMode) { _viewMode = viewMode; }

            /**
             * Sets canClear status
             * @param canClear can screen be cleared?
             */
            void setCanClear(bool canClear) { _canClear = canClear; }

            /**
             *
             * @param r red value
             * @param g green value
             * @param b blue value
             * @return rescaled input color
             */
            int getShadedColorPair(int r, int g, int b);

            /**
             *
             * @param x x position to compute
             * @param y y position to compute
             * @return converted window coordinates
             */
            std::pair<int, int> getWindowCoord(int x, int y);

            /**
             * Load a given font
             * @param directoryPath
             */
            void loadFont(const std::string &directoryPath);

            /**
             * Switch the Enhanced Dithering Mode
             */
            void toggleEnhancedDithering();

        private:
            int _windowHeightMin;
            int _windowWidthMin;
            WINDOW *_window;
            bool _isOpenFlag;
            std::unordered_map<std::string, Texture> _textureMap;
            const int _ditheringTextureSize = 4;
            ViewMode _viewMode = ViewMode::DITHERING;
            bool _enhancedDithering = false;
            int _currentDitheringTextureSize = 1;
            bool _canClear = false;
            int _intensityLevels;
            int _colorVariations;
            std::unordered_map<std::string, std::string> _font;
    };

    /**
     * NCurses Class
     */
    class NCurses : public IGraphicalModule {
        public:
            NCurses();
            ~NCurses();

            /**
             * Creates objects (events and window) and open window
             */
            void init() override;

            /**
             * Quits TTF library and close window
             */
            void stop() override;

            /**
             *
             * @return Module name
             */
            std::string getName() const override;

            /**
             *
             * @return Events wrapper
             */
            IEvent *getEventWrapper() const override;

            /**
             *
             * @return Window wrapper
             */
            IWindow *getWindowWrapper() const override;

            /**
             * Updates a pixels wrapper
             * @param pixels
             */
            void updatePixelsWrapper(IPixels *pixels) override;

            /**
             * Updates a texts wrapper
             * @param texts
             */
            void updateTextsWrapper(ITexts *texts) override;

            /**
             * Handle window quit event and pressed keys
             */
            void pollEvents() override;

            /**
             * Displays SDL renderer
             */
            void display() const override;
        protected:
            /**
             *
             * @return Events wrapper
             */
            IEvent *createEventObject() override;

            /**
             *
             * @return Window wrapper
             */
            IWindow *createWindowObject() override;

            /**
             * Pixels wrapper
             */
            IPixels *_pixels;

            /**
             * Texts wrapper
             */
            ITexts *_texts;

            /**
             * Events wrapper
             */
            std::unique_ptr<IEvent> _event;

            /**
             * Window wrapper
             */
            std::unique_ptr<IWindow> _window;

            /**
            * Keys map to store standard keys
            */
            std::unordered_map<unsigned char, Key> _keyTable;

            /**
            * Keys map to store special keys
            */
            std::unordered_map<unsigned char, Key> _specialKeyTable;

            /**
            * Keys map to store changeKeys (escape)
            */
            std::unordered_map<unsigned char, ChangeKey> _changeKeyTable;

            /**
            * Keys map to store special changeKeys (go to main menu, switch games, switch graphics libraries)
            */
            std::unordered_map<unsigned char, ChangeKey> _specialChangeKeyTable;
    };
}

extern "C" {
    std::string getType() {
        return "graphical";
    }

    std::unique_ptr<arcade::IGraphicalModule> entryPoint() {
        return std::make_unique<arcade::NCurses>();
    }
}

#endif /* !NCurses_HPP_ */
