#include "DiffusionCoefficient.hpp"

double DiffusionCoefficient::value(const double &x) const {
    if (x > 0.0 && x < L)
        return mi(x);
    else
        return 0.0;
}
