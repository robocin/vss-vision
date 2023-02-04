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
    freeglut3-dev \
    protobuf-compiler \
    libprotobuf-dev \ 
    cmake

COPY . /opt/vss-vision

RUN cd /opt/vss-vision/src/Network/pb && protoc --cpp_out=.. *.proto

WORKDIR /opt/vss-vision/build

RUN cmake clean .. && make -j4

WORKDIR /opt/vss-vision/src

CMD ["./VSS-VISION"]