#include "Vision.h"
#include "Network/Network.h"
#include <algorithm>

Vision::Vision()
{
//    this->_visionStatusLocker.lock();
    this->_detection = new BlobDetection();
    this->_detection->init();
    this->_detection->setTeamColor(getTeamColor());
    this->_segmentation = new LUTSegmentation();
    this->_correction = new WarpCorrection();
    this->_compression = new RunLengthEncoding();
    static_cast<WarpCorrection*>(this->_correction)->initFromFile(FIELDLIMITSPATH,&this->_convert);
    static_cast<LUTSegmentation*>(this->_segmentation)->initFromFile(SEGMENTATION_DEFAULT_FILE);
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
    this->firstTime = QTime::currentTime();
//    this->_visionStatusLocker.unlock();
}

Vision::~Vision()
{
    this->_visionStatusLocker.lock();
    if (this->_detection)
        delete this->_detection;

    if (this->_segmentation)
        delete(this->_segmentation);
    this->_visionStatusLocker.unlock();
}

Vision& Vision::singleton()
{
  static Vision instance;

  return instance;
}

void Vision::setFrame(cv::Mat& frame)
{
    if (this->_isCorrectionEnabled)
        this->_currentFrame = this->_correction->run(frame);
    else
        this->_currentFrame = frame;
}

void Vision::saveFrameDimensions(cv::Mat &frame){
    this->_frameDimensions = Point(frame.rows,frame.cols);
}

Point Vision::getFrameDimensions(){
    this->_visionStatusLocker.lock();
    Point ret = _frameDimensions;
    this->_visionStatusLocker.unlock();
    return ret;
}

void Vision::update(std::vector<Entity> &currentPositions)
{
    Global::setConvertRatio(_convert);

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
    this->_visionStatusLocker.lock();
  //vss.setFrame(frame);
  //vss.m_enemies.clear();
  //vss.m_allies.clear();
  this->_visionFrameTimer.start();
  std::vector<Entity> &currentPositions = this->_robotPositions;
  this->setFrame(frame);
  this->update(currentPositions);
  //this->setObjectsSpeed(timeStamp, currentPositions);
  //this->_robotPositions = currentPositions;
  uint32_t actualTime = static_cast<uint32_t>(this->firstTime.msecsTo(timeStamp));
//  printf("%u\n", actualTime);
  std::vector<Entity> &entities = currentPositions;
  //entities.resize(1 + vss.players().size());
  entities.resize(1);
  entities[0] = vss.ball();
  Players players = vss.players();
  entities.insert(entities.end(),players.begin(),players.end());

    // NETWORK
    if (this->_isProcessingEnabled)
        Network::sendFrame(entities, actualTime);
    else {
        Network::frameId = 0;
        this->firstTime = timeStamp.currentTime();
    }


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
   this->_visionFrameTimer.stop();
   this->_visionRunTime = static_cast<double> (this->_visionFrameTimer.getMilliseconds()*0.2 + this->_visionRunTime*0.8);
  this->_visionStatusLocker.unlock();
}

void Vision::getSegmentationDebugFrame(cv::Mat& frame)
{
    this->_visionStatusLocker.lock();
    if (this->_segmentation)
        this->_segmentation->getDebugFrame(frame);
    this->_visionStatusLocker.unlock();
}

void Vision::getDetectionDebugFrame(cv::Mat& frame)
{
    this->_visionStatusLocker.lock();
    if (this->_detection)
        this->_detection->getDebugFrame(frame);
    this->_visionStatusLocker.unlock();
}

void Vision::getTrackingDebugFrame(cv::Mat& frame)
{
    this->_visionStatusLocker.lock();
    if (this->_tracking)
        this->_tracking->getDebugFrame(frame);
    this->_visionStatusLocker.unlock();
}

ImageProcessing* Vision::getSegmentationObject() {
    this->_visionStatusLocker.lock();
    ImageProcessing* ret = this->_segmentation;
    this->_visionStatusLocker.unlock();
    return ret;
}

bool Vision::setTrackingAlgorithm(std::string algorithmLabel)
{
    bool ret = false;

    this->_visionStatusLocker.lock();

    if (this->_tracking)
        delete this->_tracking;

    if (algorithmLabel == GENERIC_TRACKING_LABEL) {
        //this->_tracking = new Generic();
        ret = true;
    }

    this->_visionStatusLocker.unlock();

    return ret;
}

bool Vision::setDetectionAlgorithm(std::string algorithmLabel)
{
    bool ret = false;

    this->_visionStatusLocker.lock();

    if (this->_detection)
        delete this->_detection;

    if (algorithmLabel == WHEREARE_LABEL) {
        this->_detection = new BlobDetection();
        this->_detection->init();
        ret = true;
    }

    this->_visionStatusLocker.unlock();
    return ret;
}

void Vision::setDetectionParam(std::string var, int value)
{
    this->_visionStatusLocker.lock();

    if (this->_detection)
        this->_detection->setUp(var,value);

    this->_visionStatusLocker.unlock();
}

void Vision::setTrackParam(std::string var, int value)
{
    this->_visionStatusLocker.lock();

    if (this->_tracking)
        this->_tracking->setUp(var,value);

    this->_visionStatusLocker.unlock();
}
void Vision::setDetectionParamFromXml()
{
    this->_visionStatusLocker.lock();

    if (this->_detection)
        this->_detection->init();

    this->_visionStatusLocker.unlock();
}

