## Git RoboCIn - Very Small Size League Vision Software
---

#### Content of this repository:

> Implementation of Very Small Size League Vision Software

## Dependecies

```
Qt5
OpenCV
SFML
TBB
Protobuf
```
## Running with docker
1. Build the vss-vision image using the shell script
```shell
./docker_build
```

2. Running from the docker image using the shell script
```shell
./docker_run [camera device id]
```
The camera device id should be the id found on /dev/video{id} of the camera which you want to use on vss-vision, if none is given, the image will run without a camera device attached.
The configuration files are stored on a docker volume named vss-vision-config, so the config files should persist over docker runs
## Building (Ubuntu 22.04 LTS)

1. Install the needed dependencies.
```bash
./InstallDependencies
```

2. Build via CMake
```bash
# From repository root
mkdir build
cd build
cmake ..
make
```
3. Running:
```bash
# From repository root
cd src
./VSS-VISION
```

## Repository Tree

```bash
.
├── include
│   └── spdlog
└── src
    ├── Config
    │   └── Segmentation
    ├── Entity
    │   └── Entity.cpp
    ├── iconTools
    ├── Images
    ├── Log
    │   ├── general
    │   ├── others
    │   └── vision
    ├── main.cpp
    ├── mainwindow.cpp
    ├── qrc_icontools.cpp
    ├── qrc_image.cpp
    ├── Utils
    │   ├── Constants.cpp
    │   └── Utils.cpp
    ├── Vision
    │   ├── ColorSpace.cpp
    │   ├── ImageProcessing
    │   │   ├── Cuda
    │   │   │   └── LUT
    │   │   ├── ImageProcessing.cpp
    │   │   ├── LUTSegmentation.cpp
    │   │   ├── MaggicSegmentation.cpp
    │   │   ├── OpenCV
    │   │   │   └── connectedcomponents.cpp
    │   │   └── WarpCorrection.cpp
    │   ├── PositionProcessing
    │   │   ├── BlobDetection.cpp
    │   │   ├── PositionProcessing.cpp
    │   │   ├── runlengthencoding.cpp
    │   │   └── WhereAreThose.cpp
    │   └── Vision.cpp
```
- - - 

* Vision
	* Does all image processing
		* Segmentation
		* Tracking
		* Blob detection

---
* Vision (Opencv stuff, segmentation,tracking,blob detection algorithms)
	* Src->Vision

