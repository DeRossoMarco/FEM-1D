cmake_minimum_required(VERSION 3.12.0)
project(FEM-1D LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED "ON")

# Set default build type to Release.
if(NOT CMAKE_BUILD_TYPE OR "${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()
message(STATUS)
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS)
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
    add_definitions(-DBUILD_TYPE_DEBUG)
endif()

# Locate OpenMP compiler.
option (USE_OpenMP "Use OpenMP" ON)
if(USE_OpenMP)
    find_package(OpenMP)
    if(OPENMP_FOUND)
        separate_arguments(CMAKE_C_FLAGS UNIX_COMMAND "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        endif()
endif()

# Add useful compiler flags.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wfloat-conversion -Wmissing-braces -Wnon-virtual-dtor")

add_executable(FEM-1D   src/FEM-1D.cpp
                        src/functions/ForcingTerm.cpp
                        src/functions/CFunction.cpp
                        src/functions/DiffusionCoefficient.cpp
                        src/FEspace/Mesh.cpp
                        src/FEspace/BaseFunc.cpp
                        src/FE/SystemMatrix.cpp
                        src/FE/SystemRhS.cpp
                        src/FE/SystemSol.cpp
                        src/FE/Solver.cpp
                        src/Quadrature/Quadrature.cpp)
