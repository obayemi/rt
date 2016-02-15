#ifndef _OBJECT_HH
#define _OBJECT_HH

/*!
 * \file Object.hh
 * \author obayemi
 */

#include "jsoncpp/json/json.h"

#include "Coordinates.hpp"
#include "RotMatrix.hh"
#include "Ray.hh"

class						Object {
    private:
        Position			_position;
        Rotation			_rotation;

        RotMatrix			_rotMatrix;
        RotMatrix			_invRotMatrix;

    public:
        Object();
        Object(const Object &orig);
        Object(const Position &position, const Rotation &rotation);
        virtual ~Object();
        const Position		&getPosition() const;
        const Rotation		&getRotation() const;

        void				translate(const Direction &direction);
        void				rotate(const Rotation &rotation);

        Ray					localize(const Ray &ray) const;
        Ray					globalize(const Ray &ray) const;
};


#endif // _OBJECT_HH

