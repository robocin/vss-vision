#include "Vision.h"
#include <algorithm>

Vision::Vision()
{
  this->_detection = new BlobDetection();
  this->_detection->init();
  this->_detection->setTeamColor(getTeamColor());
  this->_segmentation = new LUTSegmentation();
  this->_correction = new WarpCorrection();
  this->_compression = new RunLengthEncoding();
  ((WarpCorrection*) this->_correction )->initFromFile(FIELDLIMITSPATH,&this->_convert);
  ((LUTSegmentation*)this->_segmentation)->initFromFile(SEGMENTATION_DEFAULT_FILE);
  this->_isCorrectionEnabled = false;
  this->_isProcessingEnabled = false;
  std::vector<Entity> currentPositions (7, Entity());
  this->_robotPositions = currentPositions;
  this->_currentFrame = cv::Mat::zeros(640,480,CV_8UC3);
  this->_lastPositions = std::vector<std::queue<std::pair<cv::Point2d,QTime>>>(7);
  this->_firstFrameDeepLog = true;
  this->_deepLogFile = NULL;
  this->_deepLogFileName = "log"; // default file name
  this->_deepLogFileFolder = "Log/deep/"; // default file folder
  this->_deepLogRecordingVideo = false;
  this->_visionRunTime = 0;
}

Vision::~Vision()
{
  if(this->_detection != NULL)
  {
    delete(this->_detection);
  }

  if(this->_segmentation != NULL)
  {
    delete(this->_segmentation);
  }
}

Vision& Vision::singleton()
{
  static Vision instance;

  return instance;
}

void Vision::setFrame(cv::Mat& frame)
{
  if (this->_isCorrectionEnabled) {

    this->_currentFrame = this->_correction->run(frame);

  } else {
    this->_currentFrame = frame;
  }
}

void Vision::saveFrameDimensions(cv::Mat &frame){
    _frameDimensions = Point(frame.rows,frame.cols);
}

Point Vision::getFrameDimensions(){
    return _frameDimensions;
}

void Vision::update(std::vector<Entity> &currentPositions)
{

  if (this->_isCorrectionEnabled) {
    Global::setConvertRatio(_convert);
    //this->setConvertAll(currentPositions); // apagar depois, field possui
    // as taxas de conversao
  }

  this->_processingFrame = this->_currentFrame.clone();

  if (this->_isProcessingEnabled) {

    this->_processingFrame = this->_segmentation->run(this->_processingFrame);
    std::vector< std::vector <Run> > runs = this->_compression->run(this->_processingFrame);
    saveFrameDimensions(this->_processingFrame);
    this->_detection->run(currentPositions, runs, this->_processingFrame.rows, this->_processingFrame.cols);
  }

}



