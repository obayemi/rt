#ifndef _OBJECT_HH
#define _OBJECT_HH

/*!
 * \file Object.hh
 * \author obayemi
 */

#include <functional>

#include "jsoncpp/json/json.h"

#include "Coordinates.hpp"
#include "Texture.hh"
#include "RotMatrix.hh"
#include "Ray.hh"

class Ray;

class						Object {
    typedef Object *(JsonLoader)(const Json::Value &value, TextureMap &textures);
    //typedef std::function<JsonLoader_f> JsonLoader;

    private:
        Position			_position;
        Rotation			_rotation;

        const Texture			*_texture;

    protected:
        RotMatrix			_rotMatrix;
        RotMatrix			_invRotMatrix;


    public:
        Object();
        Object(const Object &orig);
        Object(const Position &position, const Rotation &rotation,
                const Texture *texture);
        virtual ~Object();
        const Position		&getPosition() const;
        const Rotation		&getRotation() const;
        const Texture		*getTexture() const;

        void				translate(const Direction &direction);
        void				rotate(const Rotation &rotation);

        Ray					localize(const Ray &ray) const;
        Ray					globalize(const Ray &ray) const;


    private:
        static std::map<std::string, JsonLoader*>	_objects;
    public:
        static void			registerObject(const std::string &object,
                JsonLoader *loader);
        static Object		*fromJson(const Json::Value &value, TextureMap &textures);
};


#endif // _OBJECT_HH

