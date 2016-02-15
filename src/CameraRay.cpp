/*!
 * \file CameraRay.cpp
 * \author obayemi
 */

//#include <functional>

#include "CameraRay.hh"
#include "Camera.hh"
#include "Exceptions.hh"

CameraRay::CameraRay(const Camera &camera, const Ray &ray,
        const Pixel &pixel, bool render): _camera(camera), _render(render) {
    this->_pixels.push_back(pixel);
    this->_rays.push_back(ray);
}

Color			CameraRay::render(const Scene &scene) const {
    if (!this->_render)
        throw NotRendered();

    std::list<Color>		colors;

    Intersection			*intersect = NULL;
    Intersection			*newIntersect = NULL;

    for (const Ray& ray : this->_rays) {
        for (const Mesh * const mesh: scene.getMesh()) {
            try {
                newIntersect = new Intersection(mesh->intersect(ray));
            } catch (const NoIntersect &e) {
                continue;
            }
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
            colors.push_back(this->_camera.background(this->_pixels));
        }
    }
    return Color::merge(colors);
}

const std::list<Pixel>		&CameraRay::getPixels() const {
    return this->_pixels;
}
