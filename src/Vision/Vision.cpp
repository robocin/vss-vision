#include "Vision.h"
#include <algorithm>
#include <vector>

Vision::Vision(Utils::HUE hueList)
{
    this->_detection = new BlobDetection();
    this->_detection->setTeamColor(getTeamColor());
    this->_segmentation = new MaggicSegmentation(hueList);
    this->_correction = new WarpCorrection();
    this->_compression = new RunLengthEncoding();
    this->_isCorrectionEnabled = false;
    this->_isProcessingEnabled = true;
    std::vector<Entity> currentPositions (7, Entity());
    this->_robotPositions = currentPositions;
    this->_currentFrame = cv::Mat::zeros(640,480,CV_8UC3);
    this->_firstFrameDeepLog = true;
    this->_deepLogFile = nullptr;
    this->_deepLogFileName = "log"; // default file name
    this->_deepLogFileFolder = "Log/deep/"; // default file folder
    this->_visionRunTime = 0;
}

Vision::~Vision()
{
    if (this->_detection)
        delete this->_detection;

    if (this->_segmentation)
        delete(this->_segmentation);
}

Vision& Vision::singleton(Utils::HUE hueList)
{
  static Vision instance(hueList);

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



cv::Mat Vision::update(cv::Mat &frame, Utils::FrameType frametype)
{
  this->setFrame(frame);
  this->update(frametype);
  std::vector<Entity> entities;
  entities.resize(1);
  entities[0] = vss.ball();
  Players players = vss.players();
  entities.insert(entities.end(),players.begin(),players.end());
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
void Vision::getCorrectedDebugFrame(cv::Mat &frame)
{

    if (this->_correction)
        this->_correction->getDebugFrame(frame);

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
  this->_currentFrame.copyTo(frame);
}

void Vision::setDeepLogFileName(std::string fileName) {
    this->_deepLogFilePath = fileName;

    this->_deepLogFileName = fileName.substr(
        std::max(static_cast<uint>(0),static_cast<uint>(fileName.rfind('/')+1)));
}

double Vision::getVisionRunTime() {
  double ret = this->_visionRunTime;
  return ret;
}
