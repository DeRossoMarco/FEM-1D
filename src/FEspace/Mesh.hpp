#ifndef MESH_HPP
#define MESH_HPP

#include <cstdlib>

class Mesh {
    public:

    Mesh(const double &L_, const unsigned int &N_) :
        L(L_),
        N(N_),
        h(L / (N + 1))
    {}

    double operator[](const std::size_t &i) const;

    unsigned int get_size() const;

    unsigned int get_h() const;

    private:
    const double L;
    const unsigned int N;
    const double h;
};

#endif
