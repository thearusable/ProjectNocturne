# Get ubuntu
FROM ubuntu:18.04

MAINTAINER Arkadiusz Szczepkowicz <arek.szczepkowicz@gmail.com>

# Config
ARG SDL2_VERSION=2.0.9
ARG CMAKE_VERSION=3.14.0

# Update apps on the base image
RUN apt-get -y update \
    && apt-get upgrade -y \
    && apt-get install wget git curl autoconf libtool m4 automake libssl-dev zlib1g-dev -y \
    && apt-get autoremove -y

# Install gcc
RUN apt-get install build-essential gcc-8 g++-8 -y \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-7 700 --slave /usr/bin/g++ g++ /usr/bin/g++-7 \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-8 800 --slave /usr/bin/g++ g++ /usr/bin/g++-8 \
    && apt-get autoremove -y

# Install opengl
RUN apt-get install freeglut3 freeglut3-dev libglew1.5 libglew1.5-dev libglu1-mesa libglu1-mesa-dev libgl1-mesa-glx libgl1-mesa-dev -y \
    && apt-get autoremove -y

# Build curl with https
RUN git clone https://github.com/bagder/curl.git && cd curl && ./buildconf && ./configure --with-ssl && make && make install \
    && cd .. && rm -rf curl

# Build SDL2
RUN wget https://www.libsdl.org/release/SDL2-${SDL2_VERSION}.tar.gz \
    && tar -xzf SDL2-${SDL2_VERSION}.tar.gz \
    && cd SDL2-${SDL2_VERSION} \
    && ./configure && make all && make install \
    && cd .. && rm -rf SDL2-${SDL2_VERSION} && rm SDL2-${SDL2_VERSION}.tar.gz

# Build cmake
RUN wget https://github.com/Kitware/CMake/releases/download/v${CMAKE_VERSION}/cmake-${CMAKE_VERSION}.tar.gz \
    && tar -xzf cmake-${CMAKE_VERSION}.tar.gz \
    && cd cmake-${CMAKE_VERSION} \
    && ./bootstrap --system-curl && make && make install \
    && cd .. && rm -rf cmake-${CMAKE_VERSION} && rm cmake-${CMAKE_VERSION}.tar.gz