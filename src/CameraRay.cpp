/*!
 * \file CameraRay.cpp
 * \author obayemi
 */

#include <algorithm>
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
        try {
            for (const Mesh * const mesh: scene.getMesh()) {
                if (!intersect) {
                    intersect = new Intersection(mesh->intersect(ray));
                } else {
                    newIntersect = new Intersection(mesh->intersect(ray));
                    if (newIntersect < intersect) {
                        delete intersect;
                        intersect = newIntersect;
                        std::cerr << "INTERSECTION!!!!!" << std::endl;
                    } else {
                        delete newIntersect;
                    }
                }
            }
            if (!intersect)
                throw NoIntersect();
            colors.push_back(intersect->render(scene));
            delete intersect;
        } catch (NoIntersect e) {
            colors.push_back(Color(0x111111ff)); // TODO: replace with default camera color
            //std::cerr << e.what() << std::endl;
        }
    }
    return std::accumulate(colors.begin(), colors.end(), Color(0),
            [](const Color &a, const Color &b) { return a + b; }) * (1.f / (double)colors.size());
}

const std::list<Pixel>		&CameraRay::getPixels() const {
    return this->_pixels;
}
