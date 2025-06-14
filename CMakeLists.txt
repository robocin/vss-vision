cmake_minimum_required(VERSION 3.16)

project(VSS-VISION)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH "${PROJECT_SOURCE_DIR}/src")

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
    src/visionconfigdialog.cpp
    src/fieldpointscalibratedialog.cpp
    src/segmentationconfigdialog.cpp
    src/cameraconfigurationdialog.cpp
    src/Logging/logging.cpp
    src/Vision/ColorSpace.cpp
    src/maggicsegmentationdialog.cpp
    src/Timer/Timer.cpp
    src/visionthread.cpp
    src/CameraManager/CameraManager.cpp
    src/CameraManager/CameraThread.cpp
    src/Vision/PositionProcessing/runlengthencoding.cpp
    src/Vision/PositionProcessing/BlobDetection.cpp
    src/TBBThreadManager.cpp
    src/Field/Field.cpp
    src/GameInfo/GameInfo.cpp
    src/Utils/Global.cpp
    src/Windows/MainVSSWindow.cpp
    src/Utils/Geometry.cpp
    src/Utils/Draw.cpp
    src/Utils/EnumsAndConstants.cpp
    src/Windows/RobotWidget.cpp
    src/trackconfigdialog.cpp
    src/Network/Network.cpp
    src/Network/visionServer/server.cpp
    src/Utils/FilterUtils.cpp
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
    src/visionconfigdialog.h
    src/fieldpointscalibratedialog.h
    src/segmentationconfigdialog.h
    src/cameraconfigurationdialog.h
    src/Logging/logging.h
    src/maggicsegmentationdialog.h
    src/Timer/Timer.h
    src/visionthread.h
    src/CameraManager/CameraManager.h
    src/CameraManager/CameraThread.h
    src/Vision/PositionProcessing/runlengthencoding.h
    src/Vision/PositionProcessing/BlobDetection.h
    src/TBBThreadManager.h
    src/Utils/Types.h
    src/Field/Field.h
    src/Utils/EnumsAndConstants.h
    src/GameInfo/GameInfo.h
    src/Utils/Defines.h
    src/Utils/Global.h
    src/Windows/MainVSSWindow.h
    src/Utils/Geometry.h
    src/Utils/Draw.h
    src/Windows/RobotWidget.h
    src/Utils/BetterEnum.h
    src/trackconfigdialog.h
    src/Windows/FileConstants.h
    src/Network/Network.h
    src/Network/visionServer/server.h
    src/Utils/FilterUtils.h
)

set(RESOURCES
    src/image.qrc
    src/iconTools/icontools.qrc
)

set(PROTOS
    src/Network/protobuf/proto/messages_robocup_ssl_detection.proto
    src/Network/protobuf/proto/messages_robocup_ssl_geometry.proto
    src/Network/protobuf/proto/wrapper.proto
)

find_package(Protobuf REQUIRED)
protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTOS})

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${RESOURCES} ${PROTO_SRCS} ${PROTO_HDRS})

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/src")
target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Network)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Network)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

find_package(OpenCV REQUIRED)
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

find_package(TBB REQUIRED)
target_link_libraries(${PROJECT_NAME} TBB::tbb)

find_package(SFML REQUIRED COMPONENTS network system)
target_link_libraries(${PROJECT_NAME} sfml-network sfml-system)

target_link_libraries(${PROJECT_NAME} ${Protobuf_LIBRARIES})