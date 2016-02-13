/*!
 * \file RotMatrix.cpp
 * \author obayemi
 */

#include "RotMatrix.hh"
#include "Exceptions.hh"

RotMatrix::RotMatrix() {}

RotMatrix::RotMatrix(const RotMatrix &other) {
    *this = other;
}

RotMatrix::RotMatrix(const Rotation &rotation) {
    double a = rotation.a;
    double b = rotation.b;
    double c = rotation.c;
    double d = rotation.d;

    this->_matrix[0][0] = a * a + b * b - c * c - d * d;
    this->_matrix[1][0] = 2 * b * c - 2 * a * d;
    this->_matrix[2][0] = 2 * a * c + 2 * b * d;

    this->_matrix[0][1] = 2 * a * d + 2 * b * c;
    this->_matrix[1][1] = a * a - b * b + c * c - d * d;
    this->_matrix[2][1] = 2 * c * d - 2 * a * b;

    this->_matrix[0][2] = 2 * b * d - 2 * a * c;
    this->_matrix[1][2] = 2 * a * b + 2 * c * d;
    this->_matrix[2][2] = a * a - b * b - c * c + d * d;
}

RotMatrix::~RotMatrix() {}

RotMatrix			&RotMatrix::operator=(const RotMatrix &other) {
    this->_matrix[0][0] = other._matrix[0][0];
    this->_matrix[1][0] = other._matrix[1][0];
    this->_matrix[2][0] = other._matrix[2][0];

    this->_matrix[0][1] = other._matrix[0][1];
    this->_matrix[1][1] = other._matrix[1][1];
    this->_matrix[2][1] = other._matrix[2][1];

    this->_matrix[0][2] = other._matrix[0][2];
    this->_matrix[1][2] = other._matrix[1][2];
    this->_matrix[2][2] = other._matrix[2][2];
    return (*this);
}

RotMatrix			&RotMatrix::operator*=(const RotMatrix &other) {
    return (*this = (RotMatrix(*this) * other));
}

RotMatrix			RotMatrix::operator*(const RotMatrix &other) const {
    RotMatrix		newMatrix;

    newMatrix._matrix[0][0] = this->_matrix[0][0] * other._matrix[0][0] +
        this->_matrix[1][0] * other._matrix[0][1] + this->_matrix[2][0] * other._matrix[0][2];
    newMatrix._matrix[1][0] = this->_matrix[0][0] * other._matrix[1][0] +
        this->_matrix[1][0] * other._matrix[1][1] + this->_matrix[2][0] * other._matrix[1][2];
    newMatrix._matrix[2][0] = this->_matrix[0][0] * other._matrix[2][0] +
        this->_matrix[1][0] * other._matrix[2][1] + this->_matrix[2][0] * other._matrix[2][2];

    newMatrix._matrix[0][1] = this->_matrix[0][1] * other._matrix[0][0] +
        this->_matrix[1][1] * other._matrix[0][1] + this->_matrix[2][1] * other._matrix[0][2];
    newMatrix._matrix[1][1] = this->_matrix[0][1] * other._matrix[1][0] +
        this->_matrix[1][1] * other._matrix[1][1] + this->_matrix[2][1] * other._matrix[1][2];
    newMatrix._matrix[2][1] = this->_matrix[0][1] * other._matrix[2][0] +
        this->_matrix[1][1] * other._matrix[2][1] + this->_matrix[2][1] * other._matrix[2][2];

    newMatrix._matrix[0][2] = this->_matrix[0][2] * other._matrix[0][0] +
        this->_matrix[1][2] * other._matrix[0][1] + this->_matrix[2][2] * other._matrix[0][2];
    newMatrix._matrix[1][2] = this->_matrix[0][2] * other._matrix[1][0] +
        this->_matrix[1][2] * other._matrix[1][1] + this->_matrix[2][2] * other._matrix[1][2];
    newMatrix._matrix[2][2] = this->_matrix[0][2] * other._matrix[2][0] +
        this->_matrix[1][2] * other._matrix[2][1] + this->_matrix[2][2] * other._matrix[2][2];
    return (newMatrix);
}

Direction			RotMatrix::operator*(const Direction &direction) const {
    return Direction(
            this->_matrix[0][0] * direction.x + this->_matrix[1][0] *
            direction.y + this->_matrix[2][0] * direction.z,
            this->_matrix[0][1] * direction.x + this->_matrix[1][1] *
            direction.y + this->_matrix[2][1] * direction.z,
            this->_matrix[0][2] * direction.x + this->_matrix[1][2] *
            direction.y + this->_matrix[2][2] * direction.z
            );
}

