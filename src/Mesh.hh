#ifndef _MESH_HH
#define _MESH_HH

/*!
 * \file Mesh.hh
 * \author obayemi
 */

#include "Ray.hh"
#include "Intersection.hh"
#include "Object.hh"
#include "Scene.hh"

class Scene;
class Intersection;

class							Mesh : public Object {
    public:
        Color					_color;

    protected:
        static Color			defaultColor;

    public:
        Mesh();
        Mesh(const Mesh &other);
        Mesh(const Position &position, const Rotation &rotation,
                const Color &color = Mesh::defaultColor);
        virtual ~Mesh();

        virtual Intersection	intersect(const Ray &ray) const = 0;
        const Color				&getColor() const;
};

#endif // _MESH_HH
