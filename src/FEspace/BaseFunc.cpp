#include "BaseFunc.hpp"

const std::function<double(double)> BaseFunc::func(
    const Mesh &mesh,
    const std::size_t &i) {
    return [&, mesh, i] (double x) -> double {
            if (x < mesh[i - 1] || x > mesh[i + 1])
                return 0.0;
            if (x < mesh[i])
                return mesh.get_h() / (mesh[i] - mesh[i - 1]) * (x - mesh[i - 1]);
            return mesh.get_h() / (mesh[i] - mesh[i + 1]) * (x - mesh[i + 1]);
        };
}

const std::function<double(double)> BaseFunc::d_func(
    const Mesh &mesh,
    const std::size_t &i) {
    return [&, mesh, i] (double x) -> double {
            if (x < mesh[i - 1] || x > mesh[i + 1])
                return 0.0;
            if (x < mesh[i])
                return 1.0;
            return -1.0;
        };
}
