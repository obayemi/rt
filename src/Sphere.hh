#ifndef _SPHERE_HH
#define _SPHERE_HH

/*!
 * \file Sphere.hh
 * \author obayemi
 */

#include "Mesh.hh"
#include "Ray.hh"
#include "Intersection.hh"
#include "Object.hh"
#include "Scene.hh"

class					Sphere : public Mesh {
    private:
        double			_radius;

    public:
        Sphere();
        Sphere(const Sphere &orig);
        Sphere(const Position &position, const Rotation &rotation,
                double radius = 1,
                const Color &color = Mesh::defaultColor);
        ~Sphere();

        Intersection	intersect(const Ray &ray) const;
        static Sphere	*fromJson(const Json::Value &sphere);
};

#endif // _SPHERE_HH


