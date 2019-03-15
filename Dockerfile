# STAGE 1 - get ubuntu
FROM ubuntu:18.04

# Update apps on the base image
RUN apt-get -y update \
    && apt-get upgrade -y \
    && apt-get install wget git cppcheck -y \
    && apt-get autoremove -y

# Install gcc
RUN apt-get install build-essential gcc-8 g++-8 -y \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 700 --slave /usr/bin/g++ g++ /usr/bin/g++-7 \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 800 --slave /usr/bin/g++ g++ /usr/bin/g++-8 \
    && apt-get autoremove -y 

# Install opengl
RUN apt-get install freeglut3 freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx \
    libgl1-mesa-dev -y && apt-get autoremove -y

# Install SDL2
RUN apt-get install libsdl2-dev -y && apt-get autoremove -y

# build latest cmake
RUN wget https://github.com/Kitware/CMake/releases/download/v3.14.0/cmake-3.14.0.tar.gz \
    && tar -xzf cmake-3.14.0.tar.gz \
    && cd cmake-3.14.0 \
    && ./configure && make && make install && cd .. && rm -rf cmake-3.14.0 