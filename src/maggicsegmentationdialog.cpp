#include "maggicsegmentationdialog.h"
#include "ui_maggicsegmentationdialog.h"
#include <QMouseEvent>
#include <chrono>
#include <tbb/tbb.h>
#include <QDir>
#define FILTER_GRAY_THRESHOLD_DEFAULT_MINIMUM 17
#define FILTER_GRAY_THRESHOLD_DEFAULT_MAXIMUM 45

std::string MaggicSegmentationDialog::_inputFolderName = "Input";
std::string MaggicSegmentationDialog::_outputFolderName = "Output";
std::string MaggicSegmentationDialog::_groundTruthFolderName = "GroundTruth";

std::vector<std::string> getFileList(std::string &path, QDir **_dir = nullptr){
    std::vector<std::string> list;
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

  uchar* dst_LUT = reinterpret_cast<LUTSegmentation*>(
              Vision::singleton().getSegmentationObject())->getLUT();
  uchar* src_LUT = this->maggicSegmentation->getLUT();
  memcpy(dst_LUT,src_LUT,LUTSIZE*sizeof(uchar));

  this->_selectedFileIndex = -1;
  this->_inputFileList = getFileList(_inputFolderName, &(this->_inputDir));
  this->_groundTruthFileList = getFileList(_groundTruthFolderName, &(this->_groundTruthDir));
  this->_outputDir = new QDir(this->_outputFolderName.c_str());
  if (!this->_outputDir->exists()) {
      this->_outputDir->mkpath(this->_outputDir->absolutePath());
  }
  if (this->_inputFileList.size()) {
      std::cout << "Files:" << std::endl;
      for (auto &e : this->_inputFileList) {
          std::cout << " " << e << std::endl;
      }
  }
  this->ui->NormalizationComboBox->setCurrentIndex(static_cast<int>(this->maggicSegmentation->getNormalizationMethod()));

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

void MaggicSegmentationDialog::applyLUT(){
    this->maggicSegmentation->saveSession();
    this->maggicSegmentation->lock();
    this->maggicSegmentation->setHUETable(true);
    this->maggicSegmentation->generateLUTFromHUE();
    uchar* dst_LUT = reinterpret_cast<LUTSegmentation*>(
                Vision::singleton().getSegmentationObject())->getLUT();
    uchar* src_LUT = this->maggicSegmentation->getLUT();
    memcpy(dst_LUT,src_LUT,LUTSIZE*sizeof(uchar));
    this->maggicSegmentation->unlock();
}

void MaggicSegmentationDialog::on_applyLUTButton_clicked()
{
  this->applyLUT();
  this->processAndSave();
//  this->maggicSegmentation->saveSelectedDebug();
}

void MaggicSegmentationDialog::processImage(cv::Mat &ground_truth, cv::Mat &segmented, Statistics *gstats = nullptr, Statistics *sstats = nullptr) {
    if (gstats == nullptr || sstats == nullptr) {
        spdlog::get("MaggicVision")->error(" gstats or sstats is nullptr (function : MaggicSemgentationDialog::processImage)");
        return;
    }
    cv::Mat mask = cv::Mat::zeros(ground_truth.size(), ground_truth.type());
    cv::Mat compared;
//    cv::Mat gt, sg;
//    cv::cvtColor(ground_truth,gt,cv::COLOR_BGR2BGRA);
//    cv::cvtColor(segmented,sg,cv::COLOR_BGR2BGRA);
//    gt = cv::Mat(gt.size(),CV_32SC1,gt.data);
//    sg = cv::Mat(sg.size(),CV_32SC1,sg.data);
//    cv::Mat mask;
//    cv::bitwise_and(gt, sg, mask);
//    mask = cv::Mat(mask.size(),CV_8UC4,mask.data);
    // Creating Ground Truth statistics
//    #pragma omp parallel for
    tbb::parallel_for(tbb::blocked_range2d<int>(0, mask.rows, 238, 0, mask.cols, 161),
      [&](const tbb::blocked_range2d<int> &r) {
       for (int i = r.rows().begin(); i != r.rows().end(); i++) {
            for (int j = r.cols().begin(); j != r.cols().end(); j++) {
    //    for (int i=0;i<mask.rows; ++i) {
    //        for (int j=0;j<mask.cols; ++j) {
                cv::Vec3b gt = ground_truth.at<cv::Vec3b>(i,j);
                cv::Vec3b sg = segmented.at<cv::Vec3b>(i,j);
                bool b = gt[0] == sg[0];
                bool g = gt[1] == sg[1];
                bool r = gt[2] == sg[2];
                if (b && g && r) {
                    mask.at<cv::Vec3b>(i,j) = cv::Vec3b(255,255,255);
                } else {
                    mask.at<cv::Vec3b>(i,j) = cv::Vec3b(0,0,0);
                }
            }
        }
    });
//    cv::imwrite(this->_outputDir->absolutePath().toStdString() + "/mask.png",mask);
    cv::cvtColor(mask,mask,cv::COLOR_BGRA2GRAY);
    cv::bitwise_and(ground_truth, ground_truth, compared, mask);
//    cv::imwrite(this->_outputDir->absolutePath().toStdString() + "/compared.png",compared);
//    cv::imwrite(this->_outputDir->absolutePath().toStdString() + "/gt.png",ground_truth);

    // Clean stats mapping
    sstats->clear();
    gstats->clear();

    // Initializing stats
    for (uint i=0; i < 8; ++i) { // black to light blue
        cv::Vec3b *v = reinterpret_cast<cv::Vec3b*>(ColorSpace::markerColors) + i;
        gstats->insert(std::make_pair(MaggicSegmentation::BGR2RGBHash(*v), 0));
        sstats->insert(std::make_pair(MaggicSegmentation::BGR2RGBHash(*v), 0));
    }

    // Creating Ground Truth statistics
    for (int i=0;i<ground_truth.rows; ++i) {
        for (int j=0;j<ground_truth.cols; ++j) {
            cv::Vec3b pixel = ground_truth.at<cv::Vec3b>(i,j);
            gstats->find(MaggicSegmentation::BGR2RGBHash(pixel))->second++;
        }
    }

    // Comparing and creating statistics
    for (int i=0;i<compared.rows; ++i) {
        for (int j=0;j<compared.cols; ++j) {
            cv::Vec3b pixel = compared.at<cv::Vec3b>(i,j);
            uchar pixelm = mask.at<uchar>(i,j);
            if (pixelm)
                sstats->find(MaggicSegmentation::BGR2RGBHash(pixel))->second++;
        }
    }
}

void MaggicSegmentationDialog::processBatch() {
    this->applyLUT();
    this->_selectedFileIndex = -1;



    for (size_t i=0; i < this->_inputFileList.size(); ++i) {
        this->useNextImage();
        for (int n=0;n < MaggicSegmentation::NormalizationMethod::NORMALIZATION_METHODS_LENGTH; ++n){
            this->maggicSegmentation->setNormalizationMethod(
                        static_cast<MaggicSegmentation::NormalizationMethod>(n));
            for (int t =1; t< 256; ++t) {
                this->maggicSegmentation->setFilterGrayThresholdValue(t);
                this->applyLUT();
                this->processAndSave();
            }
        }
    }
}

void MaggicSegmentationDialog::saveStats(Statistics &gstats, Statistics &sstats)  {
    std::map<uint, uint> ordered_color;
//    bool latex = true;
    bool plot = true;

    int idx[8] = {0,4,5,2,3,6,7,1}; // bk r g b y m c
    for (uint i=0; i < 8; ++i) { // black to light blue
        cv::Vec3b *v = reinterpret_cast<cv::Vec3b*>(ColorSpace::markerColors) + idx[i];
        uint hash = MaggicSegmentation::BGR2RGBHash(*v);
        ordered_color.insert(std::make_pair(i, hash));
    }
    if (plot) {
        size_t fileNameUsableLen = this->_inputFileName.size()-4;
        MaggicSegmentation::NormalizationMethod method;
        this->maggicSegmentation->getNormalizationMethod(method);
        int method_number = (this->maggicSegmentation->getNormalizedEnabled() ? static_cast<int>(method) : 0);
        std::string filepath = this->_outputDir->absolutePath().toStdString()
                +"/"+this->_inputFileName.substr(0,fileNameUsableLen)
                + std::to_string(method_number) + ".txt";
        std::cout << "Saving stats (" << this->maggicSegmentation->getFilterGrayThresholdValue()
                  << ") in " << filepath << std::endl;
        if (this->maggicSegmentation->getFilterGrayThresholdValue() == 1) {
            std::fstream fout(filepath, std::fstream::out);
            fout << "threshold\t";
            for (int i =0; i<8; ++i) {
                fout << MaggicSegmentation::RGBHash2String(ordered_color[i]);
                if (i!=7) fout << "\t";
            }
            fout << std::endl;
            fout.close();
        }
        std::fstream fout(filepath, std::fstream::out | std::fstream::app);
        if (fout.is_open()) {
            int totalGT = 0, totalSG = 0;
            fout << this->maggicSegmentation->getFilterGrayThresholdValue() << "\t";
            for (int i = 0; i < 8; ++i) {
                totalGT += gstats.find(ordered_color[i])->second;
                totalSG += sstats.find(ordered_color[i])->second;
            }
            for (int i = 0; i < 8; ++i) {
                float pct = sstats[ordered_color[i]]/static_cast<float>(gstats[ordered_color[i]]);
                fout << std::fixed << std::setprecision(1) << 100.0*pct;
                if (i !=7) fout << "\t";
            }
            fout << "\t" << 100.0*totalSG/static_cast<float>(totalGT) << std::endl;

            fout.close();
        } else {
            spdlog::get("MaggicVision")->error("Could not save latex stats. (function : MaggicSemgentationDialog::saveStats)");
        }
    }


//    if (latex) {
//        size_t fileNameUsableLen = this->_inputFileName.size()-4;
//        std::string filepath = this->_outputDir->absolutePath().toStdString()
//                +"/"+this->_inputFileName.substr(0,fileNameUsableLen)
//                +"_"+ std::to_string(this->maggicSegmentation->getFilterGrayThresholdValue()) +".tex";
//        std::cout << "Saving stats in " << filepath << std::endl;
//        std::fstream fout(filepath, std::fstream::out);
//        if (fout.is_open()) {
//            int totalGT = 0, totalSG = 0;
//            fout << "Segmentation Stats:" << std::endl;
//            for (int i =0; i<8; ++i) {
//                totalGT += gstats.find(ordered_color[i])->second;
//                fout << MaggicSegmentation::RGBHash2String(ordered_color[i]);
//                if (i !=7) fout << " & ";
//            }
//            fout << "\\" << std::endl;

//            for (int i =0; i<8; ++i) {
//                float pct = sstats[ordered_color[i]]/static_cast<float>(gstats[ordered_color[i]]);
//                fout << std::fixed << std::setprecision(1) << 100.0*pct;
//                if (i !=7) fout << " & ";
//            }
//            fout << "\\" << std::endl;


//            fout.close();
//        } else {
//            spdlog::get("MaggicVision")->error("Could not save latex stats. (function : MaggicSemgentationDialog::saveStats)");
//        }
//    }
//    {
//        size_t fileNameUsableLen = this->_inputFileName.size()-4;
//        std::string filepath = this->_outputDir->absolutePath().toStdString()
//                +"/"+this->_inputFileName.substr(0,fileNameUsableLen)
//                +"_"+ std::to_string(this->maggicSegmentation->getFilterGrayThresholdValue()) +".txt";
//        std::cout << "Saving stats in " << filepath << std::endl;
//        std::fstream fout(filepath, std::fstream::out);
//        if (fout.is_open()) {
//            int totalGT = 0, totalSG = 0;
//            fout << "Ground-Truth Stats:" << std::endl;
//            for (auto &e : gstats) {
//                fout << MaggicSegmentation::RGBHash2String(e.first) << "\t" << e.second << std::endl;
//                totalGT += e.second;
//            }
//            fout << "Segmented Stats:" << std::endl;
//            for (auto &e : sstats) {
//                fout << MaggicSegmentation::RGBHash2String(e.first) << "\t" << e.second << std::endl;
//                totalSG += e.second;
//            }
//            fout << "Correct:" << std::endl;
//            for (auto &e : sstats) {
//                std::string colorName = MaggicSegmentation::RGBHash2String(e.first);
//                float pct = e.second/static_cast<float>(gstats[e.first]);
//                fout << colorName << "\t" << std::fixed << std::setprecision(3) << pct << std::endl;
//            }
//            fout << "Wrong:" << std::endl;
//            for (auto &e : sstats) {
//                std::string colorName = MaggicSegmentation::RGBHash2String(e.first);
//                float pct = (gstats[e.first] - e.second)/static_cast<float>(gstats[e.first]);
//                fout << colorName << "\t" << std::fixed << std::setprecision(3) << pct << std::endl;
//            }
//            fout << "Total:" << std::endl;
//            fout << "totalGT\t" << totalGT << std::endl;
//            fout << "totalSG\t" << totalSG << std::endl;
//            fout << "SGpct\t" << std::fixed << std::setprecision(3) << totalSG/static_cast<float>(totalGT) << std::endl;
//            fout << "SGpct\t" << std::fixed << std::setprecision(3) << (totalGT-totalSG)/static_cast<float>(totalGT) << std::endl;

//            fout.close();
//        } else {
//            spdlog::get("MaggicVision")->error("Could not save stats. (function : MaggicSemgentationDialog::saveStats)");
//        }
//    }
}

void MaggicSegmentationDialog::processAndSave() {
    std::cout << "Processing and saving segmentation." << std::endl;
    this->maggicSegmentation->calibrate(this->_actualFrame);
    this->maggicSegmentation->lock();
    this->maggicSegmentation->run(this->_inputFrame);
    this->maggicSegmentation->getSegmentationFrameFromLUT(this->_segmentedFrame);
    this->maggicSegmentation->unlock();
//    Statistics gstats, sstats;
//    this->processImage(this->_groundTruthFrame, this->_segmentedFrame, &gstats, &sstats);
//    cv::imwrite(this->_outputDir->absolutePath().toStdString()
//                +"/"
//                +this->_inputFileList[this->_selectedFileIndex],
//                this->_segmentedFrame);
//    this->saveStats(gstats, sstats);
}

void MaggicSegmentationDialog::autoResizeInputFrame(cv::Mat &frame) {
    if (frame.rows == 1080 && frame.cols == 1920) {
        cv::resize(frame, frame,
                   cv::Size(1280, 720), 0, 0);
    }
//    if (frame.rows == 720 && frame.cols == 1280) {
//      cv::Rect cropRectangle(213, 0, 854, 720);

//      // Crop the full image to that image contained by the rectangle
//      // cropRectangle
//      cv::Mat croppedRef(frame, cropRectangle);
//      croppedRef.copyTo(frame);
//      cv::resize(frame, frame,
//                 cv::Size(FRAME_WIDTH_DEFAULT, FRAME_HEIGHT_DEFAULT), 0, 0);
//    }
}

void MaggicSegmentationDialog::useNextImage() { // Circular function
    this->on_playpauseButton_clicked(true);
    this->_selectedFileIndex = (this->_selectedFileIndex+1)
            %static_cast<int>(this->_inputFileList.size());
    this->_inputFileName = this->_inputFileList[this->_selectedFileIndex];
    std::string input_impath = this->_inputDir->absolutePath().toStdString()
            +"/"
            +this->_inputFileName;
    std::string ground_truth_impath = this->_groundTruthDir->absolutePath().toStdString()
            +"/"
            +this->_groundTruthFileList[this->_selectedFileIndex];
    // IN
    this->_inputFrame = cv::imread(input_impath);
     this->autoResizeInputFrame(this->_inputFrame);
    this->_inputFrame.copyTo(this->_actualFrame);
    std::cout << "Loaded image(" << this->_selectedFileIndex << "): "
              << input_impath << std::endl;
    // GT
    this->_groundTruthFrame = cv::imread(ground_truth_impath);
    std::cout << "Loaded image(" << this->_selectedFileIndex << "): "
              << ground_truth_impath << std::endl;
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
                this->processAndSave();
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
  if (f_event->type() == QEvent::KeyRelease && f_object == this) {
      QKeyEvent* keyEvent = reinterpret_cast<QKeyEvent*>(f_event);
      if (keyEvent->key() == Qt::Key_B) {
        this->processBatch();
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

void MaggicSegmentationDialog::on_NormalizationComboBox_currentIndexChanged(int index)
{
    this->maggicSegmentation->setNormalizationMethod(static_cast<MaggicSegmentation::NormalizationMethod>(index));
    this->maggicSegmentation->setNormalizedEnabled(index > 0);
    this->maggicSegmentation->lock();
    this->maggicSegmentation->setHUETable(true);
    this->maggicSegmentation->generateLUTFromHUE();
    this->maggicSegmentation->unlock();
}
