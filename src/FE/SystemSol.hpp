#ifndef SYSTEM_SOL_HPP
#define SYSTEM_SOL_HPP

#include <cstdlib>
#include <array>
#include <iostream>

template<std::size_t N>
class SystemSol {
    public:

    SystemSol() : sol() {}

    double& operator[](const std::size_t &i) {
        return sol[i];
    }

    double operator[](const std::size_t &i) const {
        return sol[i];
    }

    void clear() {
        for (auto e : sol) {
            e = 0.0;
        }
    }

    void display() const {
        for (std::size_t i = 0; i < sol.size(); ++i) {
            std::cout << "u_" << i << " = " << sol[i] << std::endl;
        }
    }

    private:
    std::array<double, N> sol;
};

#endif
