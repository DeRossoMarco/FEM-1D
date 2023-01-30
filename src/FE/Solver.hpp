#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "SystemMatrix.hpp"
#include "SystemRhS.hpp"
#include "SystemSol.hpp"

#include <cstdlib>

class Solver {
    public:

    Solver(const SystemMatrix &matrix_, const SystemRhS &rhs_) :
        matrix{matrix_},
        rhs{rhs_}
    {}

    SystemSol solve_thomas();

    private:
    SystemMatrix matrix;
    SystemRhS rhs;
};

#endif
