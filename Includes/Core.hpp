/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** Core
*/

#ifndef CORE_HPP_
    #define CORE_HPP_
    #include "ICore.hpp"
    #include <filesystem>
    #include <fstream>
    #include <string>
    #include "ITexts.hpp"

namespace arcade
{
    /**
     * Core Class
     */
    class Core : public ICore {
        public:
            /**
             * Creates a core
             * @param graphical name of graphical library
             */
            Core(std::string &graphical);
            ~Core();

            /**
             * Checks if two given files are the same
             * @param first first file
             * @param second second file
             * @return equality condition output between 2 files
             */
            bool areSameFiles(const std::string& first, const std::string& second);

            /**
             * Inits library
             * @param graphical graphics library
             */
            void initLib(std::string &graphical);

            /**
             * Initializes core
             * @return has the core successfully initialized?
             */
            bool initialize() override;

            void run() override;
            void shutdown() override;

            void addGameLibrary(const std::string &libraryName) override;
            void addGraphicalLibrary(const std::string &libraryName) override;

            void switchGameLibrary(const std::string &path, bool inGame = false) override;
            void switchGraphicalLibrary(const std::string &path, bool inGame = false) override;
            void switchMainMenu(bool inGame = false) override;

        private:
            std::unique_ptr<LibraryHandler> _graphicalLibrary;
            std::unique_ptr<LibraryHandler> _gameLibrary;
            std::unique_ptr<IGraphicalModule> _graphicalModule;
            std::unique_ptr<IGameModule> _gameModule;

            bool loadGameModule() override;
            bool loadGraphicalModule() override;

            void initializeModules() override;
            void initializeWrappers() override;

            int updateModules() override;

            int handleChangeEvent() override;
            std::string encryptData(const std::string &plaintext, const std::string &key);
            std::string decryptData(const std::string &ciphertext, const std::string &key);
            std::string cleanLibName(const std::string &libName);
            void saveCurrentScore(const std::string &libName);

            std::vector<std::string> _gameLibraryList;
            std::vector<std::string> _graphicalLibraryList;
            int _gameIndex;
            int _graphicalIndex;
            size_t _indexMainMenu;

            Time _time;

            IEvent *_eventWrapper;
            IWindow *_windowWrapper;

            std::string _secretKey;
            std::string _currentUserName;
            int _currentScore;
    };
}

#endif /* !CORE_HPP_ */
