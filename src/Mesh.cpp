/*!
 * \file Mesh.cpp
 * \author obayemi
 */

#include "Mesh.hh"
#include "ColorTexture.hh"

Mesh::Mesh(): Object() {}

Mesh::Mesh(const Mesh &other): Object(other) {}

Mesh::Mesh(const Position &position, const Rotation &rotation,
        const Texture * const texture):
    Object(position, rotation, texture) {}

Mesh::~Mesh() {}

std::map<std::string, Mesh::JsonLoader*>	Mesh::_meshs;

void			Mesh::registerMesh(const std::string &mesh,
        Mesh::JsonLoader *loader) {
    Mesh::_meshs[mesh] = loader;
}

Mesh		*Mesh::fromJson(const Json::Value &value, TextureMap &textures) {
    if (Mesh::_meshs.find(value["mesh"].asString()) == Mesh::_meshs.end()) {
        std::cerr << "Invalid Mesh: " << value["mesh"] << std::endl
            << value << std::endl;
        throw InvalidScene();
    }
    std::cout << "loading Mesh: " << value["mesh"] << std::endl;
    return Mesh::_meshs[value["mesh"].asString()](value, textures);
}
