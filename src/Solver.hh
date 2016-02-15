#ifndef _SOLVER_HH
#define _SOLVER_HH

/*!
 * \file Solver.hh
 * \author obayemi
 */

#include <list>

class									Solver {
    protected:
        std::list<double>		_result;

    public:
        virtual ~Solver() {};
        std::list<double>		solve() const;
};

#endif // _SOLVER_HH
