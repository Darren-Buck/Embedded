# Use an official Ubuntu image
FROM ubuntu:22.04

# Install necessary packages (CMake and g++)
RUN apt-get update && apt-get install -y cmake gcc

# Set the working directory in the container
WORKDIR /app

# Copy the CMakeLists.txt and hello_world.c into the container
COPY CMakeLists.txt .
COPY hello_world.c .

# Create a build directory and run cmake to generate build files
RUN mkdir build && \
    cd build && \
    cmake ..

# Build the CMake project
RUN cmake --build build

# Set the entry point for the container
CMD ["./build/hello_world"]