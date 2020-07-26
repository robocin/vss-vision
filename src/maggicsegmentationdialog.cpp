#include "maggicsegmentationdialog.h"
#include "ui_maggicsegmentationdialog.h"
#include <QMouseEvent>
#include <chrono>
#define FILTER_GRAY_THRESHOLD_DEFAULT_MINIMUM 17
#define FILTER_GRAY_THRESHOLD_DEFAULT_MAXIMUM 45


static MaggicVisionDebugSelection maggicVisionDebugSelectionVector[6] = {
  MaggicVisionDebugSelection_Undefined,
  MaggicVisionDebugSelection_ExtremeSaturation,
  MaggicVisionDebugSelection_MultipliedResults,
  MaggicVisionDebugSelection_Thresholded,
  MaggicVisionDebugSelection_SegmentationFrame,
  MaggicVisionDebugSelection_DetailsFrame
};

MaggicSegmentationDialog::MaggicSegmentationDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::MaggicSegmentationDialog)
{
  this->_cameraMan = &this->_cameraMan->singleton();
  ui->setupUi(this);

  this->maggicSegmentation = new MaggicSegmentation();

  qApp->installEventFilter(this);
  this->_updateFrameTimer = new QTimer(this);
  connect(this->_updateFrameTimer,SIGNAL(timeout()),this,SLOT(updateFrame()));
  this->_updateFrameTimer->start(1);

  this->maggicSegmentation->setFilterGrayThresholdValues(FILTER_GRAY_THRESHOLD_DEFAULT_MINIMUM,FILTER_GRAY_THRESHOLD_DEFAULT_MAXIMUM);
  this->maggicSegmentation->setDebugSelection(MaggicVisionDebugSelection_ExtremeSaturation);
  this->maggicSegmentation->setLearningThresholdFrames(static_cast<uint>(ui->learnSpinBox->value()));

  int m, M;
  this->maggicSegmentation->getFilterGrayThresholdValues(m,M);
  this->ui->threshGrayHorizontalSlider->setValue(this->maggicSegmentation->getFilterGrayThresholdValue());
  //std::cout << "THRESHOLD FROM MAGGIC SEGMENTATION " << this->maggicSegmentation->getFilterGrayThresholdValue() << std::endl;
  ui->minimumLcdNumber->display(m);
  ui->maximumLcdNumber->display(M);
  ui->minimumVerticalSlider->setValue(m);
  ui->maximumVerticalSlider->setValue(M);
  entities[0] = nullptr;
  entities[1] = ui->entitiesButton_1;
  entities[2] = ui->entitiesButton_2;
  entities[3] = ui->entitiesButton_3;
  entities[4] = ui->entitiesButton_4;
  entities[5] = ui->entitiesButton_5;
  entities[6] = ui->entitiesButton_6;
  entities[7] = ui->entitiesButton_7;
  
  for(int i=1;i<8;i++) {
    entities[i]->setChecked(false);
  }
  entities[this->maggicSegmentation->getEntitiesCount()]->setChecked(true);
  this->paused = false;

  //on_applyLUTButton_clicked();
  //this->maggicSegmentation->setHUETable(this->maggicSegmentation->useLoadedValues);
  //this->maggicSegmentation->generateLUTFromHUE();

  int* dst_LUT = reinterpret_cast<LUTSegmentation*>(Vision::singleton().getSegmentationObject())->getLUT();
  int* src_LUT = this->maggicSegmentation->getLUT();
  memcpy(dst_LUT,src_LUT,LUTSIZE*sizeof(int));
}

QTimer* MaggicSegmentationDialog::getUpdateFrameTimer() {
  return this->_updateFrameTimer;
}

MaggicSegmentationDialog::~MaggicSegmentationDialog()
{

  //std::cout << "destruction" << std::endl;
  //qApp->removeEventFilter(this);
  //cv::destroyAllWindows();
  //this->hide();

  this->_updateFrameTimer->stop();

  //disconnect(this->_updateFrameTimer,SIGNAL(timeout()),this, SLOT(updateFrame()));
  //this->close();
  delete this->_updateFrameTimer;
  delete this->ui;
  delete this->maggicSegmentation;
}

