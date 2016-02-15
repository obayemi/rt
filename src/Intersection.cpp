/*!
 * \file Intersection.cpp
 * \author obayemi
 */

#include "Intersection.hh"
#include "Light.hh"

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

Color					Intersection::render(const Scene &scene) {
    Color				color(0x000000ff);
    Intersection		*intersect;

    for (const Light * const light: scene.getLight()) {
        Ray				lightRay(
                    Position(this->_position),
                    Direction(light->getPosition() + (this->_position * -1))
                );
        intersect = NULL;
        for (const Mesh * const mesh: scene.getMesh()) {
            if (mesh == &this->_mesh)
                continue;
            try {
                intersect = new Intersection(mesh->intersect(lightRay));
            } catch (const NoIntersect &e) {
                intersect = NULL;
                continue;
            }
            if (*intersect < 1.) {
                break;
            }
            delete intersect;
            intersect = NULL;
        }
        if (!intersect) {
            Color		tmp = this->_mesh.getColor() * light->getColor();
            double angle = lightRay.getDirection() / this->_normal;
            tmp *= (angle > 0 ? angle : 0);
            color += tmp;
        } else {
            delete intersect;
        }
    }
    return color;
}

bool					Intersection::operator>(double distance) const {
    return this->_distance > distance;
}

bool					Intersection::operator<(double distance) const {
    return this->_distance < distance;
}

bool					Intersection::operator>(const Intersection &other) const {
    return this->_distance > other._distance;
}

bool					Intersection::operator<(const Intersection &other) const {
    return this->_distance < other._distance;
}
