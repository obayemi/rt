#ifndef _PLANE_HH
#define _PLANE_HH

/*!
 * \file Plane.hh
 * \author obayemi
 */

#include "Mesh.hh"
#include "Ray.hh"
#include "Intersection.hh"
#include "Object.hh"
#include "Scene.hh"

class				Plane : public Mesh {
    public:
        Plane();
        Plane(const Plane &orig);
        Plane(const Position &position, const Rotation &rotation, const Color &color = Mesh::defaultColor);
        ~Plane();

        Intersection	intersect(const Ray &ray) const;
        static Plane	*fromJson(const Json::Value &plane);
};

#endif // _PLANE_HH