void MaggicSegmentationDialog::updateFrame()
{
  if (this->isHidden()) return;
  if (this->_updateFrameTimer->isActive() == false) return;

  if (Vision::singleton().isCorrectionEnabled()) {
      if (!this->paused)
        Vision::singleton().getCorrectedDebugFrame(this->_actualFrame);
  } else {
      if (!this->paused)
        CameraManager::singleton().getCurrentFrame(this->_actualFrame);
  }

  if (!this->_actualFrame.empty()) {
    cv::resize(this->_actualFrame,this->_actualFrame,cv::Size(640,480),0,0);

    Timer timerFPS;
    timerFPS.start();

    maggicSegmentation->run(this->_actualFrame);
    maggicSegmentation->calibrate(this->_actualFrame);
    maggicSegmentation->getDebugFrame(this->_segmentedFrame);

    timerFPS.stop();
    printf("MaggicVision us %.0f fps %.0f\n", timerFPS.getMicroseconds(), timerFPS.getInFPS());

    static bool defineThresholdValue = true;

    uint calibratedFrames, totalCalibrationFrames;
    maggicSegmentation->getCalibrationFrames(calibratedFrames);
    maggicSegmentation->getLearningThresholdFrames(totalCalibrationFrames);
      ui->learningProgressBar->setEnabled(false);
      ui->learningProgressBar->setVisible(false);
      ui->learningProgressBar->setValue(100);


      if (defineThresholdValue) {
        int m, M;
        this->maggicSegmentation->updateFilterGrayThresholdValue();
        this->maggicSegmentation->getFilterGrayThresholdValues(m,M);
        ui->threshGrayHorizontalSlider->setMinimum(m);
        ui->threshGrayHorizontalSlider->setMaximum(M);
        int val = this->maggicSegmentation->getFilterGrayThresholdValue();
        ui->threshGrayHorizontalSlider->setValue(val);
        ui->threshGrayLcdNumber->display(val);
      }

    this->setFrameOnScreen();
  }

}

void MaggicSegmentationDialog::setFrameOnScreen()
{
  if(!this->_segmentedFrame.empty()) {
    cv::Mat tempFrame = this->_segmentedFrame.clone();
    cv::Size newSize(this->ui->visualizationLabel->width(), this->ui->visualizationLabel->height());
    cv::resize(tempFrame, tempFrame, newSize);
    cv::cvtColor(tempFrame, tempFrame, CV_BGR2RGB);
    QImage qimg2(reinterpret_cast<uchar*>(tempFrame.data), tempFrame.cols, tempFrame.rows, static_cast<int>(tempFrame.step), QImage::Format_RGB888);
    this->ui->visualizationLabel->setPixmap(QPixmap::fromImage(qimg2));
  } else {
    spdlog::get("General")->warn("You are setting a empty frame to QT Interface (function : SegmentationConfigDialog::setFrameOnScreen)");
  }
}


#define entitiesButtonClicked( elbo ) void MaggicSegmentationDialog::on_entitiesButton_ ## elbo ## _clicked() \
{\
  this->maggicSegmentation->setEntitiesCount( elbo );\
  this->clearEntitiesCheck(); \
  this->entities[elbo]->setChecked(true);\
}
entitiesButtonClicked(1)
entitiesButtonClicked(2)
entitiesButtonClicked(3)
entitiesButtonClicked(4)
entitiesButtonClicked(5)
entitiesButtonClicked(6)
entitiesButtonClicked(7)
#undef entitiesButtonClicked
//ui->tabWidget->currentIndex()+1

void MaggicSegmentationDialog::clearEntitiesCheck() {
  for(int i=1;i<8;i++) {
    entities[i]->setChecked(false);
  }
}

void MaggicSegmentationDialog::on_tabWidget_currentChanged(int index)
{
  this->maggicSegmentation->setDebugSelection(static_cast<MaggicVisionDebugSelection>(maggicVisionDebugSelectionVector[index+1]));
}
void MaggicSegmentationDialog:: on_minimumVerticalSlider_valueChanged()
{
  int m, M;
  this->maggicSegmentation->getFilterGrayThresholdValues(m,M);
  m = ui->minimumVerticalSlider->value();
  ui->minimumLcdNumber->display(m);
  this->maggicSegmentation->setFilterGrayThresholdValues(m,M);
}

void MaggicSegmentationDialog::on_maximumVerticalSlider_valueChanged()
{
  int m, M;
  this->maggicSegmentation->getFilterGrayThresholdValues(m,M);
  M = ui->maximumVerticalSlider->value();
  ui->maximumLcdNumber->display(M);
  this->maggicSegmentation->setFilterGrayThresholdValues(m,M);
}

void MaggicSegmentationDialog::on_threshGrayHorizontalSlider_valueChanged()
{
  int val = ui->threshGrayHorizontalSlider->value();
  this->maggicSegmentation->setFilterGrayThresholdValue(val);
  ui->threshGrayLcdNumber->display(val);
  this->maggicSegmentation->setHUETable(true);
  this->maggicSegmentation->generateLUTFromHUE();
}

