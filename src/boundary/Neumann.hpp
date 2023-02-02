#ifndef NEUMANN_HPP
#define NEUMANN_HPP

#include "../FE/SystemMatrix.hpp"
#include "../FE/SystemRhS.hpp"

#include <functional>

template<std::size_t N>
class Neumann {
    public:

    Neumann(const std::function<double(double)>& q_1_,
            const std::function<double(double)>& q_2_) :
        q_1(q_1_),
        q_2(q_2_)
    {}

    void apply_q1(SystemRhS<N>& rhs, const double& t) {
        rhs[0] += q_1(t);
    }

    void apply_q2(SystemRhS<N>& rhs, const double& t) {
        rhs[N] += q_2(t);
    }

    private:
    
    const std::function<double(double)> q_1;
    const std::function<double(double)> q_2;
};

#endif
