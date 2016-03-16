#include "DamierTexture.hh"

DamierTexture::DamierTexture() {
}

DamierTexture::DamierTexture(const Json::Value &value) {
    this->_size = value.get("size", "1").asDouble();
    this->_fgColor= Color(
            value["foreground"]["r"].asUInt(),
            value["foreground"]["g"].asUInt(),
            value["foreground"]["b"].asUInt()
            );
    this->_bgColor= Color(
            value["background"]["r"].asUInt(),
            value["background"]["g"].asUInt(),
            value["background"]["b"].asUInt()
            );
}

DamierTexture::DamierTexture(const Color &color, double size,
                const Color &fg,
                const Color &bg): _size(size), _fgColor(fg), _bgColor(bg)
{}

DamierTexture::~DamierTexture() {};

Color			DamierTexture::getColor(const Position &position) const {
    (void) position;
    return this->_fgColor;
}

Texture		*DamierTexture::fromJson(const Json::Value &value) {
    return new DamierTexture(value);
}
