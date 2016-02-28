/*!
 * \file Solver1.cpp
 * \author obayemi
 */

#include "Solvers.hh"

std::list<double>			Solvers::Solver1(double a, double b) {
    std::list<double>		 results;
    results.push_front(-b/a);
    return results;
}
