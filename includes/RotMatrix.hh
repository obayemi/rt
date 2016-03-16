#ifndef _ROTMATRIX_HH
#define _ROTMATRIX_HH

/*!
 * \file RotMatrix.hh
 * \author obayemi
 */

#include "Coordinates.hpp"

class				RotMatrix {
    private:
        RotMatrix();

        double		_matrix[3][3];

    public:
        RotMatrix(const RotMatrix &other);
        RotMatrix(const Rotation &rotation);
        ~RotMatrix();

        RotMatrix			&operator=(const RotMatrix &other);
        RotMatrix			&operator*=(const RotMatrix &other);
        RotMatrix			operator*(const RotMatrix &other) const;

        Direction			operator*(const Direction &direction) const;
};

#endif /* _ROTMATRIX_HH */

