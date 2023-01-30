#include "SystemRhS.hpp"
#include "../Quadrature/Quadrature.hpp"
#include "../FEspace/BaseFunc.hpp"

double& SystemRhS::operator[](const std::size_t &i) {
    return rhs[i];
}

double SystemRhS::operator[](const std::size_t &i) const {
    return rhs[i];
}

void SystemRhS::assemble(const Mesh &mesh, const ForcingTerm &f, const double &t) {
    for (std::size_t k = 1; k < mesh.get_size(); ++k) {
        for (std::size_t i = k; i < k + 2; ++i) {
            rhs[i] +=
                Quadrature::two_point_quadrature(
                    [&] (double x) -> double {
                        return
                            f.value(x, t) *
                            BaseFunc::func(mesh, i)(x);
                    },
                    mesh[k],
                    mesh[k + 1]
                );
        }
    }
}

void SystemRhS::clear() {
    for (auto e : rhs) {
        e = 0.0;
    }
}
