#ifndef SYSTEM_MATRIX_HPP
#define SYSTEM_MATRIX_HPP

#include "../FEspace/Mesh.hpp"
#include "../functions/CFunction.hpp"
#include "../functions/DiffusionCoefficient.hpp"
#include "../quadrature/Quadrature.hpp"
#include "../FEspace/BaseFunc.hpp"
#include "SystemRhS.hpp"
#include "TridiagMatrix.hpp"
#include "SystemSol.hpp"

#include <array>
#include <cstdlib>
#include <iterator>
#include <iostream>
#include <iomanip>
#include <omp.h>

template<std::size_t N>
class SystemMatrix{
    public:

    double& operator()(const std::size_t& i, const std::size_t& j) {
        return matrix(i, j);
    }

    double operator()(const std::size_t& i, const std::size_t& j) const {
        return matrix(i, j);
    }

    std::size_t size() const {
        return matrix.size();
    }

    void assemble(const Mesh &mesh,
                  const CFunction &c,
                  const DiffusionCoefficient &mi) {
        #pragma omp parallel for num_threads(1)
        for (std::size_t k = 0; k < N; ++k) {
            for (std::size_t i = k; i < k + 2; ++i) {
                for (std::size_t j = k; j < k + 2; ++j) {
                    matrix(i, j) +=
                        Quadrature::two_point_quadrature(
                            [&] (double x) -> double {
                                return
                                    mi.value(x) * 
                                    BaseFunc::d_func(mesh, i)(x) *
                                    BaseFunc::d_func(mesh, j)(x);
                            },
                            mesh[k],
                            mesh[k + 1]
                        ) + 
                        Quadrature::two_point_quadrature(
                            [&] (double x) -> double {
                                return
                                    c.value(x) *
                                    BaseFunc::func(mesh, i)(x) *
                                    BaseFunc::func(mesh, j)(x);
                            },
                            mesh[k],
                            mesh[k + 1]
                        );
                }
            }
        }
    }

    void assemble_mass(const Mesh &mesh, const double& L) {
        CFunction c([](double){ return 1.0; }, L);
        DiffusionCoefficient d([](double){ return 0.0; }, L);
        assemble(mesh, c, d);
    }

    void operator=(const double& d) {
        matrix = d;
    }

    SystemMatrix<N> operator+(const SystemMatrix<N>& matrix) const {
        SystemMatrix<N> matrix_;
        matrix_(0, 0) = this->matrix(0, 0) + matrix(0, 0);
        matrix_(0, 1) = this->matrix(0, 1) + matrix(0, 1);
        for (int i = 1; i < N; i++) {
            matrix_(i, i - 1) = this->matrix(i, i - 1) + matrix(i, i - 1);
            matrix_(i, i) = this->matrix(i, i) + matrix(i, i);
            matrix_(i, i + 1) = this->matrix(i, i + 1) + matrix(i, i + 1);
        }
        matrix_(N - 1, N - 2) = this->matrix(N - 1, N - 2) + matrix(N - 1, N - 2);
        matrix_(N - 1, N - 1) = this->matrix(N - 1, N - 1) + matrix(N - 1, N - 1);
        return matrix_;
    }

    SystemMatrix<N>& operator+=(const SystemMatrix<N>& matrix) {
        *this = *this + matrix;
        return *this;
    }

    SystemMatrix<N> operator-(const SystemMatrix<N>& matrix) const {
        SystemMatrix<N> matrix_;
        matrix_(0, 0) = this->matrix(0, 0) - matrix(0, 0);
        matrix_(0, 1) = this->matrix(0, 1) - matrix(0, 1);
        for (int i = 1; i < N; i++) {
            matrix_(i, i - 1) = this->matrix(i, i - 1) - matrix(i, i - 1);
            matrix_(i, i) = this->matrix(i, i) - matrix(i, i);
            matrix_(i, i + 1) = this->matrix(i, i + 1) - matrix(i, i + 1);
        }
        matrix_(N - 1, N - 2) = this->matrix(N - 1, N - 2) - matrix(N - 1, N - 2);
        matrix_(N - 1, N - 1) = this->matrix(N - 1, N - 1) - matrix(N - 1, N - 1);
        return matrix_;
    }

    SystemMatrix<N>& operator-=(const SystemMatrix<N>& matrix) {
        *this = *this - matrix;
        return *this;
    }

    SystemMatrix<N> operator*(const double& s) const {
        SystemMatrix<N> matrix_;
        matrix_(0, 0) = s * this->matrix(0, 0);
        matrix_(0, 1) = s * this->matrix(0, 1);
        for (int i = 1; i < N; i++) {
            matrix_(i, i - 1) = s * this->matrix(i, i - 1);
            matrix_(i, i) = s * this->matrix(i, i);
            matrix_(i, i + 1) = s * this->matrix(i, i + 1);
        }
        matrix_(N - 1, N - 2) = s * this->matrix(N - 1, N - 2);
        matrix_(N - 1, N - 1) = s * this->matrix(N - 1, N - 1);
        return matrix_;
    }

    SystemMatrix<N>& operator*=(const double& s) {
        *this = *this * s;
        return *this;
    }

    SystemRhS<N> operator*(const SystemSol<N>& vec) const {
        SystemRhS<N> rhs;
        rhs[0] = this->matrix(0, 0) * vec[0] + this->matrix(0, 1) * vec[1];
        for (int i = 1; i < N; i++) {
            rhs[i] =    this->matrix(i, i - 1) * vec [i - 1] +
                        this->matrix(i, i) * vec[i] +
                        this->matrix(i, i + 1) * vec[i + 1];
        }
        rhs[N] = this->matrix(N, N - 1) * vec[N - 1] + this->matrix(N, N) * vec[N];
        return rhs;
    }

    const TridiagMatrix<N + 1>& data() const {
        return matrix;
    }

    friend std::ostream& operator<<(std::ostream& os, const SystemMatrix<N>& m) {
        os << m.data();
        return os;
    }

    private:
    TridiagMatrix<N + 1> matrix;
};

#endif
