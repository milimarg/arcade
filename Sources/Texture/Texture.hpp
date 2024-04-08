/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Texture.hpp
*/

#ifndef B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_TEXTURE_HPP
    #define B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_TEXTURE_HPP
    #include <iostream>
    #include "../../OpenGL/Rect.hpp"
    #include "../../Includes/stb_image.hpp"
    #include "Error.hpp"

/**
 * Texture Class
 */
class Texture {
public:
    Texture();
    /**
     * Creates a texture
     * @param path filepath of input image
     */
    Texture(const std::string &path);
    ~Texture();

    /**
     *
     * @return texture width
     */
    int getWidth() const { return _width; }

    /**
     *
     * @return texture height
     */
    int getHeight() const { return _height; }

    /**
     *
     * @return texture channels number
     */
    int getChannels() const { return _channels; }

    /**
     *
     * @return texture size
     */
    int getTextureSize() const { return _width * _height * _channels; }

    /**
     *
     * @return buffer
     */
    const unsigned char *getBuffer() { return _buffer; }
private:
    std::string _filePath;
    unsigned char *_buffer;
    int _width;
    int _height;
    int _channels;
};

#endif //B_OOP_400_STG_4_1_ARCADE_NOE_TRITSCH_TEXTURE_HPP
