/*!
 * \file ColorTexture.cpp
 * \author obayemi
 */

#include "ColorTexture.hh"

ColorTexture::ColorTexture() {
}

ColorTexture::ColorTexture(const Json::Value &value) {
    if (value["color"] == Json::nullValue ||
            value["color"]["r"] == Json::nullValue ||
            value["color"]["g"] == Json::nullValue ||
            value["color"]["b"] == Json::nullValue) {
        std::cerr << "Invalid Texture:" << std::endl
            << value << std::endl;
        throw InvalidScene();
    }
    this->_color = Color(
            value["color"]["r"].asUInt(),
            value["color"]["g"].asUInt(),
            value["color"]["b"].asUInt()
            );
}

ColorTexture::ColorTexture(const Color &color): _color(color) {}

ColorTexture::~ColorTexture() {};

Color			ColorTexture::getColor(const Position &position) const {
    (void) position;
    return this->_color;
}

Texture		*ColorTexture::fromJson(const Json::Value &value) {
    return new ColorTexture(value);
}
