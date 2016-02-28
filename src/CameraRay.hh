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
        bool						_rendered;

    public:
        CameraRay(const Camera &camera, const std::list<Ray> &rays,
                const std::list<Pixel> &pixels, bool render = true);
        CameraRay(const Camera &camera, const Ray &ray,
                const Pixel &pixel, bool render = true);
        ~CameraRay();

        bool						getRendered() const;
        void						setRendered();

        Color						render(const Scene &scene) const;
        const std::list<Pixel>		&getPixels() const;
};

#endif // _CAMERARAY_HH
