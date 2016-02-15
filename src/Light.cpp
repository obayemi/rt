/*!
 * \file Light.cpp
 * \author obayemi
 */

#include "Light.hh"
#include "Color.hh"

Color		Light::defaultColor = Color(0x777777ff);

Light::Light(): Object(), _color(Light::defaultColor) {}

Light::Light(const Light &other): Object(other), _color(other._color) {}

Light::Light(const Position &position, const Rotation &rotation,
        const Color &color):
    Object(position, rotation), _color(color) {}

Light::~Light() {}

const Color				&Light::getColor(const Direction &origin, double distance) const {
    return this->_color;
}

Light						*Light::fromJson(const Json::Value &light) {
    return new Light(
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
            Color(
                    light["color"]["color"]["r"].asUInt(),
                    light["color"]["color"]["g"].asUInt(),
                    light["color"]["color"]["b"].asUInt()
                 )
            );
}
