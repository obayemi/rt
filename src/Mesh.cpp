/*!
 * \file Mesh.cpp
 * \author obayemi
 */

#include "Mesh.hh"

Color		Mesh::defaultColor = Color(0x777777ff);

Mesh::Mesh(): Object(), _color(Mesh::defaultColor) {}

Mesh::Mesh(const Mesh &other): Object(other), _color(other._color) {}

Mesh::Mesh(const Position &position, const Rotation &rotation,
        const Color &color):
    Object(position, rotation), _color(color) {}

Mesh::~Mesh() {}

const Color				&Mesh::getColor() const {
    return this->_color;
}