void MaggicSegmentationDialog::on_loadButton_clicked()
{
  this->maggicSegmentation->loadDefaultHue();
}

void MaggicSegmentationDialog::on_resetButton_clicked() {
  this->maggicSegmentation->setFilterGrayThresholdValues(FILTER_GRAY_THRESHOLD_DEFAULT_MINIMUM,FILTER_GRAY_THRESHOLD_DEFAULT_MAXIMUM);
  this->maggicSegmentation->setDebugSelection(maggicVisionDebugSelectionVector[ui->tabWidget->currentIndex()]);
  this->maggicSegmentation->setLearningThresholdFrames(static_cast<uint>(ui->learnSpinBox->value()));

  int m, M;
  this->maggicSegmentation->getFilterGrayThresholdValues(m,M);
  ui->minimumLcdNumber->display(m);
  ui->maximumLcdNumber->display(M);
  ui->minimumVerticalSlider->setValue(m);
  ui->maximumVerticalSlider->setValue(M);
}

void MaggicSegmentationDialog::on_playpauseButton_clicked(bool checked)
{
  this->paused = checked;
}

void MaggicSegmentationDialog::on_applyLUTButton_clicked()
{
  this->maggicSegmentation->saveSession();
  this->maggicSegmentation->setHUETable(true);
  this->maggicSegmentation->generateLUTFromHUE();
  int* dst_LUT = reinterpret_cast<LUTSegmentation*>(Vision::singleton().getSegmentationObject())->getLUT();
  int* src_LUT = this->maggicSegmentation->getLUT();
  memcpy(dst_LUT,src_LUT,LUTSIZE*sizeof(int));

}
void MaggicSegmentationDialog::on_fixCameraButton_clicked()
{
  std::stringstream strs;
  strs << "./Config/camera_config_magic.sh ";
  strs << "/dev/video" << CameraManager::singleton().getCameraIndex();
  char tmp[2000];
  strcpy(tmp,strs.str().c_str());
  FILE* f = popen(tmp,"r");
  pclose(f);
}

void MaggicSegmentationDialog::on_buttonBox_accepted()
{
  on_applyLUTButton_clicked();
}


bool MaggicSegmentationDialog::eventFilter(QObject *f_object, QEvent *f_event) {

    static bool cursorInsideVisualization = false;

  if (f_event->type() == QEvent::MouseButtonPress) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(f_event);
    if (this->maggicSegmentation) {
      this->maggicSegmentation->setMouseButtonPress(static_cast<int>(mouseEvent->button()));
    }
  }
  if (f_event->type() == QEvent::MouseButtonRelease) {
    QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(f_event);
    if (this->maggicSegmentation) {
      this->maggicSegmentation->setMouseButtonRelease(static_cast<int>(mouseEvent->button()));
    }
  }
  if (f_event->type() == QEvent::MouseMove) {

      if (f_object == this) {

          cv::Point2f mpos(-1,-1);
          QRect qrect = this->ui->visualizationLabel->frameRect();
          QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(f_event);
          mpos.x = mouseEvent->x() - qrect.x();
          mpos.y = mouseEvent->y() - qrect.y();
          cursorInsideVisualization = qrect.contains(static_cast<int>(mpos.x),static_cast<int>(mpos.y));
          std::cout << "cursor " << (cursorInsideVisualization ? "inside" : "outside") << std::endl;

          if(cursorInsideVisualization) {
              std::cout << "mpos " << mpos.x << " "<< mpos.y << std::endl;
              mpos.x = mpos.x / static_cast<float>(qrect.width());
              mpos.y = mpos.y / static_cast<float>(qrect.height());

            if (this->ui->tabWidget->currentIndex() == 4) this->ui->visualizationLabel->setCursor(Qt::BlankCursor);
            else this->ui->visualizationLabel->setCursor(Qt::ArrowCursor);

          } else mpos.x = mpos.y = -1;
          if (this->maggicSegmentation) {
            this->maggicSegmentation->setMousePosition(mpos);
          }
      }

  }
  return false;
}

void MaggicSegmentationDialog::on_vectorscopeCheckBox_toggled(bool checked)
{
    this->maggicSegmentation->setVectorscopeEnabled(checked);
}

void MaggicSegmentationDialog::on_FilterCheckBox_toggled(bool checked)
{
    this->maggicSegmentation->setFilterEnabled(checked);
}
