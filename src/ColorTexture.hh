#ifndef _COLORTEXTURE_HH
#define _COLORTEXTURE_HH

/*!
 * \file ColorTexture.hh
 * \author obayemi
 */

#include <SFML/Graphics.hpp>
#include "jsoncpp/json/json.h"

#include "Texture.hh"

class					ColorTexture: public Texture {
    private:
        Color			_color;

    public:
        ColorTexture();
        ColorTexture(const Json::Value &value);
        ColorTexture(const Color &color);
        ~ColorTexture();
        Color			getColor(const Position &position) const;

        static Texture		*fromJson(const Json::Value &value);
};

#endif // _COLORTEXTURE_HH

