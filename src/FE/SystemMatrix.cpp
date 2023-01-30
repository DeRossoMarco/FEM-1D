#include "SystemMatrix.hpp"
#include "../Quadrature/Quadrature.hpp"
#include "../FEspace/BaseFunc.hpp"

std::vector<double>& SystemMatrix::operator[](const std::size_t &i) {
    return matrix.at(i);
}

std::vector<double> SystemMatrix::operator[](const std::size_t &i) const {
    return matrix.at(i);
}

const std::size_t SystemMatrix::size() const {
    return matrix.size();
}

void SystemMatrix::assemble(const Mesh &mesh,
                            const CFunction &c,
                            const DiffusionCoefficient &mi) {
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

void SystemMatrix::clear() {
    for (auto r : matrix) {
        for (auto e : r)
            e = 0.0;
    }
}
