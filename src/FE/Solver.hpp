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
        std::cout << std::endl << "Solving linear system with Thomas direct method" << std::endl;
        SystemSol<N> sol;
        double w;

        sol[0] = rhs[0];

        for (int i = 2; i < N; ++i) {
            w = matrix(i, i - 1) / matrix(i - 1, i - 1);
            matrix(i, i) -= w * matrix(i - 1, i);
            rhs[i] = rhs[i] - w * rhs[i - 1];
        }

        sol[N] = rhs[N] / matrix(N, N);
        for (int i = N - 1; i > 0; --i) {
            sol[i] = (rhs[i] - matrix(i, i + 1) * sol[i + 1]) / matrix(i, i);
        }

        sol[N + 1] = rhs[N + 1];

        return sol;
    }

    private:
};

#endif
