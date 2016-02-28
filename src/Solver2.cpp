/*!
 * \file Solver2.cpp
 * \author obayemi
 */

#include <cmath>
#include <list>
#include "Solvers.hh"

std::list<double>			Solvers::Solver2(double a, double b, double c) {
    std::list<double>		results;
    double D = sqrt( (b*b) - (4*a*c) );

    if (D > 0) {
        results.push_front(( -b - D)/(2*a));
        results.push_front(( -b + D)/(2*a));
    } else if (D == 0) {
        results.push_front(( -b )/(2*a));
    }
    return results;
}
