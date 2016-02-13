/*!
 * \file Scene.cpp
 * \author obayemi
 */

#include <cstddef>

#include "Scene.hh"
#include "Exceptions.hh"
#include "Plane.hh"
#include "Color.hh"

Scene::Scene(std::string config) {
    (void)config;

    this->_cameras.push_back(new Camera(
                Position(0, 0, 0),
                Rotation(Rotation3(0, 0, 0)),
                45,
                //Canevas(21, 16),
                Canevas(21, 21),
                Resolution(800, 600)
                ));

    this->_meshs.push_back(new Plane(
                Position(0, 0, -10),
                Rotation(Rotation3(0, 0, 0)),
                Color(0xff0000ff)
                ));
}

Scene::~Scene() {
}

const std::list<Camera *>	Scene::getCamera() const {
    return this->_cameras;
}

const std::list<Mesh *>		Scene::getMesh() const {
    return this->_meshs;
}

const std::list<Light *>	Scene::getLight() const {
    return this->_lights;
}

