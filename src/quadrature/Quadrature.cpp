#include "Quadrature.hpp"

double Quadrature::two_point_quadrature(const std::function<double(double)> &f,
                                        const double &a,
                                        const double &b) {
    return (b - a) / 2 * (w_1 * f((b - a) / 2 * x_1 + (a + b) / 2) +
                          w_2 * f((b - a) / 2 * x_2 + (a + b) / 2));
}
