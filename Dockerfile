FROM ubuntu:22.04

RUN apt-get update && export DEBIAN_FRONTEND=noninteractive \
    && apt-get -y install --no-install-recommends \
    build-essential \
    pkg-config \
    zip \
    unzip \
    v4l-utils \
    libsfml-dev \
    libopencv-dev \
    freeglut3-dev \
    libprotobuf-dev \ 
    cmake \
    python3 \
    libpython3-dev \
    python3-dev \
    python3-pip \

RUN cd /usr/local/src \
    && wget https://github.com/pybind/pybind11/archive/refs/tags/v2.12.0.tar.gz \
    && tar xvf v2.12.0.tar.gz \
    && cd pybind11-2.12.0 \
    && mkdir build \
    && cd build \
    && cmake .. \
    && make \
    && make install

COPY . /opt/vss-vision

WORKDIR /opt/vss-vision/build

RUN cmake clean .. -Wno-dev && make -j4

WORKDIR /opt/vss-vision/src

CMD ["./VSS-VISION"]