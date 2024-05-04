# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Name your project
project(morse_blink_led)

# Source files here
set(SRCS blink.c delay.c morse.c)

# Include directory for testing
include_directories(unity/src)

# Unity test files
set(TEST_FILES test.c unity/src/unity.c)

# Test executable
add_executable(test ${SRCS} ${TEST_FILES})

# For release builds
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message(STATUS "Configuring for Release build")

    add_executable(morse_blink_led main.c ${SRCS})
    target_compile_definitions(morse_blink_led PRIVATE RELEASE)
    target_compile_options(morse_blink_led PRIVATE -O3)

    target_compile_definitions(test PRIVATE RELEASE)
    target_compile_options(test PRIVATE -O3)
endif()

# For debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Configuring for Debug build")

    add_executable(morse_blink_led main.c ${SRCS})
    target_compile_definitions(morse_blink_led PRIVATE RELEASE)
    target_compile_options(morse_blink_led PRIVATE -g DEBUG)

    target_compile_definitions(test PRIVATE RELEASE)
    target_compile_options(test PRIVATE -g DEBUG)
endif()