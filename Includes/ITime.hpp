/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** ITime
*/

#ifndef ITIME_HPP_
    #define ITIME_HPP_

namespace arcade
{
    /**
     * ITime Class
     */
    class ITime {
        public:
            virtual ~ITime() = default;

            /**
             * Updates times variable
             */
            virtual void update() = 0;

            /**
             *
             * @return current timeBank
             */
            virtual float getTime() const = 0;

            /**
             *
             * @return time since last call of getDeltaTime()
             */
            virtual float getDeltaTime() const = 0;
    };
}

#endif /* !ITIME_HPP_ */