void Vision::update(cv::Mat &frame, QTime timeStamp)
{
  //vss.setFrame(frame);
  //vss.m_enemies.clear();
  //vss.m_allies.clear();
  this->_visionTimer.start();
  std::vector<Entity> &currentPositions = this->_robotPositions;
  this->setFrame(frame);
  this->update(currentPositions);
  //this->setObjectsSpeed(timeStamp, currentPositions);
  this->_robotPositions = currentPositions;

  int actualTime = timeStamp.msecsSinceStartOfDay();
  std::vector<Entity> &entities = currentPositions;

  if (this->_deepLogRecord) {
    // put to deep log
    if (this->_firstFrameDeepLog) {
      if (!this->_deepLogRecordingVideo) {
        QDate date = QDate::currentDate();
        this->_deepLogFileFolder = "Log/deep/" + date.toString("yyyy-MM-dd/").toStdString();
        this->_deepLogFileName = "log";
        this->_deepLogFilePath = this->_deepLogFileFolder + this->_deepLogFileName;
      }
      std::cout << "Creating Log folder " << this->_deepLogFileFolder << std::endl;
      std::string command = "mkdir -p " + this->_deepLogFileFolder;
      FILE*f = popen(command.c_str(),"r");
      pclose(f);

      std::stringstream ss;
      int ini = actualTime;
      ss << this->_deepLogFilePath << "_" << timeStamp.hour() << "." << timeStamp.minute() << "." << timeStamp.second() << ".csv";
      std::cout << "Creating file " << ss.str() << std::endl;
      this->_deepLogFile = fopen(ss.str().c_str(),"w");
      if (this->_deepLogFile) {
        this->_firstFrameDeepLog = false;
        this->_deepLogInitialTime = ini;

        fprintf(this->_deepLogFile,"ID_VIDEO;TIMESTAMP_INITIAL;ID_ROBO1;ID_ROBO2;ID_ROBO3\n");
        fprintf(this->_deepLogFile,"%s;%d;%d;%d;%d\n",this->_deepLogFileName.c_str(),this->_deepLogInitialTime, entities[ROBOT1].id(), entities[ROBOT2].id(), entities[ROBOT3].id());
        fprintf(this->_deepLogFile,"R1X;R1Y;R1T;R2X;R2Y;R2T;R3X;R3Y;R3T;A1X;A1Y;A1T;A2X;A2Y;A2T;A3X;A3Y;A3T;BX;BY;TIMESTAMP_FRAME\n");

      }

    }

    if (this->_deepLogFile) {
      // any other frame
      fprintf(this->_deepLogFile,"%d;%d;%lf;",entities[ROBOT1].position().x, entities[ROBOT1].position().y, entities[ROBOT1].angle());
      fprintf(this->_deepLogFile,"%d;%d;%lf;", entities[ROBOT2].position().x, entities[ROBOT2].position().y, entities[ROBOT2].angle());
      fprintf(this->_deepLogFile,"%d;%d;%lf;", entities[ROBOT3].position().x, entities[ROBOT3].position().y, entities[ROBOT3].angle());

      fprintf(this->_deepLogFile,"%d;%d;%lf;", entities[ADV1].position().x, entities[ADV1].position().y, entities[ADV1].angle());
      fprintf(this->_deepLogFile,"%d;%d;%lf;", entities[ADV2].position().x, entities[ADV2].position().y, entities[ADV2].angle());
      fprintf(this->_deepLogFile,"%d;%d;%lf;", entities[ADV3].position().x, entities[ADV3].position().y, entities[ADV3].angle());

      fprintf(this->_deepLogFile,"%d;%d;", entities[BALL].position().x, entities[BALL].position().y, entities[BALL].angle());
      fprintf(this->_deepLogFile,"%d\n", actualTime - this->_deepLogInitialTime);
    }

   }
   this->_visionTimer.stop();
   this->_visionRunTime = static_cast<double> (this->_visionTimer.getMilliseconds()*0.2 + this->_visionRunTime*0.8);
}

cv::Mat Vision::getSegmentationDebugFrame(cv::Mat frame)
{
  if (this->_isCorrectionEnabled) {
    frame = this->_correction->run(frame);
  }

  this->_segmentation->run(frame);
  return ((LUTSegmentation*)this->_segmentation)->getSegmentationFrameFromLUT();
}

cv::Mat Vision::getDetectionDebugFrame(cv::Mat frame)
{
  if (this->_isCorrectionEnabled) {
    frame = this->_correction->run(frame);
  }

  this->_correctedFrame = this->_processingFrame.clone();

  frame = this->_segmentation->run(frame);
  this->_detection->run(this->_robotPositions,frame,frame.rows,frame.cols);
  return this->_detection->getDebugFrame();
}

cv::Mat Vision::getTrackingFrame()
{
  return _tracking->getDebugFrame();
}

ImageProcessing* Vision::getSegmentationObject() {
  return this->_segmentation;
}

