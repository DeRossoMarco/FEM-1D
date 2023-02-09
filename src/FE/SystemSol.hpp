#ifndef SYSTEM_SOL_HPP
#define SYSTEM_SOL_HPP

#include <cstdlib>
#include <array>
#include <iostream>
#include <iomanip>
#include <cfloat>

template<std::size_t N>
class SystemSol {
    public:

    SystemSol() {
        this->operator=(0.0);
    }

    double& operator[](const std::size_t &i) {
        return sol[i];
    }

    double operator[](const std::size_t &i) const {
        return sol[i];
    }

    void operator=(const double& i) {
        for (auto& e : sol) {
            e = i;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const SystemSol& sol) {
        for (std::size_t i = 0; i < N; ++i) {
            os << std::scientific << std::setprecision(20) << sol[i] << ",";
        }
        os << std::scientific << std::setprecision(std::numeric_limits<decltype(sol[N])>::max_digits10)
           << sol[N] << std::endl;
        return os;
    }

    private:
    std::array<double, N + 1> sol;
};

#endif
