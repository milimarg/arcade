/*
** EPITECH PROJECT, 2024
** B-OOP-400-STG-4-1-arcade-noe.tritsch
** File description:
** Texture.cpp
*/

#include "Texture.hpp"
#include "../../OpenGL/Rect.hpp"
#include "Pair.hpp"

Texture::Texture() {}

Texture::Texture(const std::string &path)
    : _filePath(path), _buffer(nullptr), _width(0), _height(0), _channels(0)
{
    _buffer = stbi_load(_filePath.c_str(), &_width, &_height, &_channels, 0);
}

Texture::~Texture()
{
    if (!_buffer)
        return;
    _buffer = nullptr;
    _width = 0;
    _height = 0;
    _channels = 0;
}
