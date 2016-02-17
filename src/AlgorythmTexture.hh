#ifndef _COLORTEXTURE_HH
#define _COLORTEXTURE_HH

/*!
 * \file AlgorythmTexture.hh
 * \author obayemi
 */

#include <SFML/Graphics.hpp>
#include "jsoncpp/json/json.h"

#include "Texture.hh"

class					AlgorythmTexture: public Texture {
    private:
        Color			_color;

    public:
        AlgorythmTexture();
        AlgorythmTexture(const Json::Value &value);
        AlgorythmTexture(const Color &color);
        virtual ~AlgorythmTexture();
        Color			getColor(const Position &position) const;

        static Texture		*fromJson(const Json::Value &value);

    private:
        static std::map<std::string, JsonLoader*>	_algorythms;
    public:
        static void			registerAlgorythm(const std::string &algorythm,
                JsonLoader *loader);
};

#endif // _COLORTEXTURE_HH
