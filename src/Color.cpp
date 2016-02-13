/*!
 * \file Color.cpp
 * \author obayemi
 */

#include <iomanip>
#include <iostream>

#include "Color.hh"

Color::Color(uint32 color) {
    uint8		*splitcolor = (uint8*)(&color);
    this->_r = splitcolor[3];
    this->_g = splitcolor[2];
    this->_b = splitcolor[1];
    this->_a = splitcolor[0];
}

Color::Color(const Color &other):
    _r(other._r), _g(other._g), _b(other._b), _a(other._a) {}

Color::Color(uint8 r,uint8 g,uint8 b, uint8 a):
    _r(r), _g(g), _b(b), _a(a) {}

Color::~Color() {}

uint32			Color::getColor() const {
    uint8		splitcolor[4] = {
        this->getA(),
        this->getB(),
        this->getG(),
        this->getR()
    };
    return *(uint32*)splitcolor;

}
uint8			Color::getR() const {
    return (this->_r > (uint8)-1) ? (uint8)-1 : this->_r;
}
uint8			Color::getG() const {
    return (this->_g > (uint8)-1) ? (uint8)-1 : this->_g;
}
uint8			Color::getB() const {
    return (this->_b > (uint8)-1) ? (uint8)-1 : this->_b;
}
uint8			Color::getA() const {
    return (this->_a > (uint8)-1) ? (uint8)-1 : this->_a;
}

Color			&Color::operator*=(double scalar) {
    this->_r *= scalar;
    this->_g *= scalar;
    this->_b *= scalar;
    this->_a *= scalar;
    return (*this);
}

Color			Color::operator*(double scalar) const {
    return (Color(*this) *= scalar);
}

Color			&Color::operator+=(const Color &other) {
    this->_r += other._r;
    this->_g += other._g;
    this->_b += other._b;
    this->_a += other._a;
    return (*this);
}

Color			Color::operator+(const Color &other) const {
    return (Color(*this) += other);
}

std::ostream&	operator<<(std::ostream& out, const Color& color) {
    return out << std::hex << std::showbase << std::setfill('0') << std::setw(8)
        << color.getColor()
        << std::dec
        << " ("
        << color._r << ", "
        << color._g << ", "
        << color._b << ", "
        << color._a
        <<")";
}
