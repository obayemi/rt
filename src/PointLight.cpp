/*!
 * \file PointLight.hh
 * \author obayemi
 */

#include "PointLight.hh"

PointLight::PointLight(): Light() {}

PointLight::PointLight(const PointLight &orig): Light(orig) {}

PointLight::PointLight(const Position &position, const Rotation &rotation,
        const Texture *texture):Light(position, rotation, texture, 1) {}

PointLight::~PointLight() {}

Light						*PointLight::fromJson(const Json::Value &light,
        TextureMap &textures) {
    if (textures.find(light["color"]["name"].asString()) == textures.end()) {
        textures[light["color"]["name"].asString()] = Texture::fromJson(light["color"]);
    }
    return new PointLight(
            Position(
                light["position"]["x"].asDouble(),
                light["position"]["y"].asDouble(),
                light["position"]["z"].asDouble()
             ),
            Rotation(Rotation3(
                light["rotation"]["x"].asDouble(),
                light["rotation"]["y"].asDouble(),
                light["rotation"]["z"].asDouble()
             )),
            textures[light["color"]["name"].asString()]
            );

}
