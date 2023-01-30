#ifndef C_FUNCTION_HPP
#define C_FUNCTION_HPP

#include <functional>

class CFunction {
    public:

    CFunction(const std::function<double(double)> &c_,
              const double &L_) : 
        c(c_),
        L(L_)
    {}

    double value(const double &x) const;

    private:
    std::function<double(double)> c;
    const double L;
};

#endif
