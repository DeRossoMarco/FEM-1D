#ifndef TRIDIAG_MATRIX_HPP
#define TRIDIAG_MATRIX_HPP

#include <cstdlib>
#include <array>
#include <iostream>
#include <iomanip>

template<std::size_t N>
class TridiagMatrix {
    public:

    TridiagMatrix() {
        this->operator=(0.0);
    }

    double& operator()(const std::size_t& i, const std::size_t& j) {
        if (i == 0) {
            if (j == 0) return b[0];
            else if (j == 1) return c[0];
        } else if (i == N - 1) {
            if (j == N - 2) return a[N - 2];
            else if (j == N - 1) return b[N - 1];
        } else if (i > 0 && i < N) {
            if (j == i - 1) return a[i - 1];
            else if (j == i) return b[i];
            else if (j == i + 1) return c[i];
        }
        throw std::__throw_out_of_range;
    }

    double operator()(const std::size_t& i, const std::size_t& j) const {
        if (i == 0) {
            if (j == 0) return b[0];
            else if (j == 1) return c[0];
            else return 0.0;
        } else if (i == N - 1) {
            if (j == N - 2) return a[N - 2];
            else if (j == N - 1) return b[N - 1];
            else return 0.0;
        } else if (i > 0 && i < N) {
            if (j == i - 1) return a[i - 1];
            else if (j == i) return b[i];
            else if (j == i + 1) return c[i];
            else return 0.0;
        } else {
            throw std::__throw_out_of_range;
        }
    }

    void operator=(const double& d) {
        for (auto& x : a) {x = d;}
        for (auto& y : b) {y = d;}
        for (auto& z : c) {z = d;}
    }

    friend std::ostream& operator<<(std::ostream& os, const TridiagMatrix<N>& m) {
        for (auto i = 0; i < N; ++i) {
            for (auto j = 0; j < N; ++j) {
                os << std::setw(8) << std::setprecision(3) << m(i, j);
            }
            os << std::endl;
        }
        return os;
    }

    private:
    std::array<double, N - 1> a;
    std::array<double, N> b;
    std::array<double, N - 1> c;
};

#endif
