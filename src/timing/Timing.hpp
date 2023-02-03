#ifndef TIMING_HPP
#define TIMING_HPP

#include <omp.h>
#include <fstream>
#include <iostream>
#include <cstring>

class Timing {
    public:

    Timing() : num_thread(omp_get_num_threads()) {}

    void start() {
        start_t = omp_get_wtime();
    }

    void end() {
        end_t = omp_get_wtime();
    }

    void print_report() {
        // Print report on std out
        std::cout << "TIMING REPORT" << std::endl << std::endl;
        std::cout << "  Num of threads used for simulation: " << num_thread << std::endl;
        std::cout << "  Total elapsed time:                 " << std::to_string(end_t - start_t) << std::endl;

        std::ofstream output;
        output.open("timing_report.txt", std::ios_base::out);
        if (!output.is_open()) {
            std::cout << "Error! Cannot open timing report file." << std::endl;
            return;
        }
        if (output.eof()) {
            output << "num_thread , elapsed_time" << std::endl;
        }
        output.seekp(std::ios_base::end);
        output << num_thread << " , " << std::to_string(end_t - start_t) << std::endl;
        output.close();
    }

    private:
    double start_t;
    double end_t;
    const std::size_t num_thread;
};

#endif 
