/*!
 * \file Camera.cpp
 * \author obayemi
 */

#include "Camera.hh"
#include "Color.hh"

Camera::Camera(const Camera &orig):
    Object(orig),
    _focalLength(orig._focalLength),
    _canevas(orig._canevas),
    _resolution(orig._resolution),
    _AA(orig._AA) {}

Camera::Camera(const Position &position, const Rotation &rotation,
        double focalLength, const Canevas &canevas,
        const Resolution &resolution, unsigned int antiAliasing,
        const Texture *texture):
    Object(position, rotation, texture),
    _focalLength(focalLength),
    _canevas(canevas),
    _resolution(resolution),
    _AA(antiAliasing) {
    }

Camera::~Camera() {}

void						Camera::setAntiAliasing(unsigned int AA) {
    this->_AA = AA;
}

const Resolution			&Camera::getResolution() const {
    return this->_resolution;
}

void						Camera::setResolution(const Resolution &resolution) {
    this->_resolution = resolution;
}

Color						Camera::background(const std::list<Ray> &rays) const {
    std::list<Color>		colors;


    for (const Ray &ray: rays) {
        colors.push_front(this->getTexture()->getColor(ray.getDirection()));
    }
    return Color::merge(colors);
}

std::list<CameraRay *>		Camera::getRays() const {
    std::list<CameraRay *>	cameraRays;
    unsigned int			resx = this->_resolution.x;
    unsigned int			resy = this->_resolution.y;

    double					maxx = this->_canevas.x / 2.f;
    double					maxy = this->_canevas.y / 2.f;

    double					pixelsize = ((this->_canevas.x / this->_canevas.y) >
        (((double)resx) / ((double)resy))) ?
        (this->_canevas.x / ((double)resx)) :
        (this->_canevas.y / ((double)resy));

    double					x;
    double					y;

    for (unsigned int pixy = 0; pixy < resy; pixy++) {
        for (unsigned int pixx = 0; pixx < resx; pixx++) {
            x = (-this->_resolution.x / 2 * pixelsize) + pixelsize * pixx;
            y = (-this->_resolution.y / 2 * pixelsize) + pixelsize * pixy;

            cameraRays.push_back(new CameraRay(*this,
                        this->globalize(Ray(Position(), Direction(
                                -y, x, this->_focalLength))),
                        Pixel(pixx, pixy),
                        ABS(x) <= maxx && ABS(y) <= maxy
                        ));
        }
    }
    return cameraRays;
}

Camera						*Camera::fromJson(const Json::Value &camera,
        TextureMap &textures) {
    if (textures.find(camera["background"]["name"].asString()) == textures.end()) {
        textures[camera["background"]["name"].asString()] = new ColorTexture(camera["background"]);
    }
    return new Camera(
            Position(
                camera["position"]["x"].asDouble(),
                camera["position"]["y"].asDouble(),
                camera["position"]["z"].asDouble()
                ),
            Rotation(Rotation3(
                    camera["rotation"]["x"].asDouble(),
                    camera["rotation"]["y"].asDouble(),
                    camera["rotation"]["z"].asDouble()
                    )
                ),
            camera["focal length"].asDouble(),
            Canevas(
                camera["canevas"]["width"].asDouble(),
                camera["canevas"]["height"].asDouble()
                ),
            Resolution(
                camera["resolution"]["width"].asUInt(),
                camera["resolution"]["height"].asUInt()
                ),
            camera["MSAA"].asUInt(),
            textures[camera["background"]["name"].asString()]
            );
}
