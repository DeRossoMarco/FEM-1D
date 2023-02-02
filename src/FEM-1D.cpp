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
#include <fstream>

int main() {
    constexpr double L = 10.0;
    constexpr double T = 1.0;
    constexpr int N = 20;
    constexpr int Nt = 10;
    constexpr double dt = T / Nt;

    // Output file
    std::ofstream output("output.csv", std::ofstream::out);
    if (!output.is_open()) {
        std::cout << "Error! Cannot open out file!" << std::endl;
        return -1;
    }

    // Functions
    ForcingTerm f([] (double x, double t) -> double { return 1.0; }, L, T);
    CFunction c([] (double x) -> double { return 0.0; }, L);
    DiffusionCoefficient mi([] (double x) -> double { return 1.0; }, L);
    Dirichlet<N> bound_d([](double t){ return 1.0; }, [](double t){ return 1.0; });
    Neumann<N> bound_n([](double t){ return 1.0; }, [](double t){ return 1.0; });

    // FE
    Mesh mesh(L, N);
    SystemMatrix<N> matrix;
    SystemMatrix<N> mass_matrix;
    SystemRhS<N> rhs;
    SystemSol<N> sol;

    // Solve solution at time 0
    matrix.assemble(mesh, c, mi);
    rhs.assemble(mesh, f, 0.0);
    bound_d.apply_g1(matrix, rhs, 0.0);
    bound_n.apply_q2(rhs, 0.0);
    
    sol = Solver<N>::solve_thomas(matrix, rhs);
    output << sol;

    // Solve for each time step
    mass_matrix.assemble_mass(mesh, L);
    matrix *= dt;
    matrix = mass_matrix - matrix;
    for (int i = 1; i < Nt + 1; ++i) {
        rhs.assemble(mesh, f, i * dt);
        rhs *= dt;
        rhs = rhs + matrix * sol;
        
        bound_d.apply_g1(mass_matrix, rhs, i * dt);
        bound_n.apply_q2(rhs, i * dt);
        
        sol = Solver<N>::solve_thomas(mass_matrix, rhs);
        output << sol;
    }

    output.close();
    return 0;
}
