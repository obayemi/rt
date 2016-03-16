#ifndef _RAY_HH
#define _RAY_HH

/*!
 * \file Ray.hh
 * \author obayemi
 */

#include <iostream>
#include "Coordinates.hpp"
#include "Ray.hh"

class Intersection;
class Scene;
class Mesh;

class						Ray {
    private:
        Ray();

    private:
        Position			_origin;
        Direction			_direction;
        unsigned int		_depth;

    public:
        Ray(Position origin, Direction direction, unsigned int depth = 0);
        Ray(const Ray &orig);
        virtual ~Ray();

        const Position		&getOrigin() const;
        const Direction		&getDirection() const;
        unsigned int		getDepth() const;
        Intersection		*intersect(const Scene &scene, const Mesh *ignore = NULL);

        friend std::ostream& operator<<(std::ostream& out, const Ray& ray);
};

#endif // _RAY_HH
