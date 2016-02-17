/*!
 * \file Object.cpp
 * \author obayemi
 */


#include "Object.hh"

Object::Object():
    _position(), _rotation(), _rotMatrix(Rotation()),
    _invRotMatrix(Rotation().conjugate()),
    _texture(NULL) {}

Object::Object(const Object &orig):
    _position(orig._position),
    _rotation(orig._rotation),
    _rotMatrix(orig._rotMatrix),
    _invRotMatrix(orig._invRotMatrix),
    _texture(orig._texture) {}

Object::Object(const Position &position, const Rotation &rotation,
        const Texture *texture):
    _position(position), _rotation(rotation),
    _rotMatrix(rotation),
    _invRotMatrix(rotation.conjugate()),
    _texture(texture) {}

Object::~Object() {}

const Position		&Object::getPosition() const {
    return this->_position;
}

const Rotation		&Object::getRotation() const {
    return this->_rotation;
}

const Texture		*Object::getTexture() const {
    return this->_texture;
}

void				Object::translate(const Direction &direction) {
    (void) direction;
    throw NotImplementedException();
    //this->_position += direction;
}

void				Object::rotate(const Rotation &rotation) {
    (void) rotation;
    throw NotImplementedException();
    //this->_rotation *= rotation;
}

Ray					Object::localize(const Ray &ray) const {
    return Ray(ray.getOrigin() + this->_position * -1,
            this->_invRotMatrix * ray.getDirection());
}

Ray					Object::globalize(const Ray &ray) const {
    return Ray(ray.getOrigin() + this->_position,
            this->_rotMatrix * ray.getDirection());
}

std::map<std::string, Object::JsonLoader*>	Object::_objects;

void			Object::registerObject(const std::string &object,
        Object::JsonLoader *loader) {
    Object::_objects[object] = loader;
}

Object		*Object::fromJson(const Json::Value &value, TextureMap &textures) {
    return Object::_objects[value["object"].asString()](value, textures);
}
