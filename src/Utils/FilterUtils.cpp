#include "FilterUtils.h"

void FilterUtils::saveFilterRectToJson(const std::vector<cv::Rect>& rects, const QString& path) {
    QFile file(path);

    QJsonArray rectsArray;
    for (const auto& rect : rects) {
        QJsonObject rectObj;
        rectObj["x"] = rect.x;
        rectObj["y"] = rect.y;
        rectObj["width"] = rect.width;
        rectObj["height"] = rect.height;
        rectsArray.append(rectObj);
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QJsonDocument saveDoc(rectsArray);
        file.write(saveDoc.toJson(QJsonDocument::Indented));
        file.close();
    } else {
        qWarning() << "Could not open" << path << "for writing!";
    }
}

void FilterUtils::loadFilterRectFromJson(std::vector<cv::Rect>& rects, const QString& path) {
    rects.clear();
    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QByteArray data = file.readAll();
        QJsonDocument loadDoc(QJsonDocument::fromJson(data));
        QJsonArray rectsArray = loadDoc.array();

        for (const auto& value : rectsArray) {
            QJsonObject rectObj = value.toObject();
            cv::Rect rect(rectObj["x"].toInt(), rectObj["y"].toInt(), rectObj["width"].toInt(), rectObj["height"].toInt());
            rects.push_back(rect);
        }
        file.close();
    } else {
        qWarning() << "Não foi possível abrir" << path << "para leitura!";
    }
}