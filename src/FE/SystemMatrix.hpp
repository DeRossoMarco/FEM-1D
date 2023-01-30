#ifndef SYSTEM_MATRIX_HPP
#define SYSTEM_MATRIX_HPP

#include "../FEspace/Mesh.hpp"

#include "../functions/CFunction.hpp"
#include "../functions/DiffusionCoefficient.hpp"

#include <vector>
#include <cstdlib>
#include <iterator>

class SystemMatrix{
    public:

    SystemMatrix(const std::size_t &N) {
        matrix.resize(N + 2);
        for (auto r : matrix)
            r.resize(N + 2);
        clear();
    }

    std::vector<double>& operator[](const std::size_t &i);

    std::vector<double> operator[](const std::size_t &i) const;

    const std::size_t size() const;

    void assemble(const Mesh &mesh,
                  const CFunction &c,
                  const DiffusionCoefficient &mi);

    void clear();

    private:
    std::vector<std::vector<double>> matrix;
};

#endif
