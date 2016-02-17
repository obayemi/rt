/*!
 * \file Texture.cpp
 * \author obayemi
 */

#include "Texture.hh"

std::map<std::string, Texture::JsonLoader*>	Texture::_textures;

void			Texture::registerTexture(const std::string &texture,
        Texture::JsonLoader *loader) {
    Texture::_textures[texture] = loader;
}

Texture		*Texture::fromJson(const Json::Value &value) {
    if (Texture::_textures.find(value["texture"].asString()) == Texture::_textures.end()) {
        std::cerr << "Invalid Texture: " << value["texture"] << std::endl
            << value << std::endl;
        throw InvalidScene();
    }
    return Texture::_textures[value["texture"].asString()](value);
}
