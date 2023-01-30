#ifndef DIFFUSION_COEFFICIENT_HPP
#define DIFFUSION_COEFFICIENT_HPP

#include <functional>

class DiffusionCoefficient {
    public:

    DiffusionCoefficient(const std::function<double(double)> &mi_,
              const double &L_) : 
        mi(mi_),
        L(L_)
    {}

    double value(const double &x) const;

    private:
    std::function<double(double)> mi;
    const double L;
};

#endif
