/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** ILibraryHandler
*/

#ifndef ILIBRARYHANDLER_HPP_
    #define ILIBRARYHANDLER_HPP_
    #include <string>
    #include <dlfcn.h>
    #include <iostream>
    #include "Pair.hpp"
    #include "Error.hpp"

namespace arcade
{
    /**
     * ILibraryHandler Class
     */
    class ILibraryHandler {
        public:
            virtual ~ILibraryHandler() = default;

            /**
             *
             * @return is the library still opened?
             */
            virtual bool isOpen() const = 0;

            /**
             *
             * @return last thrown error by dlerror()
             */
            virtual std::string getLastError() const = 0;

            /**
             * Closes the lib
             */
            virtual void close() = 0;
    };
}

#endif /* !ILIBRARYHANDLER_HPP_ */
