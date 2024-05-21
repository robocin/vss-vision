cmake_minimum_required(VERSION 3.16)

project(VSS-VISION)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/src")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)
include(FindPackageHandleStandardArgs)
include(FetchContent)

FetchContent_Declare(
  pybind11
  URL https://github.com/pybind/pybind11/archive/refs/tags/v2.6.2.tar.gz
  URL_HASH SHA256=8ff2fff22df038f5cd02cea8af56622bc67f5b64534f1b83b9f133b8366acff2
)
FetchContent_MakeAvailable(pybind11)

set(python_module_name _vss_vision)

set(SOURCES
    src/main.cpp
    src/Utils/Utils.cpp
    src/Entity/Entity.cpp
    src/Utils/kalmanfilter.cpp
    src/Utils/matrix2d.cpp
    src/Vision/Vision.cpp
    src/Vision/PositionProcessing/PositionProcessing.cpp
    src/Vision/ImageProcessing/ImageProcessing.cpp
    src/Vision/ImageProcessing/LUTSegmentation.cpp
    src/Vision/ImageProcessing/MaggicSegmentation.cpp
    src/Vision/ImageProcessing/WarpCorrection.cpp
    src/Vision/ImageProcessing/OpenCV/connectedcomponents.cpp
    src/Vision/ColorSpace.cpp
    src/Vision/PositionProcessing/runlengthencoding.cpp
    src/Vision/PositionProcessing/BlobDetection.cpp
    src/Field/Field.cpp
    src/GameInfo/GameInfo.cpp
    src/Utils/Global.cpp
    src/Utils/Geometry.cpp
    src/Utils/Draw.cpp
    src/Utils/EnumsAndConstants.cpp
)

set(HEADERS
    src/Entity/Entity.h
    src/Utils/Utils.h
    src/Utils/kalmanfilter.h
    src/Utils/matrix2d.h
    src/Vision/Vision.h
    src/Vision/PositionProcessing/PositionProcessing.h
    src/Vision/ImageProcessing/ImageProcessing.h
    src/Vision/ImageProcessing/LUTSegmentation.h
    src/Vision/ImageProcessing/MaggicSegmentation.h
    src/Vision/ImageProcessing/WarpCorrection.h
    src/Vision/ColorSpace.h
    src/Vision/ImageProcessing/OpenCV/connectedcomponents.hpp
    src/Vision/PositionProcessing/runlengthencoding.h
    src/Vision/PositionProcessing/BlobDetection.h
    src/Utils/Types.h
    src/Field/Field.h
    src/Utils/EnumsAndConstants.h
    src/GameInfo/GameInfo.h
    src/Utils/Defines.h
    src/Utils/Global.h
    src/Utils/Geometry.h
    src/Utils/Draw.h
    src/Utils/BetterEnum.h
)

set(RESOURCES
    src/image.qrc
    src/iconTools/icontools.qrc
)

pybind11_add_module(${python_module_name} MODULE
  ${SOURCES}
  ${HEADERS}
)


# add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES} ${PROTO_SRCS} ${PROTO_HDRS})

target_include_directories(${python_module_name} PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(${python_module_name} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(${python_module_name} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

find_package(OpenCV REQUIRED)
target_link_libraries(${python_module_name} PUBLIC ${OpenCV_LIBS})

find_package(TBB REQUIRED)
target_link_libraries(${python_module_name} PUBLIC TBB::tbb)


