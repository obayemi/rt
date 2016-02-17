#ifndef _TEXTURE_HH
#define _TEXTURE_HH

/*!
 * \file Texture.hh
 * \author obayemi
 */

#include <string>
#include <map>

#include "jsoncpp/json/json.h"

#include "Coordinates.hpp"
#include "Color.hh"

class 					Texture {
    typedef Texture *(JsonLoader)(const Json::Value &value);
    
    public:
        virtual ~Texture() {};
        virtual Color	getColor(const Position &position) const = 0;

    private:
        static std::map<std::string, JsonLoader*>	_textures;
    public:
        static void			registerTexture(const std::string &texture,
                JsonLoader *loader);
        static Texture		*fromJson(const Json::Value &value);
};

typedef std::map<std::string, Texture *> TextureMap;

#endif // _TEXTURE_HH
