#ifndef SYSTEM_RHS_HPP
#define SYSTEM_RHS_HPP

#include "../FEspace/Mesh.hpp"
#include "../functions/ForcingTerm.hpp"
#include "../Quadrature/Quadrature.hpp"
#include "../FEspace/BaseFunc.hpp"

#include <array>
#include <cstdlib>
#include <iostream>

template<std::size_t N>
class SystemRhS{
    public:

    SystemRhS() : rhs() {}

    double& operator[](const std::size_t &i) {
        return rhs[i];
    }

    double operator[](const std::size_t &i) const {
        return rhs[i];
    }

    void assemble(const Mesh &mesh, const ForcingTerm &f, const double &t) {
        std::cout << "Assemblig system RhS" << std::endl;
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

    void clear() {
        for (auto e : rhs) {
            e = 0.0;
        }
    }

    private:
    std::array<double, N> rhs;
};

#endif
