#ifndef MESH_HPP
#define MESH_HPP

#include <cstdlib>

class Mesh {
    public:

    Mesh(const double &L_, const std::size_t &N_) :
        L(L_),
        N(N_),
        h(L / (N))
    {}

    double operator[](const std::size_t &i) const;

    std::size_t get_size() const;

    double get_h() const;

    private:
    const double L;
    std::size_t N;
    const double h;
};

#endif
