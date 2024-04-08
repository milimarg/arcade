/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** IEvent
*/

#ifndef IEVENT_HPP_
    #define IEVENT_HPP_
    #include "Keys.hpp"
    #include "IEventInfo.hpp"

namespace arcade
{
    /**
     * IEvent Class
     */
    class IEvent {
        public:
            virtual ~IEvent() = default;

            /**
             *
             * @return events info wrapper
             */
            virtual std::unique_ptr<IEventInfo> getEvent() = 0;

            /**
             *
             * @return change events info wrapper
             */
            virtual std::unique_ptr<IEventInfo> getChangeEvent() = 0;

            /**
             * Pushes a key event to events wrapper
             * @param key event to add
             */
            virtual void pushEvent(const Key &key) = 0;

            /**
             * Pushes a key event to events wrapper
             * @param key event to add
             * @param mouseCoords mouse coordinates
             */
            virtual void pushEvent(const Key &key, std::pair<int, int> mouseCoords) = 0;

            /**
             * Pushes a change key event to events wrapper
             * @param changeKey event to add
             */
            virtual void pushChangeEvent(const ChangeKey &changeKey) = 0;

            /**
             * Clears events wrapper
             */
            virtual void clearEventQueue() = 0;

            /**
             * Clears change events wrapper
             */
            virtual void clearChangeEventQueue() = 0;
    };
}

#endif /* !IEVENT_HPP_ */
