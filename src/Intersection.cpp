/*!
 * \file Intersection.cpp
 * \author obayemi
 */

#include "Intersection.hh"

Intersection::Intersection(const Intersection &other) :
        _position(other._position),
        _localPosition(other._localPosition),
        _mesh(other._mesh),
        _ray(other._ray),
        _localray(other._localray),
        _normal(other._normal),
        _distance(other._distance) {};

Intersection::Intersection(
        const Position &position,
        const Position &localPosition,
        const Mesh &mesh,
        const Ray &ray,
        const Ray &localray,
        const Direction &normal,
        double distance) :
        _position(position),
        _localPosition(localPosition),
        _mesh(mesh),
        _ray(ray),
        _localray(localray),
        _normal(normal),
        _distance(distance) {}
;
Intersection::~Intersection() {}

Color				Intersection::render(const Scene &scene) {
    return this->_mesh.getColor();
}

bool					Intersection::operator>(const Intersection &other) const {
    return this->_distance > other._distance;
}

bool					Intersection::operator<(const Intersection &other) const {
    return this->_distance < other._distance;
}
