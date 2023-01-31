#ifndef SYSTEM_SOL_HPP
#define SYSTEM_SOL_HPP

#include <cstdlib>
#include <array>
#include <iostream>
#include <iomanip>

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
        for (auto i = 0; i < N + 2; ++i) {
            os << "u_" << std::setw(2) << std::setfill('0') << i << " = ";
            os << std::setfill(' ') << std::setw(10) << std::setprecision(3) << sol[i] << std::endl;
        }
        return os;
    }

    private:
    std::array<double, N + 2> sol;
};

#endif
