/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Error
*/

#ifndef ERROR_HPP_
    #define ERROR_HPP_
    #include <iostream>

namespace arcade {
    /**
     * Error Class
     */
    class Error : public std::exception {
        public:
            /**
             * Creates en error thrower
             * @param what error message
             */
            Error(std::string what) : _what(what) {}

            /**
             *
             * @return error message
             */
            const char *what() const throw() override
            {
                static std::string errorMessage = _what;
                return errorMessage.c_str();
            }
        private:
            std::string _what;
    };
};

#endif /* !ERROR_HPP_ */
