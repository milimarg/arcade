/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** IEventInfo
*/

#ifndef IEVENTINFO_HPP_
    #define IEVENTINFO_HPP_
    #include <iostream>
    #include "Keys.hpp"

namespace arcade
{
    /**
     * IEventInfo Class
     */
    class IEventInfo {
        public:
            virtual ~IEventInfo() = default;

            /**
             *
             * @return mouse coordinates
             */
            virtual std::pair<int, int> getMouseCoords() const = 0;

            /**
             *
             * @return last pressed key
             */
            virtual Key getKey() const = 0;

            /**
             *
             * @return last pressed change key
             */
            virtual ChangeKey getChangeKey() const = 0;

            /**
             * Sets mouse coordinates
             * @param coords new coordinates
             */
            virtual void setMouseCoords(const std::pair<int, int> &coords) = 0;

            /**
             * Sets key
             * @param key new key
             */
            virtual void setKey(const Key &key) = 0;

            /**
             * Sets change key
             * @param key new change key
             */
            virtual void setChangeKey(const ChangeKey &key) = 0;
    };
}

#endif /* !IEVENTINFO_HPP_ */
