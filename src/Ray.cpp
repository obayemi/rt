/*!
 * \file Ray.cpp
 * \author obayemi
 */

#include <iostream>

#include "Ray.hh"

Ray::Ray(Position origin, Direction direction)
    : _origin(origin), _direction(direction) {}

Ray::Ray(const Ray &orig)
    : _origin(orig._origin), _direction(orig._direction) {}

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
