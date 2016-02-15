/*!
 * \file Camera.cpp
 * \author obayemi
 */

#include "Camera.hh"
#include "Color.hh"

Color				Camera::defaultColor = Color(0x111111ff);

Camera::Camera(const Camera &orig):
    Object(orig),
    _focalLength(orig._focalLength),
    _canevas(orig._canevas),
    _resolution(orig._resolution),
    _AA(orig._AA),
    _background(orig._background) {}

Camera::Camera(const Position &position, const Rotation &rotation,
        double focalLength, const Canevas &canevas,
        const Resolution &resolution, unsigned int antiAliasing,
        const Color &color):
    Object(position, rotation),
    _focalLength(focalLength),
    _canevas(canevas),
    _resolution(resolution),
    _AA(antiAliasing) {
        this->_background.create(this->getResolution().x, this->getResolution().y,
                sf::Color(color.getR(), color.getG(), color.getB(), color.getA()));
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

Color						Camera::background(const std::list<Pixel> &pixels) const {
    std::list<Color>		colors;
    sf::Color				color;


    for (const Pixel &pixel: pixels) {
        color = this->_background.getPixel(pixel.x, pixel.y);
        colors.push_front(Color(color.r, color.g, color.b, color.a));
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

Camera						*Camera::fromJson(const Json::Value &camera) {
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
             )),
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
            Color(
                    camera["background"]["color"]["r"].asUInt(),
                    camera["background"]["color"]["g"].asUInt(),
                    camera["background"]["color"]["b"].asUInt()
                 )
            );
}
