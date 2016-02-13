/*!
 * \file Plane.cpp
 * \author obayemi
 */

#include "Plane.hh"
#include "Exceptions.hh"




template<typename T>
T			solver2(T a, T b) {
    return -b / a;
}


Plane::Plane(): Mesh() {}

Plane::Plane(const Plane &orig): Mesh(orig) {}

Plane::Plane(const Position &position, const Rotation &rotation, const Color &color):
    Mesh(position, rotation, color) {}

Plane::~Plane() {}

Intersection			Plane::intersect(const Ray &ray) const {
    Ray					localRay = this->localize(ray);

    //std::cout << "localized " << ray << " to " << localRay << std::endl;

    double distance = solver2<double>(localRay.getDirection().y, localRay.getOrigin().y);

    std::cout << distance << std::endl;
    if (distance > 0)
        return Intersection(
                Position(
                    ray.getOrigin().x + distance * ray.getDirection().x,
                    ray.getOrigin().y + distance * ray.getDirection().y,
                    ray.getOrigin().z + distance * ray.getDirection().z
                    ),
                Position(
                    localRay.getOrigin().x + distance * localRay.getDirection().x,
                    localRay.getOrigin().y + distance * localRay.getDirection().y,
                    localRay.getOrigin().z + distance * localRay.getDirection().z
                    ),
                *this,
                ray,
                localRay,
                Direction(0, 1, 0),
                distance
                );
    throw NoIntersect();
}
