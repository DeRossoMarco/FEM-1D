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
#include "timing/Timing.hpp"
 
#include <iostream>
#include <fstream>
#include <cmath>

int main() {
    constexpr double L = 100.0;
    constexpr double T = 0.0;
    constexpr std::size_t N = 100;
    constexpr std::size_t Nt = 1000;
    constexpr double dt = T / Nt;
    constexpr double theta = 1.0;
    constexpr std::size_t num_threads = 10;

    Timing timer(num_threads);
    omp_set_num_threads(num_threads);

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
    Dirichlet<N> bound_d([](double t){ return 0.0; }, [](double t){ return 0.0; });
    Neumann<N> bound_n([](double t){ return 0.0; }, [](double t){ return 0.0; });

    // FE
    Mesh mesh(L, N);
    SystemMatrix<N> matrix;
    SystemMatrix<N> mass_matrix;
    SystemRhS<N> rhs;
    SystemRhS<N> rhs_;
    SystemSol<N> sol;

    output << mesh.get_h() << ", " << dt << std::endl;

    timer.start();

    // Solve solution at time 0
    matrix.assemble(mesh, c, mi);
    rhs.assemble(mesh, f, 0.0);
    bound_d.apply_g1(matrix, rhs, 0.0);
    bound_n.apply_q2(rhs, 0.0);
    
    sol = Solver<N>::solve_thomas(matrix, rhs);
    output << sol;

    // Assemble mass matrix and striffness matrix for theta method 
    mass_matrix.assemble_mass(mesh, L);
    mass_matrix = mass_matrix * (1.0 / dt) + matrix * theta;
    SystemMatrix<N> mass_matrix_;
    mass_matrix_.assemble_mass(mesh, L);
    matrix = mass_matrix_ * (1.0 / dt) - matrix * (1.0 - theta);
    
    for (int i = 1; i < Nt + 1; ++i) {
        // Assemble rhs
        rhs.assemble(mesh, f, (double)i * dt);
        bound_n.apply_q2(rhs, (double)i * dt);
        rhs_.assemble(mesh, f, (double)(i + 1) * dt);
        bound_n.apply_q2(rhs_, (double)(i + 1) * dt);
        rhs = matrix * sol + rhs * (1.0 - theta) + rhs_ * theta;
        
        // Apply boundary conditions
        bound_d.apply_g1(mass_matrix, rhs, (double)i * dt);
        
        sol = Solver<N>::solve_thomas(mass_matrix, rhs);
        output << sol;
    }

    timer.stop();
    timer.print_report();

    output.close();
    return 0;
}
