/*!
 * \file Solver2.cpp
 * \author obayemi
 */

#include <cmath>
#include "Solver2.hh"

Solver2::Solver2(double a, double b, double c) {
    double D = sqrt( (b*b) - (4*a*c) );

    if (D > 0) {
        this->_result.push_front(( -b - D)/(2*a));
        this->_result.push_front(( -b + D)/(2*a));
    } else if (D == 0) {
        this->_result.push_front(( -b )/(2*a));
    }
}

Solver2::~Solver2() {}

