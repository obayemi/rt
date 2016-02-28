/*!
 * \file CameraRay.cpp
 * \author obayemi
 */

//#include <functional>

#include "CameraRay.hh"
#include "Camera.hh"
#include "Exceptions.hh"

CameraRay::CameraRay(const Camera &camera, const Ray &ray,
        const Pixel &pixel, bool render): _camera(camera), _render(render),
        _rendered(false) {
    this->_pixels.push_back(pixel);
    this->_rays.push_back(ray);
}
CameraRay::CameraRay(const Camera &camera, const std::list<Ray> &rays,
                const std::list<Pixel> &pixels, bool render):
    _pixels(pixels), _rays(rays), _camera(camera), _render(render),  _rendered(false) {}

CameraRay::~CameraRay() {}

bool						CameraRay::getRendered() const {
    return this->_rendered;
}
void						CameraRay::setRendered() {
    this->_rendered |= true;
}

Color			CameraRay::render(const Scene &scene) const {
    if (!this->_render)
        throw NotRendered();

    std::list<Color>		colors;

    Intersection			*newIntersect = NULL;

    for (const Ray& ray : this->_rays) {
        Intersection			*intersect = NULL;
        for (const Mesh * const mesh: scene.getMesh()) {
            if ((newIntersect = mesh->intersect(ray)) == NULL)
                continue; // circulez, y'a rien a voir ici ;)
            if (!intersect) {
                intersect = newIntersect;
            } else {
                if (*newIntersect < *intersect) {
                    delete intersect;
                    intersect = newIntersect;
                } else {
                    delete newIntersect;
                }
            }
        }
        if (intersect) {
            colors.push_back(intersect->render(scene));
            delete intersect;
        } else {
            colors.push_back(this->_camera.background(this->_rays));
        }
    }
    return Color::merge(colors);
}

const std::list<Pixel>		&CameraRay::getPixels() const {
    return this->_pixels;
}
