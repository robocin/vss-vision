#include "Vision.h"
#include "Network/Network.h"
#include <algorithm>
#include <vector>

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
    this->_isProcessingEnabled = true;
    std::vector<Entity> currentPositions (7, Entity());
    this->_robotPositions = currentPositions;
    this->_currentFrame = cv::Mat::zeros(640,480,CV_8UC3);
    this->_lastPositions = std::vector<std::queue<std::pair<cv::Point2d,QTime>>>(7);
    this->_firstFrameDeepLog = true;
    this->_deepLogFile = nullptr;
    this->_deepLogFileName = "log"; // default file name
    this->_deepLogFileFolder = "Log/deep/"; // default file folder
    this->_deepLogRecordingVideo = false;
    this->_visionRunTime = 0;
    this->firstTime = QTime::currentTime();
    this->server = new VisionServer("224.5.23.2", 10015);
//    this->_visionStatusLocker.unlock();
}

Vision::~Vision()
{
    if (this->_detection)
        delete this->_detection;

    if (this->_segmentation)
        delete(this->_segmentation);
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
    Point ret = _frameDimensions;
    return ret;
}

void Vision::update(Utils::FrameType frametype)
{
    Global::setConvertRatio(_convert);
    
    this->_processingFrame = this->_currentFrame.clone();


    if (this->_isProcessingEnabled) {

        this->_processingFrame = this->_segmentation->run(this->_processingFrame);

        if(frametype == Utils::FrameType::Tracked){
            auto _runs = this->_compression->run(this->_processingFrame);
            saveFrameDimensions(this->_processingFrame);
            this->_detection->run(_runs, this->_processingFrame.rows, this->_processingFrame.cols);
            
            cv::Mat frameAux, frameAux2;
            getCurrentFrame(frameAux);
            getDetectionFrame(frameAux2);
            cv::resize(frameAux2, frameAux2, frameAux.size());
            cv::Mat aux = vss.frameCopy();
            vss.clearFrame();
            cv::resize(aux, aux, frameAux2.size());
            this->output_frame = frameAux + frameAux2 + aux;
            
        }else if(frametype == Utils::FrameType::Segmented){
            cv::Mat frameAux2;
            getSegmentationFrame(frameAux2);
            this->output_frame = frameAux2;
        }
    }
}



cv::Mat Vision::update(cv::Mat &frame, QTime timeStamp, Utils::FrameType frametype)
{
  this->_visionFrameTimer.start();
  this->setFrame(frame);
  this->update(frametype);
  uint32_t actualTime = static_cast<uint32_t>(this->firstTime.msecsTo(timeStamp));
  //printf("%u\n", actualTime);
  std::vector<Entity> entities;
  entities.resize(1);
  entities[0] = vss.ball();
  Players players = vss.players();
  entities.insert(entities.end(),players.begin(),players.end());
  
    // NETWORK
    if (this->_isProcessingEnabled) {
        //spdlog::get("Vision")->info("update:: Seding frame.\n");
        // Network::sendFrame(entities, actualTime);
        // this->server->send(entities);

        //spdlog::get("Vision")->info("update:: Frame sent.\n");
    } else {
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
      uint ini = actualTime;
      ss << this->_deepLogFilePath << "_" << timeStamp.hour() << "." << timeStamp.minute() << "." << timeStamp.second() << ".csv";
      std::cout << "Creating file " << ss.str() << std::endl;
      this->_deepLogFile = fopen(ss.str().c_str(),"w");
      if (this->_deepLogFile) {
        this->_firstFrameDeepLog = false;
        this->_deepLogInitialTime = ini;

        // fprintf(this->_deepLogFile,"ID_VIDEO;TIMESTAMP_INITIAL;ID_ROBO1;ID_ROBO2;ID_ROBO3\n");
        // fprintf(this->_deepLogFile,"%s;%d;%d;%d;%d\n",this->_deepLogFileName.c_str(),this->_deepLogInitialTime, entities[ROBOT1].id(), entities[ROBOT2].id(), entities[ROBOT3].id());
        // fprintf(this->_deepLogFile,"R1X;R1Y;R1T;R2X;R2Y;R2T;R3X;R3Y;R3T;A1X;A1Y;A1T;A2X;A2Y;A2T;A3X;A3Y;A3T;BX;BY;TIMESTAMP_FRAME\n");

      }

    }

    if (this->_deepLogFile) {
      // any other frame
      // fprintf(this->_deepLogFile,"%lf;%lf;%lf;", entities[ROBOT1].position().x, entities[ROBOT1].position().y, entities[ROBOT1].angle());
      // fprintf(this->_deepLogFile,"%lf;%lf;%lf;", entities[ROBOT2].position().x, entities[ROBOT2].position().y, entities[ROBOT2].angle());
      // fprintf(this->_deepLogFile,"%lf;%lf;%lf;", entities[ROBOT3].position().x, entities[ROBOT3].position().y, entities[ROBOT3].angle());

      // fprintf(this->_deepLogFile,"%lf;%lf;%lf;", entities[ADV1].position().x, entities[ADV1].position().y, entities[ADV1].angle());
      // fprintf(this->_deepLogFile,"%lf;%lf;%lf;", entities[ADV2].position().x, entities[ADV2].position().y, entities[ADV2].angle());
      // fprintf(this->_deepLogFile,"%lf;%lf;%lf;", entities[ADV3].position().x, entities[ADV3].position().y, entities[ADV3].angle());

      // fprintf(this->_deepLogFile,"%lf;%lf;%lf", entities[BALL].position().x, entities[BALL].position().y, entities[BALL].angle());
      // fprintf(this->_deepLogFile,"%u\n", actualTime - this->_deepLogInitialTime);
    }

   }
   this->_visionFrameTimer.stop();
   this->_visionRunTime = static_cast<double> (this->_visionFrameTimer.getMilliseconds()*0.2 + this->_visionRunTime*0.8);

   return this->output_frame;
}

