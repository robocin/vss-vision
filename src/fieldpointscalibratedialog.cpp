#include "fieldpointscalibratedialog.h"
#include "ui_fieldpointscalibratedialog.h"

FieldPointsCalibrateDialog::FieldPointsCalibrateDialog(const bool videoFlag,
                                                       QWidget *parent)
    : QDialog(parent), ui(new Ui::FieldPointsCalibrateDialog) {
  this->_videoFlag = videoFlag;
  ui->setupUi(this);
  this->_updateFrameTimer = new QTimer(this);
  if (this->_videoFlag) {
    this->_updateFrameTimer->start(30);
  } else {
    this->_updateFrameTimer->start(30);
  }
  connect(this->_updateFrameTimer, SIGNAL(timeout()), this,
          SLOT(updateFrame()));
}

void FieldPointsCalibrateDialog::showEvent(QShowEvent *event) {
  QDialog::showEvent(event);

  this->_selectedPointIndex = 0;
  this->setMouseTracking(true);
  this->setFocus();
  this->getPointsFromFile(FIELDLIMITSPATH);
  if (this->_videoFlag) {
    this->_updateFrameTimer->start(30);
  } else {
    this->_updateFrameTimer->start(30);
  }
}

FieldPointsCalibrateDialog::~FieldPointsCalibrateDialog() {
  this->_updateFrameTimer->stop();
  delete this->_updateFrameTimer;
  delete ui;
}

void FieldPointsCalibrateDialog::keyPressEvent(QKeyEvent *e) {
  switch (e->key()) {
    case Qt::Key_Escape:
      this->_updateFrameTimer->stop();
      QDialog::reject();
      break;
    case Qt::Key_1:
      _selectedPointIndex = 0;
      break;
    case Qt::Key_2:
      _selectedPointIndex = 1;
      break;
    case Qt::Key_3:
      _selectedPointIndex = 2;
      break;
    case Qt::Key_4:
      _selectedPointIndex = 3;
      break;
    case Qt::Key_W:
      if (_limitPoints[_selectedPointIndex].y > 0) {
        _limitPoints[_selectedPointIndex].y--;
      }
      break;
    case Qt::Key_S:
      if (_limitPoints[_selectedPointIndex].y < _cameraFrame.rows) {
        _limitPoints[_selectedPointIndex].y++;
      }
      break;
    case Qt::Key_A:
      if (_limitPoints[_selectedPointIndex].x > 0) {
        _limitPoints[_selectedPointIndex].x--;
      }
      break;
    case Qt::Key_D:
      if (_limitPoints[_selectedPointIndex].x < _cameraFrame.cols) {
        _limitPoints[_selectedPointIndex].x++;
      }
      break;
    default:
      break;
  }
}

void FieldPointsCalibrateDialog::mousePressEvent(QMouseEvent *event) {
  if (event->pos().x() - this->ui->videoLabel->x() > 0 &&
      event->pos().y() - this->ui->videoLabel->y() > 0 &&
      event->pos().x() -
              (this->ui->videoLabel->x() + this->ui->videoLabel->width()) <
          0 &&
      event->pos().y() -
              (this->ui->videoLabel->y() + this->ui->videoLabel->height()) <
          0) {
    double xConvert = this->_frameCols / (double)this->ui->videoLabel->width();
    double yConvert = this->_frameRows / (double)this->ui->videoLabel->height();

    this->_limitPoints[this->_selectedPointIndex].x =
        (event->pos().x() - this->ui->videoLabel->x()) * xConvert;
    this->_limitPoints[this->_selectedPointIndex].y =
        (event->pos().y() - this->ui->videoLabel->y()) * yConvert;
  }
}

void FieldPointsCalibrateDialog::updateFrame() {
  CameraManager::singleton().getCurrentFrame(this->_cameraFrame);

  this->_frameCols = this->_cameraFrame.cols;
  this->_frameRows = this->_cameraFrame.rows;

  if (!this->_cameraFrame.empty()) {
    this->drawPoints();

    cv::Mat frameToImage = this->_cameraFrame.clone();
    cv::Size newSize(ui->videoLabel->width(), ui->videoLabel->height());
    cv::resize(frameToImage, frameToImage, newSize);
    cv::cvtColor(frameToImage, frameToImage, cv::COLOR_BGR2RGB);
    QImage qimg2((uchar *)frameToImage.data, frameToImage.cols,
                 frameToImage.rows, frameToImage.step, QImage::Format_RGB888);
    ui->videoLabel->setPixmap(QPixmap::fromImage(qimg2));
  }
  QCoreApplication::processEvents();
}

void FieldPointsCalibrateDialog::getPointsFromFile(std::string path) {
    std::ifstream file(path);
    if (!file.is_open()) {
        std::cout << "failed to open file: " << path << std::endl;
        exit(1);
    }

    std::string content((std::istreambuf_iterator<char>(file)),
                    std::istreambuf_iterator<char>());

    nlohmann::json pointsJson;
    if (content.empty()) {
      std::cerr << "The file is empty: " << path << std::endl;
    }else pointsJson = nlohmann::json::parse(content);
    file.close();

    std::string pointString = "point";

    for (int i = 1; i <= 4; i++) {
        std::string tempKey = pointString + std::to_string(i);
        auto& value = pointsJson[tempKey];
        std::cout << "fieldPoint" << std::endl;
        _limitPoints[i - 1].x = value["x"].get<int>();
        _limitPoints[i - 1].y = value["y"].get<int>();
    }

    file.close();
}

void FieldPointsCalibrateDialog::drawPoints() {
  for (int i = 0; i < 4; i++) {
    cv::line(_cameraFrame, _limitPoints[i], _limitPoints[(i + 1) % 4],
             YELLOW_SCALAR, LINE_THICKNESS, cv::LINE_AA);
  }

  for (int i = 0; i < 4; i++) {
    if (i == _selectedPointIndex) {
      cv::circle(_cameraFrame, _limitPoints[i], CIRCLE_RADIUS, RED_SCALAR, -1,
                 1);
    } else {
      cv::circle(_cameraFrame, _limitPoints[i], CIRCLE_RADIUS, BLUE_SCALAR, -1,
                 1);
    }

    cv::putText(_cameraFrame, std::to_string(i + 1),
                cv::Point(_limitPoints[i].x - 10, _limitPoints[i].y - 10),
                cv::FONT_HERSHEY_PLAIN, 1.5, RED_SCALAR, 2, cv::LINE_4);
  }
}

void FieldPointsCalibrateDialog::on_buttonBox_accepted() {
  std::ofstream file(FIELDLIMITSPATH, std::ios::out | std::ios::trunc);
  if (!file.is_open()) {
      std::cout << "failed to open file: " << FIELDLIMITSPATH << std::endl;
      exit(1);
  }

  std::string pointString = "point";

  nlohmann::json value;

  for (int i = 1; i <= 4; i++) {
      std::string tempKey = pointString + std::to_string(i);
      nlohmann::json pair;
      pair["x"] = _limitPoints[i - 1].x;
      pair["y"] = _limitPoints[i - 1].y;
      value[tempKey] = pair;
  }


  file << value.dump(4);
  file.close();
}

void FieldPointsCalibrateDialog::on_buttonBox_rejected() {
  this->_updateFrameTimer->stop();
}
