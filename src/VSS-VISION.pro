#-------------------------------------------------
#
# Project created by QtCreator 2017-02-05T13:18:49
#
#-------------------------------------------------



QT     += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VSS-VISION
TEMPLATE = app

QMAKE_CXXFLAGS += -O3 -std=c++11
#QMAKE_EXT_MOC = .cu

##CUDA BEGIN

USE_CUDA = 0

equals(USE_CUDA,"1") {
  message(Using CUDA compiler)
  warning(This project may need nvcc compiler! Please verify "USE_CUDA" define.)
  CUDA_SOURCES = Vision/ImageProcessing/Cuda/LUT/lut_kernel.cu
  CUDA_COMPILER.output  = ${QMAKE_FILE_BASE}.o
  CUDA_COMPILER.commands = nvcc -c ${QMAKE_FILE_NAME} \
    -o ${QMAKE_FILE_OUT} \
     -Wno-deprecated-gpu-targets
  CUDA_COMPILER.input = CUDA_SOURCES
  QMAKE_EXTRA_COMPILERS += CUDA_COMPILER
} else {
  warning(This project may need nvcc compiler! Please verify "USE_CUDA" define.)
}
##CUDA END


# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000  # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
  Utils/Utils.cpp \
  Entity/Entity.cpp \
    Utils/kalmanfilter.cpp \
    Utils/matrix2d.cpp \
  Vision/Vision.cpp \
  Vision/PositionProcessing/PositionProcessing.cpp \
  Vision/ImageProcessing/ImageProcessing.cpp \
  Vision/ImageProcessing/LUTSegmentation.cpp \
  Vision/ImageProcessing/MaggicSegmentation.cpp \
  Vision/ImageProcessing/WarpCorrection.cpp \
  Vision/ImageProcessing/OpenCV/connectedcomponents.cpp \
  visionconfigdialog.cpp \
  fieldpointscalibratedialog.cpp \
  segmentationconfigdialog.cpp \
  cameraconfigurationdialog.cpp \
  Logging/logging.cpp \
  Vision/ColorSpace.cpp \
  maggicsegmentationdialog.cpp \
  Timer/Timer.cpp \
  visionthread.cpp \
  CameraManager/CameraManager.cpp \
  CameraManager/CameraThread.cpp \
  Vision/PositionProcessing/runlengthencoding.cpp \
  Vision/PositionProcessing/BlobDetection.cpp \
  TBBThreadManager.cpp \
    Field/Field.cpp \
    GameInfo/GameInfo.cpp \
    Utils/Global.cpp \
    Windows/MainVSSWindow.cpp \
    Utils/Geometry.cpp \
    Utils/Draw.cpp \
    Utils/EnumsAndConstants.cpp \
    Windows/RobotWidget.cpp \
    trackconfigdialog.cpp \
    Network/Network.cpp

HEADERS  += \
  Entity/Entity.h \
  Utils/Utils.h \
    Utils/kalmanfilter.h \
    Utils/matrix2d.h \
  Vision/Vision.h \
  Vision/PositionProcessing/PositionProcessing.h \
  Vision/ImageProcessing/ImageProcessing.h \
  Vision/ImageProcessing/LUTSegmentation.h \
  Vision/ImageProcessing/MaggicSegmentation.h \
  Vision/ImageProcessing/WarpCorrection.h \
  Vision/ColorSpace.h \
  Vision/ImageProcessing/OpenCV/connectedcomponents.hpp \
  visionconfigdialog.h \
  fieldpointscalibratedialog.h \
  segmentationconfigdialog.h \
  cameraconfigurationdialog.h \
  Logging/logging.h \
  maggicsegmentationdialog.h \
  Timer/Timer.h \
  visionthread.h \
  CameraManager/CameraManager.h \
  CameraManager/CameraThread.h \
  Vision/PositionProcessing/runlengthencoding.h \
  Vision/PositionProcessing/BlobDetection.h \
  TBBThreadManager.h \
  Utils/Types.h \
    Field/Field.h \
    Utils/EnumsAndConstants.h \
    GameInfo/GameInfo.h \
    Utils/Defines.h \
    Utils/Global.h \
    Windows/MainVSSWindow.h \
    Utils/Geometry.h \
    Utils/Draw.h \
    Windows/RobotWidget.h \
    Utils/BetterEnum.h \
    trackconfigdialog.h \
    Windows/FileConstants.h\
    Network/Network.h

FORMS  += \
  visionconfigdialog.ui \
  fieldpointscalibratedialog.ui \
  segmentationconfigdialog.ui \
  cameraconfigurationdialog.ui \
  maggicsegmentationdialog.ui \
    Windows/MainVSSWindow.ui \
    Windows/RobotWidget.ui \
    trackconfigdialog.ui

unix:!macx{

  INCLUDEPATH += ../include

    # Configuring project for OpenCV 3.x (Ubuntu 18.04 or less) and OpenCV 4.x (Ubuntu 20.04)
    OPENCV3 = pkg-config opencv --cflags --libs --silence-errors
    OPENCV4 = pkg-config opencv4 --cflags --libs --silence-errors

    OPENCV3_CMD = $$system($$OPENCV3)
    OPENCV3_STATUS = true
    equals(OPENCV3_CMD,"") {
      OPENCV3_STATUS = false
    }

    OPENCV4_CMD = $$system($$OPENCV4)
    OPENCV4_STATUS = true
    equals(OPENCV4_CMD,"") {
      OPENCV4_STATUS = false
    }

    message( OpenCV <= 3.x : $${OPENCV3_STATUS} )
    message( OpenCV == 4.x : $${OPENCV4_STATUS} )

    equals(OPENCV3_STATUS,"true") {
          LIBS += `$${OPENCV3}`
          INCLUDEPATH += /usr/local/include/opencv
          INCLUDEPATH += /usr/local/include/opencv2
          message(Using OpenCV 3.x or less)
    } else {
      equals(OPENCV4_STATUS,"true") {
        LIBS += `$${OPENCV4}`
        INCLUDEPATH += /usr/include/opencv4
        message(Using OpenCV 4.x)
      } else {
          error(No viable OpenCV for project. Sorry.)
      }
    }

  equals(USE_CUDA,"1") {
    LIBS += -L/usr/local/cuda/lib64
    LIBS += -lcudart
  }
  LIBS += -ltbb
  LIBS += -lsfml-system -lsfml-network

}

macx{
  PKG_CONFIG = /usr/local/bin/pkg-config
  QT_CONFIG -= no-pkg-config
  CONFIG  += link_pkgconfig
  PKGCONFIG += opencv
  INCLUDEPATH += /usr/local/include/
  INCLUDEPATH += ../include

  LIBS += $(pkg-config opencv --cflags --libs)
  equals(USE_CUDA,"1") {
    LIBS += -L/usr/local/cuda/lib64
    LIBS += -lcudart
  }
  LIBS += -ltbb
  LIBS += -lsfml-system -lsfml-network
}

RESOURCES += \
  image.qrc \
  iconTools/icontools.qrc

DISTFILES += \
    Utils/Comments.txt
