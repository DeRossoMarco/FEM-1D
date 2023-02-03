#ifndef SOLVER_HPP
#define SOLVER_HPP

#include "SystemMatrix.hpp"
#include "SystemRhS.hpp"
#include "SystemSol.hpp"

#include <cstdlib>
#include <iostream>

template<std::size_t N>
class Solver {
    public:

    static SystemSol<N> solve_thomas(SystemMatrix<N> matrix, SystemRhS<N> rhs) {
        SystemSol<N> sol;
        double w;

        for (std::size_t i = 1; i < N + 1; ++i) {
            w = matrix(i, i - 1) / matrix(i - 1, i - 1);
            matrix(i, i) -= w * matrix(i - 1, i);
            rhs[i] = rhs[i] - w * rhs[i - 1];
        }

        sol[N] = rhs[N] / matrix(N, N);
        for (std::size_t i = N; i > 0; --i) {
            sol[i - 1] = (rhs[i - 1] - matrix(i - 1, i) * sol[i]) / matrix(i - 1, i - 1);
        }

        return sol;
    }

    private:
};

#endif
