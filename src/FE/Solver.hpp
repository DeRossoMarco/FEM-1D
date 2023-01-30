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

    Solver(const SystemMatrix<N> &matrix_, const SystemRhS<N> &rhs_) :
        matrix{matrix_},
        rhs{rhs_}
    {}

    SystemSol<N> solve_thomas() {
        std::cout << "Solving linear system with Thomas direct method" << std::endl;

        SystemSol<N> sol;
        SystemRhS<N> rhs_t;
        SystemMatrix<N> matrix_t;

        rhs_t[0] /= matrix[0][0];
        matrix_t[0][1] /= matrix[0][0];  
        for (auto i = 1; i < N - 1; ++i) {
            double r = 1 / (matrix[i][i] - matrix[i][i - 1] * matrix[i - 1][i]);
            rhs_t[i] = r * (rhs[i] - matrix[i][i - 1] * rhs[i - 1]);
            matrix_t[i][i + 1] = r * matrix[i][i + 1];
        }

        for (auto i = N - 2; i > 0; --i) {
            sol[i] = rhs_t[i] - matrix[i][i - 1] * rhs[i + 1];
        }

        return sol;
    }

    private:
    SystemMatrix<N> matrix;
    SystemRhS<N> rhs;
};

#endif
