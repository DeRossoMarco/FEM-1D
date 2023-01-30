#ifndef FORCING_TERM_HPP
#define FORCING_TERM_HPP

#include <functional>

class ForcingTerm {
    public:

    ForcingTerm(const std::function<double(double, double)> &f_,
                const double &L_,
                const double &T_) : 
        f(f_),
        L(L_),
        T(T_)
    {}

    double value(const double &x, const double &t) const;

    private:
    std::function<double(double, double)> f;
    const double L;
    const double T;
};

#endif
