#ifndef DIRICHLET_HPP
#define DIRICHLET_HPP

#include "../FE/SystemMatrix.hpp"
#include "../FE/SystemRhS.hpp"

#include <functional>

template<std::size_t N>
class Dirichlet {
    public:

    Dirichlet(const std::function<double(double)>& g_1_,
              const std::function<double(double)>& g_2_) :
        g_1(g_1_),
        g_2(g_2_)
    {}

    void apply(SystemMatrix<N>& matrix, SystemRhS<N>& rhs, const double& t) {
        matrix(0, 0) = 1;
        matrix(N + 1, N + 1) = 1;
        rhs[0] = g_1(t);
        rhs[N + 1] = g_2(t);
    }

    private:
    std::function<double(double)> g_1;
    std::function<double(double)> g_2;
 };

#endif
