#ifndef SYSTEM_RHS_HPP
#define SYSTEM_RHS_HPP

#include "../FEspace/Mesh.hpp"

#include "../functions/ForcingTerm.hpp"

#include <vector>
#include <cstdlib>

class SystemRhS{
    public:

    SystemRhS(const std::size_t &N) {
        rhs.resize(N + 2);
        clear();
    }

    double& operator[](const std::size_t &i);

    double operator[](const std::size_t &i) const;

    void assemble(const Mesh &mesh, const ForcingTerm &f, const double &t);

    void clear();

    private:
    std::vector<double> rhs;
};

#endif
