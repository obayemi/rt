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
    private:
        double						_focalLength;
        Canevas						_canevas;
        Resolution					_resolution;

        unsigned int				_AA;

    private:
        Camera();

    public:
        Camera(const Camera &camera);
        Camera(const Position &position, const Rotation &rotation,
                double focalLength, const Canevas &canevas,
                const Resolution &resolution,
                unsigned int antiAliasing,
                const Texture *texture);
        ~Camera();

        void						setAntiAliasing(unsigned int AA);
        void						setResolution(const Resolution &resolition);
        const Resolution			&getResolution() const;

        Color						background(const std::list<Ray> &rays) const;

        CameraRay					**getRays() const;

        static Camera				*fromJson(const Json::Value &camera,
                TextureMap &textures);
};


#endif // _CAMERA_HH
