#ifndef _PLANE_HH
#define _PLANE_HH

/*!
 * \file Plane.hh
 * \author obayemi
 */

#include <map>
#include <string>

#include "Mesh.hh"
#include "Ray.hh"
#include "Intersection.hh"

class				Plane : public Mesh {
    public:
        Plane();
        Plane(const Plane &orig);
        Plane(const Position &position, const Rotation &rotation,
                const Texture *texture);
        ~Plane();

        Intersection	*intersect(const Ray &ray) const;

        static Mesh		*fromJson(const Json::Value &value,
                TextureMap &textures);
};

#endif // _PLANE_HH
