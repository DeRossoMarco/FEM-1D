#include "Mesh.hpp"

#include <cstdlib>
#include <array>

double Mesh::operator[](const std::size_t &i) const {
    if (i >= 0 && i <= N + 1) return h * i;
    else throw std::__throw_out_of_range;
}

unsigned int Mesh::get_size() const {
    return N;
}

double Mesh::get_h() const {
    return h;
}
