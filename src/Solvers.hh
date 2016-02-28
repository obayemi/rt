#ifndef _SOLVER_HH
#define _SOLVER_HH

/*!
 * \file Solver.hh
 * \author obayemi
 */

#include <list>

namespace Solvers {
    std::list<double>			Solver1(double a, double b);
    std::list<double>			Solver2(double a, double b, double c);
    std::list<double>			Solver3(double a, double b, double c, double d);
    std::list<double>			Solver4(double a, double b, double c, double d, double e);
};

#endif // _SOLVER_HH
