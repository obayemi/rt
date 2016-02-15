#ifndef _SOLVER2_HH
#define _SOLVER2_HH

/*!
 * \file Solver2.hh
 * \author obayemi
 */

#include <list>

#include "Solver.hh"

class							Solver2 : public Solver {
    public:
        Solver2(double a, double b, double c);
        ~Solver2();
};

#endif // _SOLVER2_HH


