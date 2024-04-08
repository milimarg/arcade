/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** SFML
*/

#ifndef SFML_HPP_
    #define SFML_HPP_

    #include "IGraphicalModule.hpp"
    #include "IGameModule.hpp"
    #include "GraphicalWindow.hpp"
    #include <queue>
    #include <SFML/System.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include "Pixels.hpp"
    #include "Texts.hpp"

namespace arcade
{
    /**
     * Event SFML
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
     * Window SFML
     */
    class Window : public GraphicalWindow {
        public:
            Window();
            ~Window();

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
             * Display pixels in pixels wrapper
             * @param pixels pixels wrapper
             */
            void displayPixels(IPixels *pixels) override;

            /**
             * Displays a standard pixel
             * @param coords position of the pixel
             * @param pixel pixel to display
             */
            void displayDefaultPixel(const std::pair<int, int> &coords, const arcade::Pixel &pixel);

            /**
             * Displays a textured pixel
             * @param coords position of the pixel
             * @param pixel pixel to display
             */
            void displayTexturedPixel(const std::pair<int, int> &coords, const arcade::Pixel &pixel);

            /**
             * Displays texts of texts wrapper
             * @param texts
             */
            void displayTexts(ITexts *texts) override;

            /**
             * Displays render window
             */
            void display() override;

            /**
             *
             * @return current render window
             */
            sf::RenderWindow &getRenderWindow();

        private:
            int _windowWidth;
            int _windowHeight;
            bool _isOpenFlag;
            sf::RenderWindow _window;
            sf::VertexArray _vertexArray;
            sf::Font _currentFont;
            bool _fontLoaded = false;
            std::unordered_map<std::string, sf::Texture> _textureMap;
    };

    /**
     * SFML Class
     */
    class SFML : public IGraphicalModule {
        public:
            SFML();
            ~SFML();

            /**
             * Creates objects (events and window), open a window
             */
            void init() override;

            /**
             * Close the window
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
             * Calls window display
             */
            void display() const override;

        protected:
            /**
             * Events wrapper
             * @return
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
            std::unordered_map<sf::Keyboard::Key, Key> _keyTable;

            /**
             * Keys map to store changeKeys (go to main menu, switch games, switch graphics libraries)
             */
            std::unordered_map<sf::Keyboard::Key, ChangeKey> _changeKeyTable;
    };
}

extern "C" {
    std::string getType() {
        return "graphical";
    }

    std::unique_ptr<arcade::IGraphicalModule> entryPoint() {
        return std::make_unique<arcade::SFML>();
    }
}

#endif /* !SFML_HPP_ */
