#ifndef SYSTEM_RHS_HPP
#define SYSTEM_RHS_HPP

#include "../FEspace/Mesh.hpp"
#include "../functions/ForcingTerm.hpp"
#include "../quadrature/Quadrature.hpp"
#include "../FEspace/BaseFunc.hpp"
#include "../boundary/Neumann.hpp"

#include <array>
#include <cstdlib>
#include <iostream>
#include <iomanip>

template<std::size_t N>
class SystemRhS{
    public:

    SystemRhS() {
        this->operator=(0.0);
    }

    double& operator[](const std::size_t &i) {
        return rhs[i];
    }

    double operator[](const std::size_t &i) const {
        return rhs[i];
    }

    void assemble(const Mesh &mesh, const ForcingTerm &f, const double &t) {
        std::cout << std::endl << "Assemblig system RhS" << std::endl;
        for (std::size_t k = 1; k < N + 1; ++k) {
            for (std::size_t i = k; i < k + 2; ++i) {
                rhs[k] +=
                    Quadrature::two_point_quadrature(
                        [&] (double x) -> double {
                            return
                                f(x, t) *
                                BaseFunc::func(mesh, k)(x);
                        },
                        mesh[i - 1],
                        mesh[i]
                    );
            }
        }
    }

    void assemble(const Mesh &mesh,
                  const ForcingTerm &f,
                  const double &t,
                  const Neumann& bound) {
        rhs[0] +=
            Quadrature::two_point_quadrature(
                [&] (double x) -> double {
                    return
                        f(x, t) *
                        BaseFunc::func(mesh, 0)(x);
                },
                mesh[0],
                mesh[1]
            ) +
            bound(0, t);
        assemble(mesh, f, t);
        rhs[N + 1] +=
            Quadrature::two_point_quadrature(
                [&] (double x) -> double {
                    return
                        f(x, t) *
                        BaseFunc::func(mesh, N + 1)(x);
                },
                mesh[N],
                mesh[N + 1]
            ) +
            bound(N + 1, t);
    }

    void operator=(const double& i) {
        for (auto& e : rhs) {
            e = i;
        }
    }

    auto begin() const {
        return rhs.begin();
    }

    auto end() const {
        return rhs.end();
    }

    friend std::ostream& operator<<(std::ostream& os, const SystemRhS& rhs) {
        for (auto e : rhs) {
            os << std::setw(5) << std::setprecision(3) << e << std::endl;
        }
        return os;
    }

    private:
    std::array<double, N + 2> rhs;
};

#endif
