#ifndef _SCENE_HH
#define _SCENE_HH

/*!
 * \file Scene.hh
 * \author obayemi
 */

#include <list>
#include <string>

#include "Camera.hh"
#include "Mesh.hh"
#include "Light.hh"

class Light;
class Mesh;
class Camera;

class				Scene {

    private:
        std::list<Camera*>	_cameras;
        std::list<Mesh*>		_meshs;
        std::list<Light*>	_lights;

    private:
        Scene(const Scene &);
        Scene();

    public:
        Scene(std::string config);
        ~Scene();

        const std::list<Camera *>	getCamera() const;
        const std::list<Mesh *>		getMesh() const;
        const std::list<Light *>	getLight() const;
};

#endif // _SCENE_HH
