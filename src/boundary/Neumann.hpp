#ifndef NEUMANN_HPP
#define NEUMANN_HPP

#include <functional>
#include <cstdlib>

class Neumann {
    public:

    Neumann(const double& L_,
            const std::function<double(double)>& q_1_,
            const std::function<double(double)>& q_2_) :
        L(L_),
        q_1(q_1_),
        q_2(q_2_)
    {}

    double operator()(const double& x, const double& t) const {
        if (x == 0.0) return q_1(t);
        else if (x == L) return q_2(t);
        else return 0.0;
    }

    private:
    const double L;
    const std::function<double(double)> q_1;
    const std::function<double(double)> q_2;
};

#endif
