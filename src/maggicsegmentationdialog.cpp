#include "maggicsegmentationdialog.h"
#include "ui_maggicsegmentationdialog.h"
#include <QMouseEvent>
#include <chrono>
#include <QDir>
#define FILTER_GRAY_THRESHOLD_DEFAULT_MINIMUM 17
#define FILTER_GRAY_THRESHOLD_DEFAULT_MAXIMUM 45

String MaggicSegmentationDialog::_inputFolderName = "Input";
String MaggicSegmentationDialog::_outputFolderName = "Output";

Strings getFileList(String &path, QDir **_dir = nullptr){
    Strings list;
    QDir *dir = nullptr;
    if (_dir == nullptr) {
        if (*_dir == nullptr) *_dir = new QDir(path.c_str());
        else dir = *_dir;
    }
    else {
        *_dir = new QDir(path.c_str());
        dir = *_dir;
    }
    if (dir->exists()) {
        std::cout << dir->absolutePath().toStdString() << std::endl;
        QStringList sl = dir->entryList(QDir::Files);
        for (QString &e : sl) {
            list.push_back(e.toStdString());
        }
    } else {
        dir->mkpath(dir->absolutePath());
    }
    if (_dir == nullptr) delete dir;
    return list;
}

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
  this->_updateFrameTimer->start(16);

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

  this->_selectedFileIndex = -1;
  this->_fileList= getFileList(_inputFolderName, &(this->_inputDir));
  this->_outputDir = new QDir(this->_outputFolderName.c_str());
  if (!this->_outputDir->exists()) {
      this->_outputDir->mkpath(this->_outputDir->absolutePath());
  }
  if (this->_fileList.size()) {
      std::cout << "Files:" << std::endl;
      for (auto &e : this->_fileList) {
          std::cout << " " << e << std::endl;
      }
  }

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
  delete this->_inputDir;
  delete this->_outputDir;
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

    //maggicSegmentation->run(this->_actualFrame);
    if (this->ui->tabWidget->currentIndex() == 4) this->maggicSegmentation->updateDetails();
    else maggicSegmentation->updateFrame();
    maggicSegmentation->calibrate(this->_actualFrame);
    maggicSegmentation->getDebugFrame(this->_segmentedFrame);

    timerFPS.stop();
    //printf("MaggicVision us %.0f fps %.0f\n", timerFPS.getMicroseconds(), timerFPS.getInFPS());

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
    cv::cvtColor(tempFrame, tempFrame, cv::COLOR_BGR2RGB);
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
  this->maggicSegmentation->lock();
  int val = ui->threshGrayHorizontalSlider->value();
  this->maggicSegmentation->setFilterGrayThresholdValue(val);
  ui->threshGrayLcdNumber->display(val);
  this->maggicSegmentation->setHUETable(true);
  this->maggicSegmentation->generateLUTFromHUE();
  this->maggicSegmentation->unlock();
}

void MaggicSegmentationDialog::on_loadButton_clicked()
{
  this->maggicSegmentation->loadDefaultHue();
}

void MaggicSegmentationDialog::on_resetButton_clicked() {
  this->maggicSegmentation->lock();
  this->maggicSegmentation->setFilterGrayThresholdValues(FILTER_GRAY_THRESHOLD_DEFAULT_MINIMUM,FILTER_GRAY_THRESHOLD_DEFAULT_MAXIMUM);
  this->maggicSegmentation->setDebugSelection(maggicVisionDebugSelectionVector[ui->tabWidget->currentIndex()]);
  this->maggicSegmentation->setLearningThresholdFrames(static_cast<uint>(ui->learnSpinBox->value()));

  int m, M;
  this->maggicSegmentation->getFilterGrayThresholdValues(m,M);
  this->maggicSegmentation->unlock();
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
  this->maggicSegmentation->lock();
  this->maggicSegmentation->setHUETable(true);
  this->maggicSegmentation->generateLUTFromHUE();
  int* dst_LUT = reinterpret_cast<LUTSegmentation*>(
              Vision::singleton().getSegmentationObject())->getLUT();
  int* src_LUT = this->maggicSegmentation->getLUT();
  memcpy(dst_LUT,src_LUT,LUTSIZE*sizeof(int));
  this->maggicSegmentation->unlock();
  this->processAndSave();
  this->maggicSegmentation->saveSelectedDebug();
}

void MaggicSegmentationDialog::processAndSave() {
    std::cout << "Processing and saving segmentation." << std::endl;
    this->maggicSegmentation->calibrate(this->_actualFrame);
    this->maggicSegmentation->lock();
    this->_segmentedFrame = this->maggicSegmentation->run(this->_inputFrame);
    this->maggicSegmentation->getSegmentationFrameFromLUT(this->_segmentedFrame);
    this->maggicSegmentation->unlock();
    cv::imwrite(this->_outputDir->absolutePath().toStdString()
                +"/"
                +this->_fileList[this->_selectedFileIndex],
                this->_segmentedFrame);
}

