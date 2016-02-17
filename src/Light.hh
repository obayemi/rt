#ifndef _LIGHT_HH
#define _LIGHT_HH

/*!
 * \file Light.hh
 * \author obayemi
 */

#include "Object.hh"
#include "Color.hh"

class							Light : public Object {
    typedef Light *(JsonLoader)(const Json::Value &value,
            TextureMap &textures);

    public:
        Light();
        Light(const Light &other);
        Light(const Position &position, const Rotation &rotation,
                const Texture *texture);
        virtual ~Light();

    private:
        static std::map<std::string, JsonLoader*>	_lights;
    public:
        static void			registerLight(const std::string &object,
                JsonLoader *loader);
        static Light		*fromJson(const Json::Value &value,
                TextureMap &textures);
};

#endif // _LIGHT_HH
