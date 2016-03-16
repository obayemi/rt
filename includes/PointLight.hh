#ifndef _POINTLIGHT_HH
#define _POINTLIGHT_HH

/*!
 * \file PointLight.hh
 * \author obayemi
 */

#include <map>
#include <string>

#include "Light.hh"

class				PointLight : public Light {
    public:
        PointLight();
        PointLight(const PointLight &orig);
        PointLight(const Position &position, const Rotation &rotation,
                const Texture *texture);
        ~PointLight();

        static Light	*fromJson(const Json::Value &value,
                TextureMap &textures);
};

#endif // _POINTLIGHT_HH

