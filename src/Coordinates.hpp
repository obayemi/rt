#ifndef _COORDINATES_HPP
#define _COORDINATES_HPP

/*!
 * \file Coordinates.hpp
 * \author obayemi
 */

#include <iostream>
#include <cmath>

#include "Exceptions.hh"
#define WHATEVER
#define WHEREVER

/*!
 * \class Vector3
 * \brief tri-dimentional vector
 *
 * Tridimentional vector with Matrix functions
 * Templated to use any type needed
 */
template<typename T>
class				Vector2 {
    private:

    public:
        T				x;
        T				y;

    public:
        Vector2(): x(0), y(0) {};
        Vector2(T x, T y): x(x), y(y) {};
        Vector2(const Vector2 &orig): x(orig.x), y(orig.y) {};
        ~Vector2() {};

        Vector2			&operator=(const Vector2 &other) {
            this->x *= other.x;
            this->y *= other.y;
            return (*this);
        }

        Vector2			&operator*=(T value) {
            this->x *= value;
            this->y *= value;
            return (*this);
        }

        Vector2			operator*(T value) const {
            return (Vector2(*this) *= value);
        }
        
        friend std::ostream& operator<<(std::ostream& out, const Vector2& vector) {
            return out << "(" << vector.x
                << ", "<< vector.y << ")";
        }
};

typedef Vector2<int> Resolution;
typedef Vector2<int> Pixel;
typedef Vector2<double> Canevas;

template<typename T>
class				Vector3 {
    private:

    public:
        T				x;
        T				y;
        T				z;

    public:
        Vector3(): x(0), y(0), z(0) {};
        Vector3(T x, T y, T z): x(x), y(y), z(z) {};
        Vector3(const Vector3 &orig): x(orig.x), y(orig.y), z(orig.z) {};
        ~Vector3() {};

        Vector3			&operator+=(const Vector3<T> &other) {
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return (*this);
        }

        Vector3			operator+(const Vector3<T> &other) const {
            return (Vector3(*this) += other);
        }

        Vector3			&operator*=(T value) {
            this->x *= value;
            this->y *= value;
            this->z *= value;
            return (*this);
        }

        Vector3			operator*(T value) const {
            return (Vector3(*this) *= value);
        }
        
        friend std::ostream& operator<<(std::ostream& out, const Vector3& vector) {
            return out << "(" << vector.x
                << ", "<< vector.y
                << ", "<< vector.z << ")";
        }
};

typedef Vector3<double> Position;
typedef Vector3<double> Direction;
typedef Vector3<double> Rotation3;

template<typename T>
class				Quaternion {
    private:

    public:
        T				a;
        T				b;
        T				c;
        T				d;

    public:
        Quaternion() {
            this->fromVector3(Vector3<T>());
        }

        Quaternion(Vector3<T> vector) {
            this->fromVector3(vector);
        };

        Quaternion(T a, T b, T c, T d): a(a), b(b), c(c), d(d) {};

        Quaternion(const Quaternion &orig):
            a(orig.a), b(orig.b), c(orig.c), d(orig.d) {};

        ~Quaternion() {};

        Quaternion			&fromVector3(const Vector3<T> &vector) {
            double c1 = cos(vector.x/2);
            double s1 = sin(vector.x/2);
            double c2 = cos(vector.y/2);
            double s2 = sin(vector.y/2);
            double c3 = cos(vector.z/2);
            double s3 = sin(vector.z/2);
            double c1c2 = c1*c2;
            double s1s2 = s1*s2;
            this->a = c1c2*c3 - s1s2*s3;
            this->b = c1c2*s3 + s1s2*c3;
            this->c = s1*c2*c3 + c1*s2*s3;
            this->d = c1*s2*c3 - s1*c2*s3;
            return (*this);
        }

        Quaternion			conjugate() const {
            return Quaternion(a, -b, -c, -d);
        }

        Quaternion			&operator*=(T value) {
            this->a *= value;
            this->b *= value;
            this->c *= value;
            this->d *= value;
            return (*this);
        }

        Quaternion			operator*(T value) const {
            return (Quaternion(*this) *= value);
        }
        
        friend std::ostream& operator<<(std::ostream& out, const Quaternion& vector) {
            return out << "(" << vector.a
                << ", "<< vector.b
                << ", "<< vector.c
                << ", "<< vector.d << ")";
        }
};
typedef Quaternion<double> Rotation;

#endif // _COORDINATES_HPP
