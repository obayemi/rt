/*!
 * \file Object.cpp
 * \author obayemi
 */


#include "Object.hh"

Object::Object():
    _position(), _rotation(), _rotMatrix(Rotation()),
    _invRotMatrix(Rotation().conjugate()) {}

Object::Object(const Object &orig):
    _position(orig._position),
    _rotation(orig._rotation),
    _rotMatrix(orig._rotMatrix),
    _invRotMatrix(orig._invRotMatrix) {}

Object::Object(const Position &position, const Rotation &rotation):
    _position(position), _rotation(rotation),
    _rotMatrix(rotation),
    _invRotMatrix(rotation.conjugate()) {}

Object::~Object() {}

const Position		&Object::getPosition() const {
    return this->_position;
}

const Rotation		&Object::getRotation() const {
    return this->_rotation;
}

void			Object::translate(const Direction &direction) {
    (void) direction;
    throw NotImplementedException();
    //this->_position += direction;
}

void			Object::rotate(const Rotation &rotation) {
    (void) rotation;
    throw NotImplementedException();
    //this->_rotation *= rotation;
}

Ray				Object::localize(const Ray &ray) const {
    return Ray(ray.getOrigin() + this->_position * -1,
            this->_invRotMatrix * ray.getDirection());
}

Ray				Object::globalize(const Ray &ray) const {
    return Ray(ray.getOrigin() + this->_position,
            this->_rotMatrix * ray.getDirection());
}
