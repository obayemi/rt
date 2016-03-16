#ifndef _FLATTEXTURE_HH
#define _FLATTEXTURE_HH

/*!
 * \file Flattexture.hh
 * \author obayemi
 */

#include <SFML/Graphics.hpp>
#include "jsoncpp/json/json.h"

class 					FlatTexture: public Texture {
    sf::image			*_image;
    NoiseEngine			*_noise;
    double				*_size;

    public:
        FlatTexture();
        FlatTexture(Json::Value);
        ~FlatTexture() {};
        virtual getColor(const Position &position) const;
};

#endif // _FLATTEXTURE_HH
