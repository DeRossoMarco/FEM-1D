#include "Solver.hpp"

SystemSol Solver::solve_thomas() {
    SystemSol sol(matrix.size());
    SystemRhS rhs_t(matrix.size());
    SystemMatrix matrix_t(matrix.size());

    rhs_t[0] /= matrix[0][0];
    matrix_t[0][1] /= matrix[0][0];  
    for (auto i = 1; i < matrix.size() - 1; ++i) {
        double r = 1 / (matrix[i][i] - matrix[i][i - 1] * matrix[i - 1][i]);
        rhs_t[i] = r * (rhs[i] - matrix[i][i - 1] * rhs[i - 1]);
        matrix_t[i][i + 1] = r * matrix[i][i + 1];
    }

    for (auto i = matrix.size() - 2; i >= 0; --i) {
        sol[i] = rhs_t[i] - matrix[i][i - 1] * rhs[i + 1];
    }

    return sol;
}
