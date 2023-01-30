#ifndef SYSTEM_SOL_HPP
#define SYSTEM_SOL_HPP

#include <cstdlib>
#include <vector>

class SystemSol {
    public:

    SystemSol(const std::size_t &N) {
        sol.resize(N + 2);
        clear();
    }

    double& operator[](const std::size_t &i);

    double operator[](const std::size_t &i) const;

    void clear();

    private:
    std::vector<double> sol;
};

#endif
