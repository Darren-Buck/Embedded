# This is the base image to use
# alternatively you could use ubuntu and apt update/install python3
FROM ubuntu:latest

# These python images by default are debian based so you can apt install things
# By default, the apt cache is removed so you have to run an update
# first. If you uncomment the lines below, this is a simple apt-get
# update and apt-get install for some packages that your container might need.
RUN apt-get update && \
    apt-get install -y pkg-config build-essential cmake && \  
    rm -rf /var/lib/apt/lists/*

# you can use alpine linux (even smaller base) by using one of the official tags
# FROM python:3.8-alpine3.18, however the apt install commands will be different
# as alpine uses a different package manager

# This copies all the files in the current directory
# to a folder, /app in this case
# Alternatively you can just copy your python file
# ex: COPY my_script.py /app/ vs using '.' which copies
# all files
COPY . app/

# This is the default work directory
# when you shell into the container
# This is the default location
WORKDIR /app

RUN mkdir build && cd build && cmake .. && make

# This cmd is run when you launch the container
CMD ["./build/assignment2"]