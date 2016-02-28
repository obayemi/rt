/*!
 * \file Plane.cpp
 * \author obayemi
 */

#include "Plane.hh"
#include "Exceptions.hh"
#include "Solvers.hh"
#include "ColorTexture.hh"


Plane::Plane(): Mesh() {}

Plane::Plane(const Plane &orig): Mesh(orig) {}

Plane::Plane(const Position &position, const Rotation &rotation,
        const Texture *texture):
    Mesh(position, rotation, texture) {}

Plane::~Plane() {}

Intersection			*Plane::intersect(const Ray &ray) const {
    Ray					localRay = this->localize(ray);

    double distance = Solvers::Solver1(localRay.getDirection().x, localRay.getOrigin().x).front();

    if (distance > 0)
        return new Intersection(
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
    return NULL;
}

Mesh						*Plane::fromJson(const Json::Value &plane,
        TextureMap &textures) {
    if (textures.find(plane["texture"]["name"].asString()) == textures.end()) {
        textures[plane["texture"]["name"].asString()] = new ColorTexture(plane["texture"]);
    }
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
            textures[plane["texture"]["name"].asString()]
            );
}
