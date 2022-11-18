FROM ubuntu:20.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    qt5-default \
    build-essential \
    pkg-config \
    zip \
    unzip \
    v4l-utils \
    libsfml-dev \
    libopencv-dev \
    freeglut3-dev

WORKDIR /workspaces/vss-vision

COPY . .

RUN cd src && qmake && make clean && make -j8
