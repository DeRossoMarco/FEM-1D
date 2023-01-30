#include "SystemSol.hpp"

double& SystemSol::operator[](const std::size_t &i) {
    return sol[i];
}

double SystemSol::operator[](const std::size_t &i) const {
    return sol[i];
}

void SystemSol::clear() {
    for (auto e : sol) {
        e = 0.0;
    }
}
