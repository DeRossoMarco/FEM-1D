cmake_minimum_required(VERSION 3.12.0)
project(2FEM-1D LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED "ON")
set(CMAKE_CXX_FLAGS "${OpenMP_CXX_FLAGS} -pthread -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-conversion -Wmissing-braces -Wnon-virtual-dtor")

# Set default build type to Release.
if(NOT CMAKE_BUILD_TYPE OR "${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-DBUILD_TYPE_DEBUG)
endif()
message(STATUS)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS)

add_executable(FEM-1D   src/FEM-1D.cpp
                        src/functions/ForcingTerm.cpp
                        src/functions/CFunction.cpp
                        src/functions/DiffusionCoefficient.cpp
                        src/FEspace/Mesh.cpp
                        src/Quadrature/Quadrature.cpp)

# Locate OpenMP compiler.
option (USE_OpenMP "Use OpenMP" ON)
if(USE_OpenMP)
    find_library(LIBOMP OpenMP omp omp5 HINTS "~/usr/local/Cellar/libomp/15.0.7/lib")
    find_package(OpenMP)
    if(OPENMP_FOUND)
        set(CMAKE_CXX_FLAGS "${OpenMP_CXX_FLAGS}")
        target_link_libraries(FEM-1D PUBLIC OpenMP::OpenMP_CXX)
        endif()
endif()
