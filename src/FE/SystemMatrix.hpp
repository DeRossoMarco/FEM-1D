#ifndef SYSTEM_MATRIX_HPP
#define SYSTEM_MATRIX_HPP

#include "../FEspace/Mesh.hpp"
#include "../functions/CFunction.hpp"
#include "../functions/DiffusionCoefficient.hpp"
#include "../quadrature/Quadrature.hpp"
#include "../FEspace/BaseFunc.hpp"
#include "TridiagMatrix.hpp"

#include <array>
#include <cstdlib>
#include <iterator>
#include <iostream>
#include <iomanip>

template<std::size_t N>
class SystemMatrix{
    public:

    double& operator()(const std::size_t& i, const std::size_t& j) {
        return matrix(i, j);
    }

    double operator()(const std::size_t& i, const std::size_t& j) const {
        return matrix(i, j);
    }

    const std::size_t size() const {
        return N + 2;
    }

    void assemble(const Mesh &mesh,
                  const CFunction &c,
                  const DiffusionCoefficient &mi) {
        std::cout << std::endl << "Assembling system matrix" << std::endl;
        for (std::size_t k = 1; k < N; ++k) {
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

    void operator=(const double& d) {
        matrix = d;
    }

    const TridiagMatrix<N + 2>& data() const {
        return matrix;
    }

    friend std::ostream& operator<<(std::ostream& os, const SystemMatrix<N>& m) {
        os << m.data();
        return os;
    }

    private:
    TridiagMatrix<N + 2> matrix;
};

#endif
