#include "CFunction.hpp"

double CFunction::value(const double &x) const {
    if (x >= 0.0 && x <= L)
        return c(x);
    else
        return 0.0;
}
