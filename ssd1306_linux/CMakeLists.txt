# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Name your project
project(ssd1306)

# Main executable
# ssd1306_bin is the binary name
# main.c is the primary source file
add_executable(ssd1306_bin main.c)

# SSD1306 static library
# ssd1306 is the library name
# STATIC creates static library (libssd1306.a)
# ssd1306.c is the library source file
# linux_i2c.c is the interface code for i2c
add_library(ssd1306 STATIC ssd1306.c linux_i2c.c)

# SSD1306 shared library
# ssd1306s is the library name
# STATIC creates static library (libssd1306_shared.so)
# ssd1306.c is the library source file
# linux_i2c.c is the interface code for i2c
add_library(ssd1306_shared SHARED ssd1306.c linux_i2c.c)

# Link the static library
target_link_libraries(ssd1306_bin ssd1306)

# Link the shared library
# If you wanted to use the shared library, then use this instead
# remember you'll have to copy the libssd1306_shared.so to /usr/lib on the duo
# target_link_libraries(ssd1306_bin ssd1306_shared)
