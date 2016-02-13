#ifndef _CAMERA_HH
#define _CAMERA_HH

/*!
 * \file Camera.hh
 * \author obayemi
 */

#include <list>

#include "Coordinates.hpp"
#include "Object.hh"
#include "CameraRay.hh"

#ifndef ABS
#define ABS(x) ((x) < 0 ? (-x) : (x))
#endif //ABS

class CameraRay;

class								Camera : public Object {
    private:
        double						_focalLength;
        Canevas					_canevas;
        Resolution					_resolution;

        unsigned int				_AA;

        Camera();

   public:
        Camera(const Camera &camera);
        Camera(const Position &position, const Rotation &rotation,
                double focalLength, const Canevas &canevas,
                const Resolution &resolution = Resolution(0, 0),
                unsigned int antiAliasing = 0);
        ~Camera();

        void						setAntiAliasing(unsigned int AA);
        void						setResolution(const Resolution &resolition);
        const Resolution			&getResolution() const;

        std::list<CameraRay>		getRays() const;
};


#endif // _CAMERA_HH
