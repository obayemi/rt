#ifndef _CAMERA_HH
#define _CAMERA_HH

/*!
 * \file Camera.hh
 * \author obayemi
 */

#include <list>
#include <SFML/Graphics.hpp>

#include "jsoncpp/json/json.h"

#include "Coordinates.hpp"
#include "Object.hh"
#include "CameraRay.hh"
#include "Color.hh"

#ifndef ABS
#define ABS(x) ((x) < 0 ? (-x) : (x))
#endif //ABS

class CameraRay;

class								Camera : public Object {
    public:
        static Color				defaultColor;

    private:
        double						_focalLength;
        Canevas						_canevas;
        Resolution					_resolution;

        unsigned int				_AA;
        sf::Image					_background;

        Camera();

   public:
        Camera(const Camera &camera);
        Camera(const Position &position, const Rotation &rotation,
                double focalLength, const Canevas &canevas,
                const Resolution &resolution = Resolution(0, 0),
                unsigned int antiAliasing = 0,
                const Color &color = Camera::defaultColor);
        ~Camera();

        void						setAntiAliasing(unsigned int AA);
        void						setResolution(const Resolution &resolition);
        const Resolution			&getResolution() const;

        Color						background(const std::list<Pixel> &pixels) const;

        std::list<CameraRay *>		getRays() const;

        static Camera				*fromJson(const Json::Value &camera);
};


#endif // _CAMERA_HH
