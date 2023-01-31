#include "ForcingTerm.hpp"

double ForcingTerm::operator()(const double &x, const double &t) const {
    if (x > 0.0 && x < L && t >= 0.0 && t <= T)
        return f(x, t);
    else
        return 0.0;
}
