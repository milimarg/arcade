/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** Doom.hp
*/

#ifndef Doom_HPP_
    #define Doom_HPP_

    #include "AGameModule.hpp"
    #include "IGraphicalModule.hpp"
    #include "idt1/include/my.hpp"
    #include <stddef.h>

namespace arcade
{
    /**
     * Doom Class
     */
    class Doom : public AGameModule {
        public:
            Doom();
            ~Doom();

            /**
             * Creates objects (pixels and texts) and init doom scene.
             */
            void init() override;

            /**
             * Called when game is quit.
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

        protected:
            /**
             * Checks if key is in keyTable, if it does, it runs the associated action
             * @param key Pressed key to process
             */
            void applyEvent(const Key &key) override;

        private:
            int _score;
            bool _isGameOver;
            std::unordered_map<std::string, int> _gameSettings;
            float _timeBank;

            int _windowWidth;
            int _windowHeight;

            std::unique_ptr<my_idt1> _world = nullptr;
            std::array<bool, KEY_ACTIONS_NUMBER> _actions = {false};
            std::array<Key, KEY_ACTIONS_NUMBER> _keyTable;
            std::string _filepath;
    };
}

extern "C" {
    std::string getType() {
        return "game";
    }

    std::unique_ptr<arcade::IGameModule> entryPoint() {
        return std::make_unique<arcade::Doom>();
    }
}

#endif /* Doom_HPP_ */
