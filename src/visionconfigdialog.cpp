#include "visionconfigdialog.h"
#include "ui_visionconfigdialog.h"


VisionConfigDialog::VisionConfigDialog(bool videoFlag, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::VisionConfigDialog) {
  this->_vision = &this->_vision->singleton();
  ui->setupUi(this);
  this->_segmentationDialog = NULL;
  this->_trackDialog = NULL;
  this->_videoFlag = videoFlag;
  this->_fieldPixmap = QPixmap("Images/field.png");
  this->_fieldPixmap = this->_fieldPixmap.scaled(this->ui->projectionLabel->width(),
                                                 this->ui->projectionLabel->height(),
                                                 Qt::KeepAspectRatio,
                                                 Qt::SmoothTransformation);
  this->ui->projectionLabel->setPixmap(this->_fieldPixmap);
  this->_updateLabelsTimer = new QTimer(this);
  connect(this->_updateLabelsTimer, SIGNAL(timeout()), this, SLOT(updateLabels()));
  this->_updateLabelsTimer->start(30);
}

VisionConfigDialog::~VisionConfigDialog() {
  delete ui;
}

void VisionConfigDialog::on_calibrateTrackingPushButton_clicked() {
  if (this->getHasStarted()) {
    this->_trackDialog = new TrackConfigDialog();
    this->_trackDialog->exec();

    if (this->_trackDialog->result() == QDialog::Accepted) {
      this->_vision->savePositionParam();
    } else {
      this->_vision->setDetectionParamFromXml();
      this->_vision->setTrackParamFromXml();
    }

    delete this->_trackDialog;
  }
}

void VisionConfigDialog::on_calibrateSegmentationPushButton_clicked() {
  this->_segmentationDialog = new SegmentationConfigDialog(this->_videoFlag);
  this->_segmentationDialog->exec();

  if (this->_segmentationDialog->result() == QDialog::Accepted) {
  } else {
  }

  delete this->_segmentationDialog;
}

void VisionConfigDialog::updateLabels() {
  this->_robotPositions = Vision::singleton().getRobotPositions();
  QImage tmp(this->_fieldPixmap.toImage());
  QPainter painter(&tmp);
  painter.setRenderHint(QPainter::Antialiasing, true);
  QPen velocityPen(Qt::black, 3), robotSidePen(Qt::black);
  QPoint p1, p2;
  int colorIndex;
  double x, y, velx, vely, angle, robotWidth = 20;
  QColor allyColor, enemyColor, currentColor;

  if (Vision::singleton().getTeamColor() == BlueCOL) {
    allyColor = QColor((int)ColorSpace::markerColors[BlueCOL].red,
                       (int)ColorSpace::markerColors[BlueCOL].green,
                       (int)ColorSpace::markerColors[BlueCOL].blue);
    enemyColor = QColor((int)ColorSpace::markerColors[YellowCOL].red,
                        (int)ColorSpace::markerColors[YellowCOL].green,
                        (int)ColorSpace::markerColors[YellowCOL].blue);
  } else {
    allyColor = QColor((int)ColorSpace::markerColors[YellowCOL].red,
                       (int)ColorSpace::markerColors[YellowCOL].green,
                       (int)ColorSpace::markerColors[YellowCOL].blue);
    enemyColor = QColor((int)ColorSpace::markerColors[BlueCOL].red,
                        (int)ColorSpace::markerColors[BlueCOL].green,
                        (int)ColorSpace::markerColors[BlueCOL].blue);
  }

  for (int i = 0; i < this->_robotPositions.size(); i++) {
    if (this->_robotPositions[i].updated()) {
      x = this->_robotPositions[i].position().x;
      y = this->_robotPositions[i].position().y;
      //velx = this->_robotPositions[i].getObjectSpeed().x;
      //vely = this->_robotPositions[i].getObjectSpeed().y;
      angle = this->_robotPositions[i].angle();
      p1.setX(std::floor(x * 3));
      p1.setY(std::floor(390 - y * 3));
      p2.setX(p1.x() + velx);
      p2.setY(p1.y() - vely);
      colorIndex = this->_robotPositions[i].id();
      currentColor = QColor((int)ColorSpace::markerColors[colorIndex].red,
                            (int)ColorSpace::markerColors[colorIndex].green,
                            (int)ColorSpace::markerColors[colorIndex].blue);
      painter.setPen(robotSidePen);

      if (i == BALL) {
        painter.setBrush(currentColor);
        painter.drawEllipse(p1, 8, 8);
        painter.setPen(velocityPen);
        painter.drawLine(p1, p2);
      } else {
        painter.translate(p1);
        //calculating angle with 0 in the north
        angle = 90.0 - Geometry::radiansToDegrees(angle);

        if (angle < 0.001) {
          angle += 360.0;
        }

        painter.rotate(angle);
        painter.translate(-p1);
        painter.setBrush(QBrush(currentColor));
        painter.drawRect(p1.x() - robotWidth / 2, p1.y() - robotWidth / 2, robotWidth, robotWidth / 2);

        if (i <= ROBOT3) {
          painter.setBrush(QBrush(allyColor));
        } else {
          painter.setBrush(QBrush(enemyColor));
        }

        painter.drawRect(p1.x() - robotWidth / 2, p1.y(), robotWidth, robotWidth / 2);
        painter.resetTransform();
        painter.setPen(velocityPen);
        painter.drawLine(p1, p2);
      }
    }
  }

  this->ui->projectionLabel->setPixmap(QPixmap::fromImage(tmp));
}

void VisionConfigDialog::on_buttonBox_clicked() {
  this->_updateLabelsTimer->stop();
}

void VisionConfigDialog::setHasStarted(bool visionStarted) {
  this->_visionStarted = visionStarted;
}

bool VisionConfigDialog::getHasStarted() {
  return this->_visionStarted;
}
