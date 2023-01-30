#ifndef SYSTEM_MATRIX_HPP
#define SYSTEM_MATRIX_HPP

#include "../FEspace/Mesh.hpp"
#include "../functions/CFunction.hpp"
#include "../functions/DiffusionCoefficient.hpp"
#include "../Quadrature/Quadrature.hpp"
#include "../FEspace/BaseFunc.hpp"

#include <array>
#include <cstdlib>
#include <iterator>
#include <iostream>

template<std::size_t N>
class SystemMatrix{
    public:

    SystemMatrix() : matrix() {}

    std::array<double, N>& operator[](const std::size_t &i) {
        return matrix.at(i);
    }

    std::array<double, N> operator[](const std::size_t &i) const {
    return matrix.at(i);
    }

    const std::size_t size() const {
        return N;
    }
    void assemble(const Mesh &mesh,
                  const CFunction &c,
                  const DiffusionCoefficient &mi) {
        std::cout << "Assembling system matrix" << std::endl;
        for (std::size_t k = 1; k < mesh.get_size(); ++k) {
            for (std::size_t i = k; i < k + 2; ++i) {
                for (std::size_t j = k; j < k + 2; ++j) {
                    matrix[i][j] +=
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

    void clear() {
        for (auto r : matrix) {
            for (auto e : r)
                e = 0.0;
        }
    }

    private:
    std::array<std::array<double, N>, N> matrix;
};

#endif
