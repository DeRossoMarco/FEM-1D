#ifndef SYSTEM_RHS_HPP
#define SYSTEM_RHS_HPP

#include "../FEspace/Mesh.hpp"
#include "../functions/ForcingTerm.hpp"
#include "../quadrature/Quadrature.hpp"
#include "../FEspace/BaseFunc.hpp"

#include <array>
#include <cstdlib>
#include <iostream>
#include <iomanip>

template<std::size_t N>
class SystemRhS {
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
        for (std::size_t k = 0; k < N; ++k) {
            for (std::size_t i = k; i < k + 2; ++i) {
                rhs[i] +=
                    Quadrature::two_point_quadrature(
                        [&] (double x) -> double {
                            return
                                f(x, t) *
                                BaseFunc::func(mesh, k)(x);
                        },
                        mesh[k],
                        mesh[k + 1]
                    );
            }
        }
    }

    void operator=(const double& i) {
        for (auto& e : rhs) {
            e = i;
        }
    }

    SystemRhS<N> operator+(const SystemRhS<N>& rhs) const {
        SystemRhS<N> rhs_;
        for (int i = 0; i < N + 1; ++i) {
            rhs_[i] = this->rhs[i] + rhs[i];
        }
        return rhs_;
    }

    SystemRhS<N>& operator+=(const SystemRhS<N>& rhs) {
        *this = *this + rhs;
        return *this;
    }

    SystemRhS<N> operator-(const SystemRhS<N>& rhs) const {
        SystemRhS<N> rhs_;
        for (int i = 0; i < N + 1; ++i) {
            rhs_[i] = this->rhs[i] - rhs[i];
        }
    }

    SystemRhS<N>& operator-=(const SystemRhS<N>& rhs) {
        *this = *this - rhs;
        return *this;
    }

    SystemRhS<N> operator*(const double& s) const {
        SystemRhS<N> rhs_;
        for (int i = 0; i < N + 1; ++i) {
            rhs_[i] = s * this->rhs[i];
        }
        return rhs_;
    }

    SystemRhS<N>& operator*=(const double& s) {
        *this = *this * s;
        return *this;
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
    std::array<double, N + 1> rhs;
};

#endif
