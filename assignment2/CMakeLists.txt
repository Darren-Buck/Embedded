# Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# Define the project name and version
project(Arithmetic VERSION 1.0)

# Specify the C and C++ standards
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set variables for the library names
set(C_LIBRARY intarithmetic)
set(CPP_LIBRARY doublearithmetic)

# Add source files for the executable
add_executable(assignment2 main.c)

set(C_LIB_SOURCES
    int_arithmetic/add_int.c
    int_arithmetic/subtract_int.c
    int_arithmetic/multiply_int.c
    int_arithmetic/divide_int.c
)

set(CPP_LIB_SOURCES
    double_arithmetic/add_double.cpp
    double_arithmetic/subtract_double.cpp
    double_arithmetic/multiply_double.cpp
    double_arithmetic/divide_double.cpp
)

# Add a static library for C
add_library(${C_LIBRARY} STATIC ${C_LIB_SOURCES})

# Add a static library for C++
add_library(${CPP_LIBRARY} STATIC ${CPP_LIB_SOURCES})

# Link the executable with both C and C++ libraries
target_link_libraries(assignment2 ${C_LIBRARY} ${CPP_LIBRARY})