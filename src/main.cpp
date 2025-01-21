#include <CameraManager/CameraThread.h>
#include <TBBThreadManager.h>
#include <visionthread.h>
#include <QApplication>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "Entity/Entity.h"
#include "Field/Field.h"
#include "Windows/MainVSSWindow.h"
#include "maggicsegmentationdialog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void load_env_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error while opening .env");
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        if (line[0] == '\0' || line[0] == '#') {
            continue;
        }

        char *key = strtok(line, "=");
        char *value = strtok(NULL, "=");

        if (key && value) {
            setenv(key, value, 1);
        }
    }

    fclose(file);

    const char *w = getenv("FRAME_WIDTH");
    const char *h = getenv("FRAME_HEIGHT");
    
    const std::string green = "\033[32m";
    const std::string red = "\033[31m";
    const std::string bold = "\033[1m";
    const std::string reset = "\033[0m";
    if (w && h) {
        std::cout << green << bold << "Camera Resolution set to " << w << "x" << h  << "!" << reset << std::endl;
    }else {
        std::cout << red << bold << "Camera Resolution was not set in .env file! Please verify it." << std::endl;
        exit(EXIT_FAILURE);
    }
}


int main(int argc, char *argv[]) {
  load_env_file(".env");

  TBBThreadManager Graph;

  cv::useOptimized();
  Logging::init();
  QApplication app(argc, argv);
  MainVSSWindow vsswindow;

  QObject::connect(&vsswindow, SIGNAL(startCameraUpdate()), &Graph,
                   SLOT(cameraStart()));
  QObject::connect(&vsswindow, SIGNAL(pauseCameraUpdate()), &Graph,
                   SLOT(cameraPause()));
  QObject::connect(&vsswindow, SIGNAL(enableVisionThread(bool)), &Graph,
                   SLOT(visionStart()));
  QObject::connect(&vsswindow, SIGNAL(finishVisionThread()), &Graph,
                   SLOT(visionPause()));

  vsswindow.showMaximized();
  return app.exec();
}
