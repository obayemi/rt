/*!
 * \file Scene.cpp
 * \author obayemi
 */

#include <cstddef>
#include <fstream>

#include "jsoncpp/json/json.h"

#include "Camera.hh"
#include "Mesh.hh"
#include "Light.hh"

#include "Scene.hh"
#include "Exceptions.hh"
#include "Color.hh"
#include "Sphere.hh"
#include "Plane.hh"

Scene::Scene(const std::string &config) {
    Json::Value scene;
    std::ifstream sceneFile(config, std::ifstream::binary);
    try {
        sceneFile >> scene;
    } catch (const Json::RuntimeError &e) {
        std::cerr << "Invalid scene file (" << e.what() << ")" << std::endl;
        throw InvalidScene();
    }
    this->loadFromJson(scene);
}

Scene::~Scene() {
    Camera *camera;
    while (!this->_cameras.empty()) {
        camera = this->_cameras.front();
        this->_cameras.remove(camera);
        delete camera;
    }
    Mesh		*mesh;
    while (!this->_meshs.empty()) {
        mesh = this->_meshs.front();
        this->_meshs.remove(mesh);
        delete mesh;
    }
    Light *light;
    while (!this->_lights.empty()) {
        light = this->_lights.front();
        this->_lights.remove(light);
        delete light;
    }
}

void						Scene::addCamera(Camera *camera) {
    this->_cameras.push_back(camera);
}

void						Scene::addMesh(Mesh *mesh) {
    this->_meshs.push_back(mesh);
}

void						Scene::addLight(Light *light) {
    this->_lights.push_back(light);
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

void						Scene::loadFromJson(const Json::Value &scene ) {
    for (const Json::Value &value: scene["textures"]) {
        this->_textures[value["name"].asString()] = new ColorTexture(value);
    }
    for (const Json::Value &value: scene["objects"]) {
        if (value["object"] == Json::nullValue) {
            std::cerr << "invalid object with no object" << std::endl
                << value << std::endl;
            throw InvalidScene();
        } else if (value["object"].asString() == "Camera") {
            this->addCamera(Camera::fromJson(value, this->_textures));
        } else if (value["object"].asString() == "Mesh") {
            this->addMesh(Mesh::fromJson(value, this->_textures));
        } else if (value["object"] == "Light") {
            this->addLight(Light::fromJson(value, this->_textures));
        } else {
            std::cerr << "invalid object: " << value["object"] << std::endl
                << value << std::endl;
            throw InvalidScene();
        }
    }
}
