FROM ubuntu:22.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    qtbase5-dev \
    build-essential \
    pkg-config \
    zip \
    unzip \
    v4l-utils \
    libsfml-dev \
    libopencv-dev \
    freeglut3-dev \
    protobuf-compiler \
    libprotobuf-dev \ 
    cmake

COPY . /opt/vss-vision

WORKDIR /opt/vss-vision/build

RUN cmake clean .. -Wno-dev && make -j4

WORKDIR /opt/vss-vision/src

CMD ["./VSS-VISION"]