bool Vision::setTrackingAlgorithm(std::string algorithmLabel)
{
  if(this->_tracking != NULL) {
    delete this->_tracking;
  }
  if(algorithmLabel == GENERIC_TRACKING_LABEL) {
    //this->_tracking = new Generic();
    return true;
  }
  return false;
}

bool Vision::setDetectionAlgorithm(std::string algorithmLabel)
{
  if(this->_detection != NULL) {
    delete this->_detection;
  }

  if(algorithmLabel == WHEREARE_LABEL) {
    this->_detection = new BlobDetection();
    this->_detection->init();
    return true;
  }
  return false;
}

void Vision::setDetectionParam(std::string var, int value)
{
  this->_detection->setUp(var,value);
}

void Vision::setTrackParam(std::string var, int value)
{
  this->_tracking->setUp(var,value);
}
void Vision::setDetectionParamFromXml()
{
  if(this->_detection != NULL)
  {
    this->_detection->init();
  }
}

void Vision::setTrackParamFromXml()
{
  if(this->_tracking != NULL)
  {
    this->_tracking->init();
  }
}

cv::Mat Vision::getCorrectedDebugFrame(cv::Mat &frame)
{
  return _correction->run(frame);
}

void Vision::savePositionParam()
{
  if(this->_detection != NULL) {
    this->_detection->saveParam();
  }
  if(this->_tracking != NULL) {
    this->_tracking->saveParam();
  }
}

void Vision::resetCorrection()
{
  ((WarpCorrection*) this->_correction )->initFromFile(FIELDLIMITSPATH, &this->_convert);
}

void Vision::resetSegmentation()
{
  ((LUTSegmentation*)this->_segmentation)->initFromFile(SEGMENTATION_DEFAULT_FILE);
}

cv::Mat Vision::getSegmentationFrame()
{
  return this->_segmentation->getDebugFrame();
}

cv::Mat Vision::getDetectionFrame()
{
  return this->_detection->getDebugFrame();
}

bool  Vision::isCorrectionEnabled()
{
  return this->_isCorrectionEnabled;
}

void Vision::setCorrection(bool enabled)
{
  this->_isCorrectionEnabled = enabled;
}

bool Vision::isProcessingEnabled()
{
  return this->_isProcessingEnabled;
}

void Vision::setProcessing(bool enabled)
{
  this->_isProcessingEnabled = enabled;
}

int Vision::setColorIndex(int color, int index)
{
  return this->_detection->setColorIndex(color, index);
}

void Vision::setQuantizationBool(bool quantization)
{

  ((LUTSegmentation*)this->_segmentation)->setQuantizationBool(quantization);
}

bool Vision::getQuantizationBool()
{

  return ((LUTSegmentation*)this->_segmentation)->getQuantizationBool();
}

std::vector<Entity> Vision::getRobotPositions()
{
  return this->_robotPositions;
}

void Vision::setTeamColor(int color)
{
  this->_teamColor = color;
  this->_detection->setTeamColor(this->_teamColor);
}

int Vision::getTeamColor()
{
  return this->_teamColor;
}

cv::Mat Vision::getCurrentFrame() {
  this->_currentFrameLocker.lockForRead();
  cv::Mat clone = this->_currentFrame.clone();
  this->_currentFrameLocker.unlock();
  return clone;
}

void Vision::setDeepLogFileName(std::string fileName) {
  this->_deepLogFilePath = fileName;

  this->_deepLogFileName = fileName.substr(
        std::max(0,(int)fileName.rfind('/')+1));
}

void Vision::setRecordingVideo(bool value) {
  this->_deepLogRecordingVideo = value;
}

void Vision::closeDeepLog() {
  if(this->_deepLogFile) fclose(this->_deepLogFile);
  this->_deepLogRecord = false;
}

void Vision::recordDeepLog() {
  this->_deepLogRecord = true;
  this->_firstFrameDeepLog = true;
}

double Vision::getVisionRunTime() {
  return this->_visionRunTime;
}
