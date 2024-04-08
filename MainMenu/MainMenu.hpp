/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** MainMenu
*/

#ifndef MAINMENU_HPP_
    #define MAINMENU_HPP_

    #include "AGameModule.hpp"
    #include "IGraphicalModule.hpp"
    #include <vector>
    #include <filesystem>
    #include <fstream>
    #include <string>
    #include "LibraryHandler.hpp"
    #include <openssl/evp.h>
    #include <openssl/err.h>
    #include <openssl/conf.h>
    #include <openssl/rand.h>
    #include <cstring>
    #include "Score.hpp"
    #include <algorithm>

namespace arcade
{
    /**
     * MainMenu Class
     */
    class MainMenu : public AGameModule {
        public:
            MainMenu();
            ~MainMenu();

            /**
             * Sets up snake entity, init gameSettings values and create objects (pixels and texts)
             */
            void init() override;

            /**
             * Resets snake entity, clears gameSettings, resets timeBank
             */
            void stop() override;

            /**
             * Checks for events (i.e. pressed keys) sent by current graphics library.
             * @param eventWrapper wrapper containing getters to obtain events
             */
            void applyEvents(IEvent *eventWrapper) override;

            /**
             * Clears pixels wrapper, moves player and displays doom renderer.
             * @param deltaTime Time since last call of update() function
             */
            void update(float deltaTime) override;

            /**
             * Calls stop() then init().
             */
            void reload() override;

            /**
             * Returns the current score.
             * @return current score
             */
            int getScore() override;

            /**
             * Updates pixels wrapper, texts wrapper and call display() of the given module
             * @param module given graphical module
             */
            void draw(IGraphicalModule *module) override;

            std::string getName() const override;

        protected:
            /**
             * Checks if key is in keyTable, if it does, it runs the associated action
             * @param key Pressed key to process
             */
            void applyEvent(const Key &key) override;

        private:
            std::string _nameInput;
            bool _nameInputActive;
            std::vector<std::string> _gameLibraries;
            std::vector<std::string> _graphicLibraries;
            std::size_t _selectedGameIndex;
            std::size_t _selectedGraphicIndex;
            std::size_t _mainMenuIndex;
            bool _isGameListChecked;
            std::string _currentGraphical;
            std::string _secretKey;
            std::unordered_map<std::string, std::vector<Score>> _scores;

            void initLibs();
            std::string cleanLibName(const std::string &libName);
            void loadScores();

            void moveUp();
            void moveDown();
            void switchList(bool left);
            void addChar(Key key);
            void deleteChar();
            bool isCharInput(Key key) const;
            void selectLibraries(IEvent *eventWrapper);
            void sortScores(std::vector<Score> &scores);
            void handleMouseClick([[maybe_unused]] const Key &event, const std::pair<int, int> &clickPosition);

            void clearScreen();
            void drawBackground();
            void drawUsernameText();
            void drawGameList();
            void drawGraphicList();
            void drawTextBackground(size_t xOffset, size_t yOffset, size_t textLength, const Pixel &pixel);
            void drawScores();

            std::string decryptData(const std::string &ciphertext, const std::string &key);

            Score parseScore(const std::string& line);
    };
}

extern "C" {
    std::string getType() {
        return "mainMenu";
    }

    std::unique_ptr<arcade::IGameModule> entryPoint() {
        return std::make_unique<arcade::MainMenu>();
    }
}

#endif /* !MAINMENU_HPP_ */
