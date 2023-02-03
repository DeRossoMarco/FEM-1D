#ifndef TIMING_HPP
#define TIMING_HPP

#include <omp.h>
#include <fstream>
#include <iostream>
#include <cstring>

class Timing {
    public:

    Timing(const std::size_t& num_threads_) : num_threads(num_threads_) {}

    void start() {
        start_t = omp_get_wtime();
    }

    void stop() {
        end_t = omp_get_wtime();
    }

    void print_report() {
        // Print report on std out
        std::cout << "TIMING REPORT" << std::endl;
        std::cout << "  Num of threads used for simulation: " << num_threads << std::endl;
        std::cout << "  Total elapsed time:                 " << std::to_string(end_t - start_t) << " s" << std::endl;

        std::ofstream output;
        output.open("timing_report.txt", std::ios_base::app);
        if (!output.is_open()) {
            std::cout << "Error! Cannot open timing report file." << std::endl;
            return;
        }
        output << num_threads << " , " << std::to_string(end_t - start_t) << std::endl;
        output.close();
    }

    private:
    double start_t;
    double end_t;
    const std::size_t num_threads;
};

#endif 
