#ifndef BASE_FUNC_HPP
#define BASE_FUNC_HPP

#include <functional>
#include "Mesh.hpp"

class BaseFunc {
    public:
    
    static const std::function<double(double)> func(
        const Mesh &mesh,
        const std::size_t &i);

    static const std::function<double(double)> d_func(
        const Mesh &mesh,
        const std::size_t &i);

    private:
};

#endif
