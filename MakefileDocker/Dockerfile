FROM ubuntu:latest

# Install build essentials and other necessary packages
RUN apt-get update && apt-get install -y build-essential

# Set the working directory
WORKDIR /app

# Copy your C source code into the container
COPY hello_world.c /app/

# Compile the C program
RUN gcc -o hello_world hello_world.c

# Set the entry point for the container
CMD ["./hello_world"]
