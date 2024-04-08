/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** IGameModule
*/

#ifndef IGAMEMODULE_HPP_
    #define IGAMEMODULE_HPP_
    #include <string>
    #include <unordered_map>
    #include <array>
    #include <algorithm>
    #include <memory>
    #include "Pair.hpp"
    #include "Keys.hpp"
    #include "Error.hpp"

namespace arcade
{
    class IGraphicalModule;
    class IEvent;
    class IWindow;
    class IPixels;
    class ITexts;

    /**
     * IGameModule Class
     */
    class IGameModule {
        public:
            virtual ~IGameModule() = default;

            /**
             * Inits game module
             */
            virtual void init() = 0;

            /**
             * Stops game module
             */
            virtual void stop() = 0;

            /**
             *
             * @return game module name
             */
            virtual std::string getName() const = 0;

            /**
             *
             * @return pixels wrapper
             */
            virtual IPixels *getPixelsWrapper() = 0;

            /**
             * texts wrapper
             * @return
             */
            virtual ITexts *getTextsWrapper() = 0;

            /**
             * Apply events of events wrapper
             * @param eventWrapper events wrapper
             */
            virtual void applyEvents(IEvent *eventWrapper) = 0;

            /**
             * Updates game
             * @param deltaTime time since last call of update()
             */
            virtual void update(float deltaTime) = 0;

            /**
             * Stops then inits game module
             */
            virtual void reload() = 0;

            /**
             *
             * @return current score
             */
            virtual int getScore() = 0;

            /**
             * Draws pixels and texts
             * @param module graphical module
             */
            virtual void draw(IGraphicalModule *module) = 0;

        protected:
            /**
             * Creates pixels wrapper
             * @return pixels wrapper
             */
            virtual IPixels *createPixelsObject() = 0;

            /**
             * Creates texts wrapper
             * @return texts wrapper
             */
            virtual ITexts *createTextsObject() = 0;

            /**
             * Apply event depending on pressed key
             * @param key pressed key
             */
            virtual void applyEvent(const Key &key) = 0;
    };
}

#endif /* !IGAMEMODULE_HPP_ */
