/*!
 * \file Ray.cpp
 * \author obayemi
 */

#include <iostream>

#include "Ray.hh"
#include "Intersection.hh"
#include "Mesh.hh"

Ray::Ray(Position origin, Direction direction, unsigned int depth)
    : _origin(origin), _direction(direction), _depth(depth) {}

Ray::Ray(const Ray &orig)
    : _origin(orig._origin), _direction(orig._direction), _depth(orig._depth) {}

Ray::~Ray() {}

std::ostream& operator<<(std::ostream& out, const Ray& ray) {
    return out << ray._origin << " " << ray._direction;
}

const Position		&Ray::getOrigin() const {
    return this->_origin;
}

const Direction		&Ray::getDirection() const {
    return this->_direction;
}

unsigned int		Ray::getDepth() const {
    return this->_depth;
}

Intersection		*Ray::intersect(const Scene &scene, const Mesh *ignore) {
    Intersection	*intersect = NULL;
    Intersection	*newIntersect = NULL;

    for (const Mesh * const mesh: scene.getMesh()) {
        if (mesh == ignore) {
            continue;
        }
        if ((newIntersect = mesh->intersect(*this)) == NULL)
            continue; // circulez, y'a rien a voir ici ;)
        if (!intersect) {
            intersect = newIntersect;
        } else {
            if (*newIntersect < *intersect) {
                delete intersect;
                intersect = newIntersect;
            } else {
                delete newIntersect;
            }
        }
    }
    return intersect;
}
