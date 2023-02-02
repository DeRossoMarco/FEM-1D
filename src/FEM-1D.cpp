#include "functions/ForcingTerm.hpp"
#include "functions/CFunction.hpp"
#include "functions/DiffusionCoefficient.hpp"
#include "FEspace/Mesh.hpp"
#include "FE/Solver.hpp"
#include "FE/SystemMatrix.hpp"
#include "FE/SystemRhS.hpp"
#include "FE/SystemSol.hpp"
#include "boundary/Dirichlet.hpp"
#include "boundary/Neumann.hpp"
 
#include <iostream>

int main() {
    constexpr double L = 10.0;
    constexpr double T = 0.0;
    constexpr int N = 10;

    // Functions
    ForcingTerm f([] (double x, double t) -> double { return 1.0; }, L, T);
    CFunction c([] (double x) -> double { return 0.0; }, L);
    DiffusionCoefficient mi([] (double x) -> double { return 1.0; }, L);
    Dirichlet<N> bound_d([](double t){ return 1.0; }, [](double t){ return 1.0; });
    Neumann<N> bound_n([](double t){ return 1.0; }, [](double t){ return 1.0; });

    // FE
    Mesh mesh(L, N);
    SystemMatrix<N> matrix;
    SystemRhS<N> rhs;
    SystemSol<N> sol;

    // Solver
    matrix.assemble(mesh, c, mi);
    rhs.assemble(mesh, f, 0.0);
    bound_d.apply_g1(matrix, rhs, 0.0);
    bound_n.apply_q2(rhs, 0.0);

    std::cout << matrix << rhs;
    
    sol = Solver<N>::solve_thomas(matrix, rhs);

    std::cout << sol;

    return 0;
}
