#ifndef BASE_FUNC_HPP
#define BASE_FUNC_HPP

#include <functional>
#include "Mesh.hpp"

namespace BaseFunc {
    static const std::function<double(double)> func(
        const Mesh &mesh,
        const std::size_t &i) {
        return [&] (double x) -> double {
                if (x < mesh[i - 1] || x > mesh[i + 1])
                    return 0.0;
                if (x < mesh[i])
                    return x - mesh[i - 1];
                return -x + mesh[i + 1];
            };
    }
    static const std::function<double(double)> d_func(
        const Mesh &mesh,
        const std::size_t &i) {
        return [&] (double x) -> double {
                if (x < mesh[i - 1] || x > mesh[i + 1])
                    return 0.0;
                if (x < mesh[i])
                    return 1.0;
                return -1.0;
            };
    }
};

#endif
