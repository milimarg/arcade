/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** ICore
*/

#ifndef ICORE_HPP_
    #define ICORE_HPP_
    #include <iostream>
    #include "IGameModule.hpp"
    #include "IGraphicalModule.hpp"
    #include "LibraryHandler.hpp"
    #include "Time.hpp"
    #include <memory>
    #include <thread>
    #include <chrono>
    #include <openssl/evp.h>
    #include <openssl/conf.h>
    #include <openssl/err.h>
    #include <openssl/rand.h>
    #include <cstring>

namespace arcade
{
    /**
     * ICore Class
     */
    class ICore {
        public:
            virtual ~ICore() = default;

            /**
             * Inits core
             * @return has the core successfully initialized?
             */
            virtual bool initialize() = 0;

            /**
             * Runs the core
             */
            virtual void run() = 0;

            /**
             * Shutdowns the core
             */
            virtual void shutdown() = 0;

            /**
             * Adds game library into core
             * @param libraryName library filepath
             */
            virtual void addGameLibrary(const std::string &libraryName) = 0;

            /**
             * Adds graphical library into core
             * @param libraryName library filepath
             */
            virtual void addGraphicalLibrary(const std::string &libraryName) = 0;

            /**
             * Switch to another game library
             * @param path library filepath
             * @param inGame has the lib to launch right now?
             */
            virtual void switchGameLibrary(const std::string &path, bool inGame = false) = 0;

            /**
             * Switch to another graphics library
             * @param path library filepath
             * @param inGame has the lib to launch right now?
             */
            virtual void switchGraphicalLibrary(const std::string &path, bool inGame = false) = 0;

            /**
             * Switches to main menu
             * @param inGame has the lib to launch right now?
             */
            virtual void switchMainMenu(bool inGame = false) = 0;

        protected:
            /**
             * Loads game module
             * @return Has game loading been successful?
             */
            virtual bool loadGameModule() = 0;

            /**
             * Loads graphical module
             * @return Has graphics loading been successful?
             */
            virtual bool loadGraphicalModule() = 0;

            /**
             * Init modules
             */
            virtual void initializeModules() = 0;

            /**
             * Init wrappers
             */
            virtual void initializeWrappers() = 0;

            /**
             * Updates modules
             * @return used to check error handling
             */
            virtual int updateModules() = 0;

            /**
             * Handles change events
             * @return used to check error handling
             */
            virtual int handleChangeEvent() = 0;
    };
}

#endif /* !ICORE_HPP_ */
