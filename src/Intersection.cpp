/*!
 * \file Intersection.cpp
 * \author obayemi
 */

#include "Intersection.hh"
#include "Light.hh"

Intersection::Intersection(const Intersection &other) :
        _position(other._position),
        _localPosition(other._localPosition),
        _mesh(other._mesh),
        _ray(other._ray),
        _localray(other._localray),
        _normal(other._normal.normal()),
        _distance(other._distance) {
        };

Intersection::Intersection(
        const Position &position,
        const Position &localPosition,
        const Mesh &mesh,
        const Ray &ray,
        const Ray &localray,
        const Direction &normal,
        double distance) :
        _position(position),
        _localPosition(localPosition),
        _mesh(mesh),
        _ray(ray),
        _localray(localray),
        _normal(normal.normal()),
        _distance(distance) {}
;
Intersection::~Intersection() {}

Color					Intersection::render(const Scene &scene) {
    Color				color(0x000000ff);
    Intersection		*intersect;
    std::list<Color>	colors;

    for (const Light * const light: scene.getLight()) {
        Color			lightTmp(0x000000ff);
        for (unsigned int i = 0; i < light->getSamples(); i++){
            Ray				lightRay(
                    Position(this->_position),
                    Direction(light->getPosition() + (this->_position * -1))
                    );
            intersect = NULL;
            for (const Mesh * const mesh: scene.getMesh()) {
                if (mesh == &this->_mesh)
                    continue;
                if ((intersect = mesh->intersect(lightRay)) == NULL)
                    continue;
                if (*intersect < 1.) {
                    break;
                }
                delete intersect;
                intersect = NULL;
            }
            if (!intersect) {
                Color		tmp = light->getTexture()->getColor(lightRay.getDirection() * -1);
                double angle = lightRay.getDirection() / this->_normal;
                tmp *= (angle > 0 ? angle : 0);

                lightTmp += tmp;
            } else {
                delete intersect;
            }
        }
        color += lightTmp * (1.f  / (double)light->getSamples());
    }

    if (this->_ray.getDepth() < 1 ) {
        Ray		reflectionRay(this->_position,
                this->_normal.reflect(this->_ray.getDirection()),
                this->_ray.getDepth() + 1);
        /*
         *std::cout << this->_ray << std::endl 
         *    << reflectionRay << std::endl;
         */

        //color = Color(0x000000ff);
        if ((intersect = reflectionRay.intersect(scene, &this->_mesh)) != NULL) {
            color = color * 0.5 + (intersect->render(scene) * 0.5);
            delete intersect;
        }
    }
    

    /*
     *std::cout
     *    << "light sum: " << color
     *    << std::endl
     *    << "texture: " << this->_mesh.getTexture()->getColor(Direction(this->_normal))
     *    << std::endl
     *    << "sum: "<< this->_mesh.getTexture()->getColor(Direction(this->_normal)) * color
     *    << std::endl
     *    << std::endl;
     */
    return this->_mesh.getTexture()->getColor(Direction(this->_normal)) * color;
    //return color;
}

bool					Intersection::operator>(double distance) const {
    return this->_distance > distance;
}

bool					Intersection::operator<(double distance) const {
    return this->_distance < distance;
}

bool					Intersection::operator>(const Intersection &other) const {
    return this->_distance > other._distance;
}

bool					Intersection::operator<(const Intersection &other) const {
    return this->_distance < other._distance;
}
