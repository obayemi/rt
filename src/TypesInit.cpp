/*!
 * \file Mesh.hh
 * \author obayemi
 */

#include "Object.hh"

#include "Mesh.hh"
#include "Plane.hh"
#include "Sphere.hh"
//#include "Cone.hh"

#include "Camera.hh"

#include "Light.hh"
#include "PointLight.hh"

#include "Texture.hh"
#include "ColorTexture.hh"

void		typesInit() {
    /*
     *Object::registerObject("mesh", &Mesh::fromJson);
     *Object::registerObject("camera", &Mesh::fromJson);
     *Object::registerObject("light", &Mesh::fromJson);
     */

    Mesh::registerMesh("Plane", &Plane::fromJson);
    Mesh::registerMesh("Sphere", &Sphere::fromJson);

    Light::registerLight("Point", &PointLight::fromJson);

    Texture::registerTexture("Color", &ColorTexture::fromJson);
}
