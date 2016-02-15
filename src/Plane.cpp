/*!
 * \file Plane.cpp
 * \author obayemi
 */

#include "Plane.hh"
#include "Exceptions.hh"
#include "Solver1.hh"


Plane::Plane(): Mesh() {}

Plane::Plane(const Plane &orig): Mesh(orig) {}

Plane::Plane(const Position &position, const Rotation &rotation, const Color &color):
    Mesh(position, rotation, color) {}

Plane::~Plane() {}

Intersection			Plane::intersect(const Ray &ray) const {
    Ray					localRay = this->localize(ray);

    double distance = Solver1(localRay.getDirection().x, localRay.getOrigin().x).solve().front();

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
                Direction(1, 0, 0),
                distance
                );
    throw NoIntersect();
}

Plane						*Plane::fromJson(const Json::Value &plane) {
    return new Plane(
            Position(
                plane["position"]["x"].asDouble(),
                plane["position"]["y"].asDouble(),
                plane["position"]["z"].asDouble()
             ),
            Rotation(Rotation3(
                plane["rotation"]["x"].asDouble(),
                plane["rotation"]["y"].asDouble(),
                plane["rotation"]["z"].asDouble()
             )),
            Color(
                    plane["color"]["color"]["r"].asUInt(),
                    plane["color"]["color"]["g"].asUInt(),
                    plane["color"]["color"]["b"].asUInt()
                 )
            );
}
