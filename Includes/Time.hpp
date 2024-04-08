/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Time
*/

#ifndef TIME_HPP_
    #define TIME_HPP_

    #include <chrono>
    #include <ITime.hpp>

namespace arcade {
    /**
     * Time Class
     */
    class Time : public ITime {
        public:
            Time();

            /**
             * Update time variables
             */
            void update() override;

            /**
             *
             * @return current timeBank
             */
            float getTime() const override;

            /**
             *
             * @return time since last call of this function
             */
            float getDeltaTime() const override;

        private:
            std::chrono::steady_clock::time_point _startTime;
            std::chrono::steady_clock::time_point _previousTime;
            std::chrono::steady_clock::time_point _currentTime;

            float _deltaTime;
    };
}

#endif /* !TIME_HPP_ */
