#include "visionconfigdialog.h"
#include "ui_visionconfigdialog.h"

VisionConfigDialog::VisionConfigDialog(bool videoFlag, QWidget *parent) :
  QDialog(parent),
  ui(new Ui::VisionConfigDialog) {
  this->_vision = &this->_vision->singleton();
  ui->setupUi(this);
  this->_segmentationDialog = nullptr;
  this->_trackDialog = nullptr;
  this->_videoFlag = videoFlag;
  this->_fieldPixmap = QPixmap("Images/field.png");
  if (this->_fieldPixmap.isNull()) {
    std::cerr << "erro ao abrir o arquivo Images/field.png" << std::endl;
    return;
  }
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
//  this->_segmentationDialog = new SegmentationConfigDialog(this->_videoFlag);
//  this->_segmentationDialog->exec();

//  if (this->_segmentationDialog->result() == QDialog::Accepted) {
//  } else {
//  }

//  delete this->_segmentationDialog;
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
    allyColor = QColor(static_cast<int>(ColorSpace::markerColors[BlueCOL].red),
                       static_cast<int>(ColorSpace::markerColors[BlueCOL].green),
                       static_cast<int>(ColorSpace::markerColors[BlueCOL].blue));
    enemyColor = QColor(static_cast<int>(ColorSpace::markerColors[YellowCOL].red),
                        static_cast<int>(ColorSpace::markerColors[YellowCOL].green),
                        static_cast<int>(ColorSpace::markerColors[YellowCOL].blue));
  } else {
    allyColor = QColor(static_cast<int>(ColorSpace::markerColors[YellowCOL].red),
                       static_cast<int>(ColorSpace::markerColors[YellowCOL].green),
                       static_cast<int>(ColorSpace::markerColors[YellowCOL].blue));
    enemyColor = QColor(static_cast<int>(ColorSpace::markerColors[BlueCOL].red),
                        static_cast<int>(ColorSpace::markerColors[BlueCOL].green),
                        static_cast<int>(ColorSpace::markerColors[BlueCOL].blue));
  }

  for (Entities::size_type i = 0; i < this->_robotPositions.size(); i++) {
    if (this->_robotPositions[i].updated()) {
      x = this->_robotPositions[i].position().x;
      y = this->_robotPositions[i].position().y;
      //velx = this->_robotPositions[i].getObjectSpeed().x;
      //vely = this->_robotPositions[i].getObjectSpeed().y;
      velx = vely = 0;
      angle = this->_robotPositions[i].angle();
      p1.setX(static_cast<int>(std::floor(x * 3)));
      p1.setY(static_cast<int>(std::floor(390 - y * 3)));
      p2.setX(static_cast<int>(p1.x() + velx));
      p2.setY(static_cast<int>(p1.y() - vely));
      colorIndex = static_cast<int>(this->_robotPositions[i].id());
      currentColor = QColor(static_cast<int>(ColorSpace::markerColors[colorIndex].red),
                            static_cast<int>(ColorSpace::markerColors[colorIndex].green),
                            static_cast<int>(ColorSpace::markerColors[colorIndex].blue));
      painter.setPen(robotSidePen);

      if (this->_robotPositions[i].id() == 0) { // ball
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
        painter.drawRect(static_cast<int>(p1.x() - robotWidth / 2),
                         static_cast<int>(p1.y() - robotWidth / 2),
                         static_cast<int>(robotWidth),
                         static_cast<int>(robotWidth / 2));

        if (this->_robotPositions[i].id()/100 == 1) {
          painter.setBrush(QBrush(allyColor));
        } else {
          painter.setBrush(QBrush(enemyColor));
        }

        painter.drawRect(static_cast<int>(p1.x() - robotWidth / 2),
                         static_cast<int>(p1.y()),
                         static_cast<int>(robotWidth),
                         static_cast<int>(robotWidth / 2));
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
