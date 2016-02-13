#ifndef _RAY_HH
#define _RAY_HH

/*!
 * \file Ray.hh
 * \author obayemi
 */

#include <iostream>
#include "Coordinates.hpp"

class Ray {
    private:
        Ray();

    public:
        Position _origin;
        Direction _direction;

    public:
        Ray(Position origin, Direction direction);
        Ray(const Ray &orig);
        virtual ~Ray();

        const Position		&getOrigin() const;
        const Direction		&getDirection() const;

        friend std::ostream& operator<<(std::ostream& out, const Ray& ray);
};

#endif // _RAY_HH
