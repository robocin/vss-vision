#ifndef FILTERUTILS_H
#define FILTERUTILS_H

#include <iostream>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <opencv2/opencv.hpp>
#include <QFile>


namespace FilterUtils {
    void saveFilterRectToJson(const std::vector<cv::Rect>& rects, const QString& path);
    void loadFilterRectFromJson(std::vector<cv::Rect>& rects, const QString& path);
}

#endif /* FILTERUTILS_H */
