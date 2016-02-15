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

class Camera;
class Mesh;
class Light;

class				Scene {

    private:
        std::list<Camera*>			_cameras;
        std::list<Mesh*>			_meshs;
        std::list<Light*>			_lights;

    private:
        Scene(const Scene &);
        Scene();

        static void					_freeList(std::list<Object *> &list);

    public:
        Scene(const std::string &config);
        ~Scene();

        void						addCamera(Camera *camera);
        void						addMesh(Mesh *mesh);
        void						addLight(Light *light);

        const std::list<Camera *>	getCamera() const;
        const std::list<Mesh *>		getMesh() const;
        const std::list<Light *>	getLight() const;

        void						loadFromJson(const Json::Value &scene);
};

#endif // _SCENE_HH