void Vision::setTrackParamFromXml()
{
    this->_visionStatusLocker.lock();

    if (this->_tracking)
        this->_tracking->init();

    this->_visionStatusLocker.unlock();
}

void Vision::getCorrectedDebugFrame(cv::Mat &frame)
{
    this->_visionStatusLocker.lock();

    if (this->_correction)
        this->_correction->getDebugFrame(frame);

    this->_visionStatusLocker.unlock();
}

void Vision::savePositionParam()
{
    this->_visionStatusLocker.lock();

    if (this->_detection)
        this->_detection->saveParam();

    if (this->_tracking)
        this->_tracking->saveParam();

    this->_visionStatusLocker.unlock();
}

void Vision::resetCorrection()
{
    this->_visionStatusLocker.lock();
    if (this->_correction)
        static_cast<WarpCorrection*>(this->_correction)->initFromFile(FIELDLIMITSPATH, &this->_convert);
    this->_visionStatusLocker.unlock();
}

void Vision::resetSegmentation()
{
    this->_visionStatusLocker.lock();

    if (this->_segmentation)
        static_cast<LUTSegmentation*>(this->_segmentation)->initFromFile(SEGMENTATION_DEFAULT_FILE);

    this->_visionStatusLocker.unlock();
}

void Vision::getSegmentationFrame(cv::Mat& frame)
{
    this->_visionStatusLocker.lock();

    if (this->_segmentation)
        this->_segmentation->getDebugFrame(frame);

    this->_visionStatusLocker.unlock();
}

void Vision::getDetectionFrame(cv::Mat& frame)
{
    this->_visionStatusLocker.lock();

    if (this->_detection)
        this->_detection->getDebugFrame(frame);

    this->_visionStatusLocker.unlock();
}

bool Vision::isCorrectionEnabled()
{
    this->_visionStatusLocker.lock();

    bool ret = this->_isCorrectionEnabled;

    this->_visionStatusLocker.unlock();

    return ret;
}

void Vision::setCorrection(bool enabled)
{
    this->_visionStatusLocker.lock();
    this->_isCorrectionEnabled = enabled;
    this->_visionStatusLocker.unlock();
}

bool Vision::isProcessingEnabled()
{
    this->_visionStatusLocker.lock();
    bool ret = this->_isProcessingEnabled;
    this->_visionStatusLocker.unlock();
    return ret;
}

void Vision::setProcessing(bool enabled)
{
    this->_visionStatusLocker.lock();
    this->_isProcessingEnabled = enabled;
    this->_visionStatusLocker.unlock();
}

int Vision::setColorIndex(int color, int index)
{
    this->_visionStatusLocker.lock();
    int ret = 0;
    if (this->_detection)
        ret = this->_detection->setColorIndex(color, index);
    this->_visionStatusLocker.unlock();
    return ret;
}

void Vision::setQuantizationBool(bool quantization)
{
    this->_visionStatusLocker.lock();
    if (this->_segmentation)
        static_cast<LUTSegmentation*>(this->_segmentation)->setQuantizationBool(quantization);
    this->_visionStatusLocker.unlock();
}

bool Vision::getQuantizationBool()
{
    this->_visionStatusLocker.lock();
    bool ret = false;
    if (this->_segmentation)
        ret = static_cast<LUTSegmentation*>(this->_segmentation)->getQuantizationBool();
    this->_visionStatusLocker.unlock();
    return ret;
}

std::vector<Entity> Vision::getRobotPositions()
{
    this->_visionStatusLocker.lock();
    std::vector<Entity> ret = this->_robotPositions;
    this->_visionStatusLocker.unlock();
    return ret;
}

void Vision::setTeamColor(int color)
{
    this->_visionStatusLocker.lock();
    this->_teamColor = color;
    this->_detection->setTeamColor(this->_teamColor);
    this->_visionStatusLocker.unlock();
}

int Vision::getTeamColor()
{
    this->_visionStatusLocker.lock();
    int ret = this->_teamColor;
    this->_visionStatusLocker.unlock();
    return ret;
}

void Vision::getCurrentFrame(cv::Mat& frame) {
  this->_currentFrameLocker.lock();
  this->_currentFrame.copyTo(frame);
  this->_currentFrameLocker.unlock();
}

void Vision::setDeepLogFileName(std::string fileName) {
    this->_visionStatusLocker.lock();
    this->_deepLogFilePath = fileName;

    this->_deepLogFileName = fileName.substr(
        std::max(0,(int)fileName.rfind('/')+1));
    this->_visionStatusLocker.unlock();
}

void Vision::setRecordingVideo(bool value) {
    this->_visionStatusLocker.lock();
    this->_deepLogRecordingVideo = value;
    this->_visionStatusLocker.unlock();
}

void Vision::closeDeepLog() {
    this->_visionStatusLocker.lock();
    if(this->_deepLogFile) fclose(this->_deepLogFile);
    this->_deepLogRecord = false;
    this->_visionStatusLocker.unlock();
}

void Vision::recordDeepLog() {
    this->_visionStatusLocker.lock();
    this->_deepLogRecord = true;
    this->_firstFrameDeepLog = true;
    this->_visionStatusLocker.unlock();
}

double Vision::getVisionRunTime() {
  this->_visionStatusLocker.lock();
  double ret = this->_visionRunTime;
  this->_visionStatusLocker.unlock();
  return ret;
}
