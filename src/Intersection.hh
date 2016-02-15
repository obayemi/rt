#ifndef _INTERSECTION_HH
#define _INTERSECTION_HH

/*!
 * \file Intersection.hh
 * \author obayemi
 */

#include "Exceptions.hh"
#include "Coordinates.hpp"
#include "Mesh.hh"
#include "Color.hh"
#include "Scene.hh"

class Mesh;
class Scene;

class						Intersection {
    private:
        const Position		_position;
        const Position		_localPosition;
        const Mesh			&_mesh;
        const Ray			_ray;
        const Ray			_localray;
        const Direction		_normal;
        const double		_distance;

    private:
        Intersection();

    public:
        Intersection(const Intersection &);
        Intersection(const Position &position,
                const Position &localposition,
                const Mesh &mesh,
                const Ray &ray,
                const Ray &localray,
                const Direction &normal,
                double distance);
        ~Intersection();

        Color				render(const Scene &scene);

        bool					operator>(double distance) const;
        bool					operator<(double distance) const;

        bool					operator>(const Intersection &other) const;
        bool					operator<(const Intersection &other) const;
};

#endif // _INTERSECTION_HH