void MaggicSegmentationDialog::autoResizeInputFrame(cv::Mat &frame) {
    if (frame.rows == 1080 && frame.cols == 1920) {
        cv::resize(frame, frame,
                   cv::Size(1280, 720), 0, 0);
    }
    if (frame.rows == 720 && frame.cols == 1280) {
      cv::Rect cropRectangle(213, 0, 854, 720);

      // Crop the full image to that image contained by the rectangle
      // cropRectangle
      cv::Mat croppedRef(frame, cropRectangle);
      croppedRef.copyTo(frame);
      cv::resize(frame, frame,
                 cv::Size(FRAME_WIDTH_DEFAULT, FRAME_HEIGHT_DEFAULT), 0, 0);
    }
}

void MaggicSegmentationDialog::useNextImage() { // Circular function
    this->on_playpauseButton_clicked(true);
    this->_selectedFileIndex = (this->_selectedFileIndex+1)
            %static_cast<int>(this->_fileList.size());
    String impath = this->_inputDir->absolutePath().toStdString()
            +"/"
            +this->_fileList[this->_selectedFileIndex];
    this->_inputFrame = cv::imread(impath);
    // this->autoResizeInputFrame(this->_inputFrame);
    this->_inputFrame.copyTo(this->_actualFrame);
    std::cout << "Loaded image(" << this->_selectedFileIndex << "): "
              << impath << std::endl;
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
   /*if (this->ui->tabWidget->currentIndex() == 4 && f_object == this) {
       if (this->maggicSegmentation) {
           this->maggicSegmentation->updateDetails();
       }
   }*/
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
        if (static_cast<int>(mouseEvent->button()) == 2) { // right click
            if (f_object == ui->tabWidget) {
                std::cout << "Right click on Tab widget!" << std::endl;
                this->useNextImage();
            }
        }
    }
  }
  if (f_event->type() == QEvent::MouseMove) {

      cv::Point2f mpos(-1,-1);
      if (f_object == this) {

          QRect qrect = this->ui->visualizationLabel->geometry();
          QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(f_event);
          //std::cout << "(" << qrect.x() << " " << qrect.y() << " " << qrect.width() << " " << qrect.height() << " )" << std::endl;
          cursorInsideVisualization = qrect.contains(static_cast<int>(mouseEvent->x()),static_cast<int>(mouseEvent->y()));
          //std::cout << "cursor " << (cursorInsideVisualization ? "inside" : "outside") << std::endl;
          mpos.x = mouseEvent->x() - qrect.x();
          mpos.y = mouseEvent->y() - qrect.y();

          if(cursorInsideVisualization) {
              //std::cout << "mpos " << mpos.x << " "<< mpos.y << std::endl;
              mpos.x = mpos.x / static_cast<float>(qrect.width());
              mpos.y = mpos.y / static_cast<float>(qrect.height());

            if (this->ui->tabWidget->currentIndex() == 4) this->ui->visualizationLabel->setCursor(Qt::BlankCursor);
            else this->ui->visualizationLabel->setCursor(Qt::ArrowCursor);

          } else mpos.x = mpos.y = -1;

      }
      if (this->maggicSegmentation) {
        this->maggicSegmentation->setMousePosition(mpos);
      }
  }

  if (f_event->type() == QEvent::KeyPress && f_object == this) {
      QKeyEvent* keyEvent = reinterpret_cast<QKeyEvent*>(f_event);
      int modifiers = QApplication::keyboardModifiers();
      bool hasCtrl = (modifiers & Qt::ControlModifier) > 0;
      bool hasShift = (modifiers & Qt::ShiftModifier) > 0;

      bool hasTab = keyEvent->key() == Qt::Key_Tab;
      if (hasCtrl && hasTab) {
        int curr = this->ui->tabWidget->currentIndex();
        int manyTabs = this->ui->tabWidget->count();
        this->ui->tabWidget->setCurrentIndex((curr+1+manyTabs)%manyTabs);
      } else if (hasShift) {
          int curr = this->ui->tabWidget->currentIndex();
          int manyTabs = this->ui->tabWidget->count();
          this->ui->tabWidget->setCurrentIndex((curr-1+manyTabs)%manyTabs);
      }
      if (keyEvent->key() >= Qt::Key_1 && keyEvent->key() <= Qt::Key_5) {
        this->ui->tabWidget->setCurrentIndex(keyEvent->key()- Qt::Key_1);
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

void MaggicSegmentationDialog::on_NormalizedCheckBox_toggled(bool checked)
{
    this->maggicSegmentation->setNormalizedEnabled(checked);
    this->maggicSegmentation->lock();
    this->maggicSegmentation->setHUETable(true);
    this->maggicSegmentation->generateLUTFromHUE();
    this->maggicSegmentation->unlock();
}
