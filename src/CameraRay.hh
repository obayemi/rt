#ifndef _CAMERARAY_HH
#define _CAMERARAY_HH

/*!
 * \file CameraRay.hh
 * \author obayemi
 */


#include <list>

#include "Coordinates.hpp"
#include "Ray.hh"
#include "Camera.hh"
#include "Color.hh"
#include "Scene.hh"

class Camera;
class Scene;

class								CameraRay{
    private:
        std::list<Pixel>			_pixels;
        std::list<Ray>				_rays;
        const Camera				&_camera;
        bool						_render;

    public:
        CameraRay(const Camera &camera, const Ray &ray,
                const Pixel &pixel, bool render = true);

        Color						render(const Scene &scene) const;
        const std::list<Pixel>		&getPixels() const;
};

#endif // _CAMERARAY_HH