void Vision::getSegmentationDebugFrame(cv::Mat& frame)
{
    if (this->_segmentation)
        this->_segmentation->getDebugFrame(frame);
}

void Vision::getDetectionDebugFrame(cv::Mat& frame)
{
    if (this->_detection)
        this->_detection->getDebugFrame(frame);
}

void Vision::getTrackingDebugFrame(cv::Mat& frame)
{
    if (this->_tracking)
        this->_tracking->getDebugFrame(frame);
}

ImageProcessing* Vision::getSegmentationObject() {
    ImageProcessing* ret = this->_segmentation;
    return ret;
}

bool Vision::setTrackingAlgorithm(std::string algorithmLabel)
{
    bool ret = false;


    if (this->_tracking)
        delete this->_tracking;

    if (algorithmLabel == GENERIC_TRACKING_LABEL) {
        //this->_tracking = new Generic();
        ret = true;
    }


    return ret;
}

bool Vision::setDetectionAlgorithm(std::string algorithmLabel)
{
    bool ret = false;


    if (this->_detection)
        delete this->_detection;

    if (algorithmLabel == WHEREARE_LABEL) {
        this->_detection = new BlobDetection();
        this->_detection->init();
        ret = true;
    }

    return ret;
}

void Vision::setDetectionParam(std::string var, int value)
{
    if (this->_detection)
        this->_detection->setUp(var,value);

}

void Vision::setTrackParam(std::string var, int value)
{

    if (this->_tracking)
        this->_tracking->setUp(var,value);

}
void Vision::setDetectionParamFromXml()
{

    if (this->_detection)
        this->_detection->init();

}

void Vision::setTrackParamFromXml()
{

    if (this->_tracking)
        this->_tracking->init();

}

void Vision::getCorrectedDebugFrame(cv::Mat &frame)
{

    if (this->_correction)
        this->_correction->getDebugFrame(frame);

}

void Vision::savePositionParam()
{

    if (this->_detection)
        this->_detection->saveParam();

    if (this->_tracking)
        this->_tracking->saveParam();

}

void Vision::resetCorrection()
{
    if (this->_correction)
        static_cast<WarpCorrection*>(this->_correction)->initFromFile(FIELDLIMITSPATH, &this->_convert);
}

void Vision::resetSegmentation()
{

    if (this->_segmentation)
        static_cast<LUTSegmentation*>(this->_segmentation)->initFromFile(SEGMENTATION_DEFAULT_FILE);

}

void Vision::getSegmentationFrame(cv::Mat& frame)
{

    if (this->_segmentation)
        this->_segmentation->getDebugFrame(frame);

}

void Vision::getDetectionFrame(cv::Mat& frame)
{

    if (this->_detection)
        this->_detection->getDebugFrame(frame);

}

bool Vision::isCorrectionEnabled()
{

    bool ret = this->_isCorrectionEnabled;


    return ret;
}

void Vision::setCorrection(bool enabled)
{
    this->_isCorrectionEnabled = enabled;
}

bool Vision::isProcessingEnabled()
{
    bool ret = this->_isProcessingEnabled;
    return ret;
}

void Vision::setProcessing(bool enabled)
{
    this->_isProcessingEnabled = enabled;
}

int Vision::setColorIndex(int color, int index)
{
    int ret = 0;
    if (this->_detection)
        ret = this->_detection->setColorIndex(color, index);
    return ret;
}

void Vision::setQuantizationBool(bool quantization)
{
    if (this->_segmentation)
        static_cast<LUTSegmentation*>(this->_segmentation)->setQuantizationBool(quantization);
}

bool Vision::getQuantizationBool()
{
    bool ret = false;
    if (this->_segmentation)
        ret = static_cast<LUTSegmentation*>(this->_segmentation)->getQuantizationBool();
    return ret;
}

std::vector<Entity> Vision::getRobotPositions()
{
    std::vector<Entity> ret = this->_robotPositions;
    return ret;
}

void Vision::setTeamColor(int color)
{
    this->_teamColor = color;
    this->_detection->setTeamColor(this->_teamColor);
}

int Vision::getTeamColor()
{
    int ret = this->_teamColor;
    return ret;
}

void Vision::getCurrentFrame(cv::Mat& frame) {
  this->_currentFrameLocker.lock();
  this->_currentFrame.copyTo(frame);
  this->_currentFrameLocker.unlock();
}

void Vision::setDeepLogFileName(std::string fileName) {
    this->_deepLogFilePath = fileName;

    this->_deepLogFileName = fileName.substr(
        std::max(static_cast<uint>(0),static_cast<uint>(fileName.rfind('/')+1)));
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
  double ret = this->_visionRunTime;
  return ret;
}
