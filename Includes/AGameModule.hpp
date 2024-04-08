/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** AGameModule
*/

#ifndef AGAMEMODULE_HPP_
    #define AGAMEMODULE_HPP_
    #include "IGameModule.hpp"
    #include "IGraphicalModule.hpp"
    #include "Pixels.hpp"
    #include "Texts.hpp"

namespace arcade
{
    /**
     * AGameModule Class
     */
    class AGameModule : public IGameModule {
    public:
        /**
         * Constructor of AGameModule
         * @param name game name
         */
        AGameModule(std::string name);
        ~AGameModule();

        /**
         * Returns the current game module name.
         * @return std::string
         */
        std::string getName() const override;
        /**
        * Returns the current pixels wrapper.
        * @return IPixels *
        */
        IPixels *getPixelsWrapper() override;
        /**
        * Returns the current texts wrapper.
        * @return ITexts *
        */
        ITexts *getTextsWrapper() override;
    protected:
        /**
         * Creates a wrapper of pixels.
         * @return IPixels *
         */
        IPixels *createPixelsObject() override;
        /**
         * Creates a wrapper of texts.
         * @return ITexts *
         */
        ITexts *createTextsObject() override;

        /**
         * Wrapper of displayable pixels in the game module
         */
        std::unique_ptr<IPixels> _pixels;
        /**
         * Wrapper of displayable texts in the game module
         */
        std::unique_ptr<ITexts> _texts;
        /**
         * Name of the game module
         */
        std::string &_name;
    };
}

#endif /* !AGAMEMODULE_HPP_ */
