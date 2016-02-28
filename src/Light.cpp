/*!
 * \file Light.cpp
 * \author obayemi
 */

#include "Light.hh"
#include "Color.hh"
#include "ColorTexture.hh"

Light::Light(): Object() {}

Light::Light(const Light &other): Object(other), _samples(other._samples) {}

Light::Light(const Position &position, const Rotation &rotation,
        const Texture *texture, unsigned int samples):
    Object(position, rotation, texture), _samples(samples) {}

Light::~Light() {}


std::map<std::string, Light::JsonLoader*>	Light::_lights;

void			Light::registerLight(const std::string &light,
        Light::JsonLoader *loader) {
    Light::_lights[light] = loader;
}

Light			*Light::fromJson(const Json::Value &value, TextureMap &textures) {
    if (Light::_lights.find(value["light"].asString()) == Light::_lights.end()) {
        std::cerr << "Invalid Light: " << value["light"] << std::endl
            << value << std::endl;
        throw InvalidScene();
    }
    return Light::_lights[value["light"].asString()](value, textures);
}

unsigned int	Light::getSamples() const {
    return this->_samples;
}
