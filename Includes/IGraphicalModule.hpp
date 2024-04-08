/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** IGraphicalModule
*/

#ifndef IGRAPHICALMODULE_HPP_
    #define IGRAPHICALMODULE_HPP_

    #include <string>
    #include <array>
    #include <algorithm>
    #include <memory>
    #include "Pair.hpp"
    #include "IEvent.hpp"
    #include "IWindow.hpp"
    #include "EventInfo.hpp"
    #include "Error.hpp"
    #include <filesystem>

namespace arcade
{
    /**
     * IGraphicalModule Class
     */
    class IGraphicalModule {
        public:
            virtual ~IGraphicalModule() = default;

            /**
             * Inits graphical module
             */
            virtual void init() = 0;

            /**
             * Stops graphical module
             */
            virtual void stop() = 0;

            /**
             *
             * @return graphical module name
             */
            virtual std::string getName() const = 0;

            /**
             *
             * @return events wrapper
             */
            virtual IEvent *getEventWrapper() const = 0;

            /**
             *
             * @return window wrapper
             */
            virtual IWindow *getWindowWrapper() const = 0;

            /**
             * Updates pixels wrapper content
             * @param pixels pixels wrapper
             */
            virtual void updatePixelsWrapper(IPixels *pixels) = 0;

            /**
             * Updates texts wrapper content
             * @param texts texts wrapper
             */
            virtual void updateTextsWrapper(ITexts *texts) = 0;

            /**
             * Handles events
             */
            virtual void pollEvents() = 0;

            /**
             * Displays pixels and texts wrappers
             */
            virtual void display() const = 0;

    protected:
            /**
             * Creates an events wrapper
             * @return events wrapper
             */
            virtual IEvent *createEventObject() = 0;

            /**
             * Creates a window wrapper
             * @return window wrapper
             */
            virtual IWindow *createWindowObject() = 0;
    };
}

#endif /* !IGRAPHICALMODULE_HPP_ */
