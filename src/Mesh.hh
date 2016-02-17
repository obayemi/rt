#ifndef _MESH_HH
#define _MESH_HH

/*!
 * \file Mesh.hh
 * \author obayemi
 */

#include "Object.hh"
#include "Ray.hh"
#include "Intersection.hh"
#include "Texture.hh"

class Intersection;

class							Mesh : public Object {
    typedef Mesh *(JsonLoader)(const Json::Value &value,
            TextureMap &textures);

    public:
        Mesh();
        Mesh(const Mesh &other);
        Mesh(const Position &position, const Rotation &rotation,
                const Texture *texture);
        virtual ~Mesh();

        virtual Intersection	intersect(const Ray &ray) const = 0;

    private:
        static std::map<std::string, JsonLoader*>	_meshs;
    public:
        static void			registerMesh(const std::string &object,
                JsonLoader *loader);
        static Mesh		*fromJson(const Json::Value &value,
                TextureMap &textures);
};

#endif // _MESH_HH
