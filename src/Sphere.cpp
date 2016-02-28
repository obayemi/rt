/*!
 * \file Sphere.cpp
 * \author obayemi
 */

#include "Sphere.hh"
#include "Exceptions.hh"
#include "Solvers.hh"
#include "ColorTexture.hh"


Sphere::Sphere(): Mesh() {}

Sphere::Sphere(const Sphere &orig): Mesh(orig) {}

Sphere::Sphere(const Position &position, const Rotation &rotation,
        double radius, const Texture *texture):
    Mesh(position, rotation, texture), _radius(radius) {}

Sphere::~Sphere() {}

Intersection			*Sphere::intersect(const Ray &ray) const {
    Ray					localRay = this->localize(ray);
    double dx = localRay.getDirection().x;
    double dy = localRay.getDirection().y;
    double dz = localRay.getDirection().z;
    double ox = localRay.getOrigin().x;
    double oy = localRay.getOrigin().y;
    double oz = localRay.getOrigin().z;

    std::list<double> distances = Solvers::Solver2(
            dx*dx + dy*dy + dz*dz,
            2*(dx*ox + dy*oy + dz*oz),
            ox*ox + oy*oy + oz*oz - this->_radius
            );
    double distance = -1;
    for (double tmp: distances) {
        if (tmp > 0 && (tmp < distance || distance < 0)) {
            distance = tmp;
        }
    }

    if (distance > 0) {
        Position localposition = Position(
                    ox + distance * dx,
                    oy + distance * dy,
                    oz + distance * dz
                    );
        return new Intersection(
                Position(
                    ray.getOrigin().x + distance * ray.getDirection().x,
                    ray.getOrigin().y + distance * ray.getDirection().y,
                    ray.getOrigin().z + distance * ray.getDirection().z
                    ),
                localposition,
                *this,
                ray,
                localRay,
                //this->_rotMatrix * localposition,
                localposition,
                distance
                );
    }
    return NULL;
}

Mesh						*Sphere::fromJson(const Json::Value &sphere,
        TextureMap &textures) {
    if (textures.find(sphere["texture"]["name"].asString()) == textures.end()) {
        textures[sphere["texture"]["name"].asString()] = new ColorTexture(sphere["texture"]);
    }
    return new Sphere(
            Position(
                sphere["position"]["x"].asDouble(),
                sphere["position"]["y"].asDouble(),
                sphere["position"]["z"].asDouble()
             ),
            Rotation(Rotation3(
                sphere["rotation"]["x"].asDouble(),
                sphere["rotation"]["y"].asDouble(),
                sphere["rotation"]["z"].asDouble()
             )),
            sphere["radius"].asDouble(),
            textures[sphere["texture"]["name"].asString()]
            );
}
