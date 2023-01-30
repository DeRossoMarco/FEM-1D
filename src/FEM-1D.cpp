#include "functions/ForcingTerm.hpp"
#include "functions/CFunction.hpp"
#include "functions/DiffusionCoefficient.hpp"
#include "FEspace/Mesh.hpp"
#include "FE/Solver.hpp"
#include "FE/SystemMatrix.hpp"
#include "FE/SystemRhS.hpp"
#include "FE/SystemSol.hpp"
 
#include <iostream>

int main() {
    constexpr double L = 1.0;
    constexpr double T = 0.0;
    constexpr int N = 10;

    // Functions
    ForcingTerm f([] (double x, double t) -> double { return x; }, L, T);
    CFunction c([] (double x) -> double { return 1.0; }, L);
    DiffusionCoefficient mi([] (double x) -> double { return 1.0; }, L);

    // FE
    Mesh mesh(L, N);
    SystemMatrix<N + 2> matrix;
    SystemRhS<N + 2> rhs;
    SystemSol<N + 2> sol;

    // Solver
    matrix.assemble(mesh, c, mi);
    rhs.assemble(mesh, f, 0.0);
    Solver<N + 2> solver(matrix, rhs);

    sol = solver.solve_thomas();

    sol.display();

    return 0;
}
