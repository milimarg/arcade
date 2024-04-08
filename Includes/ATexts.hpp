/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** ATexts
*/

#ifndef ATEXTS_HPP_
    #define ATEXTS_HPP_
    #include "Pair.hpp"
    #include "ITexts.hpp"

namespace arcade
{
    /**
     * ATexts Class
     */
   class ATexts : public ITexts {
        public:
            ATexts();
            ~ATexts();

            /**
             *
             * @return texts wrapper
             */
            TextMap &getTextMap() override;

            /**
             * Update texts wrapper (only content of wrapper will be copied)
             * @param texts new texts wrapper
             */
            void updateTextMap(const TextMap &texts) override;

        private:
            TextMap _textMap;
    };
}

#endif /* !ATEXTS_HPP_ */
