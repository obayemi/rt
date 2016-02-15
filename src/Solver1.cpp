/*!
 * \file Solver1.cpp
 * \author obayemi
 */

#include "Solver1.hh"

Solver1::Solver1(double a, double b) {
    this->_result.push_front(-b/a);
}

Solver1::~Solver1() {}
