#ifndef _DAMIERTEXTURE_HH
#define _DAMIERTEXTURE_HH

/*!
 * \file DamierTexture.hh
 * \author obayemi
 */

#include <SFML/Graphics.hpp>
#include "jsoncpp/json/json.h"

#include "Texture.hh"

class					DamierTexture: public Texture {
    private:
        double			_size;
        Color			_fgColor;
        Color			_bgColor;

    public:
        DamierTexture();
        DamierTexture(const Json::Value &value);
        DamierTexture(const Color &color, double size = 1,
                const Color &fg = Color(0xffffffff),
                const Color &bg = Color(0x000000ff));
        ~DamierTexture();
        Color			getColor(const Position &position) const;

        static Texture		*fromJson(const Json::Value &value);
};

#endif // _DAMIERTEXTURE_HH

