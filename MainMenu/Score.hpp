/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Score
*/

#ifndef SCORE_HPP_
    #define SCORE_HPP_

    #include <string>

namespace arcade
{
    /**
     * Score Class
     */
    class Score {
        public:
            Score() = default;

            /**
             * Create a score
             * @param playerName name of the player
             * @param scoreValue start value of the score
             */
            Score(const std::string &playerName, int scoreValue);

            /**
             *
             * @return current player name
             */
            std::string getPlayerName() const;

            /**
             *
             * @return current score
             */
            int getScoreValue() const;

            /**
             * Set a player name
             * @param newName new name to apply
             */
            void setPlayerName(const std::string &newName);

            /**
             * Set a score value
             * @param newValue new score value to apply
             */
            void setScoreValue(int newValue);

        private:
            std::string _playerName;
            int _scoreValue;
    };

}

#endif /* !SCORE_HPP_ */
