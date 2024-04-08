/*
** EPITECH PROJECT, 2024
** arcade-preparations
** File description:
** main
*/

#include "Includes/Core.hpp"

int main(int argc, char **argv)
{
    std::string filepath = "";

    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " [graphicLibraryPath]" << std::endl;
        return 84;
    }
    filepath = argv[1];
    try {
        arcade::Core core(filepath);
        core.initialize();
        core.run();
        core.shutdown();
    } catch (const std::exception& e) {
       std::cerr << e.what() << std::endl;
       return 84;
    }
    return 0;
}
