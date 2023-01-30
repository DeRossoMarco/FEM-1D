#ifndef QUADRATURE_HPP
#define QUADRATURE_HPP

#include <functional>
#include <cmath>

class Quadrature {
    public:

    static double two_point_quadrature(const std::function<double(double)> &f,
                                       const double &a,
                                       const double &b);

    private:
    static constexpr double x_1 = - 0.577350269189625764509148780501;
    static constexpr double x_2 = 0.577350269189625764509148780501;
    static constexpr double w_1 = 1;
    static constexpr double w_2 = 1;
};

#endif
