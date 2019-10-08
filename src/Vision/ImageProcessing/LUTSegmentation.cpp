#include "LUTSegmentation.h"

LUTSegmentation::LUTSegmentation() {
  this->_LUT = new int[LUTSIZE];
  this->_calibrationParameters = new ColorInterval[NUMBEROFCOLOR];
  setQuantizationBool(false);
  this->_grayTrashHoldLevel = 0;
}

LUTSegmentation::~LUTSegmentation() {
  delete this->_LUT;
  delete this->_calibrationParameters;
}



void LUTSegmentation::init(std::map<std::string, int> parameters) {
  for (int i = 0; i < 11; i++) {
    this->_calibrationParameters[i].max.y = parameters[this->_colorLabels[i] + YMAXLABEL];
    this->_calibrationParameters[i].max.u = parameters[this->_colorLabels[i] + UMAXLABEL];
    this->_calibrationParameters[i].max.v = parameters[this->_colorLabels[i] + VMAXLABEL];
    this->_calibrationParameters[i].min.y = parameters[this->_colorLabels[i] + YMINLABEL];
    this->_calibrationParameters[i].min.u = parameters[this->_colorLabels[i] + UMINLABEL];
    this->_calibrationParameters[i].min.v = parameters[this->_colorLabels[i] + VMINLABEL];
  }

  this->initLUT();
}

void LUTSegmentation::setup(std::string parameter, int value) {
  for (int i = 0; i < NUMBEROFCOLOR; i++) {
    if (!parameter.compare(this->_colorLabels[i] + YMAXLABEL)) {
      this->_calibrationParameters[i].max.y = value;
    } else if (!parameter.compare(this->_colorLabels[i] + UMAXLABEL)) {
      this->_calibrationParameters[i].max.u = value;
    } else if (!parameter.compare(this->_colorLabels[i] + VMAXLABEL)) {
      this->_calibrationParameters[i].max.v = value;
    } else if (!parameter.compare(this->_colorLabels[i] + YMINLABEL)) {
      this->_calibrationParameters[i].min.y = value;
    } else if (!parameter.compare(this->_colorLabels[i] + UMINLABEL)) {
      this->_calibrationParameters[i].min.u = value;
    } else if (!parameter.compare(this->_colorLabels[i] + VMINLABEL)) {
      this->_calibrationParameters[i].min.v = value;
    }
  }

  this->initLUT();
}

cv::Mat LUTSegmentation::run(cv::Mat &frame) {
  cv::Mat debugFrame = cv::Mat::zeros(frame.rows, frame.cols, frame.type());
  cv::Mat returnFrame = cv::Mat::zeros(frame.rows, frame.cols, CV_8U);
  uchar cutBitsDecimal = 15;
  this->_quantizationLock.lock();
  tbb::parallel_for(tbb::blocked_range2d<int>(0, frame.rows, 238, 0, frame.cols, 161),
    [&](const tbb::blocked_range2d<int> &r) {
      for (int i = r.rows().begin(); i != r.rows().end(); i++) {
        RGB *row = frame.ptr<RGB>(i);

        for (int j = r.cols().begin(); j != r.cols().end(); j++) {
          if (this->_quantization) {
            row[j].red  = row[j].red | cutBitsDecimal;
            row[j].green = row[j].green | cutBitsDecimal;
            row[j].blue = row[j].blue | cutBitsDecimal;
          }

          int label = this->_LUT[(row[j].red << 16) + (row[j].green << 8) + row[j].blue];
          //std::cout << "Lut Segmentation [" << (int) label << "] = {" << (int) row[j].red << ", " << (int) row[j].green << ", " << (int) row[j].blue << "}" << std::endl;
          debugFrame.ptr<RGB>(i)[j] = ColorSpace::markerColors[label];
          returnFrame.ptr<uchar>(i)[j] = label;
        }
      }
    }
  );
  this->_quantizationLock.unlock();
  this->_frameLock.lock();
  debugFrame.copyTo(this->_segmentationFrame);
  this->_frameLock.unlock();
  return returnFrame;
}

void LUTSegmentation::initLUT() {
  int index;
  YUV color;

  for (int r = 0; r < 256; r++) {
    for (int g = 0; g < 256; g++) {
      for (int b = 0; b < 256; b++) {
        index = r * 65536 + g * 256 + b;

        if (abs(r - g) < this->_grayTrashHoldLevel
            && abs(r - b) < this->_grayTrashHoldLevel
            && abs(b - g) < this->_grayTrashHoldLevel) {
          this->_LUT[index] = NoCOL;
        } else {
          color.y = Utils::bound((306 * r + 601 * g + 117 * b) >> 10, 0, 255);
          color.u = Utils::bound(((-172 * r - 340 * g + 512 * b) >> 10) + 128, 0, 255);
          color.v = Utils::bound(((512 * r - 419 * g - 83 * b) >> 10) + 128, 0, 255);
          this->_LUT[index] = this->getColorLabel(color);
        }
      }
    }
  }
}

void LUTSegmentation::getDebugFrame(cv::Mat& frame) {
  this->_frameLock.lock();
  this->_segmentationFrame.copyTo(frame);
  this->_frameLock.unlock();
}

void LUTSegmentation::setLUTPixel(YUV &color, int id) {
  if (id < LUTSIZE) {
    this->_LUT[id] = this->getColorLabel(color);
  }
}

int LUTSegmentation::getColorLabel(YUV &color) {
  for (int i = 0; i < NUMBEROFCOLOR; i++) {
    if (color.y >= this->_calibrationParameters[i].min.y
        && color.y <= this->_calibrationParameters[i].max.y) {
      if (color.u >= this->_calibrationParameters[i].min.u
          && color.u <= this->_calibrationParameters[i].max.u) {
        if (color.v >= this->_calibrationParameters[i].min.v
            && color.v <= this->_calibrationParameters[i].max.v) {
          return i;
        }
      }
    }
  }

  return NoCOL;
}

void LUTSegmentation::initFromFile(std::string path) {
  cv::FileStorage fs(path, cv::FileStorage::READ);

  if (!fs.isOpened()) {
    spdlog::get("Vision")->error("LUTSegmentation::initFromFile: Diretorio não encontrado {}", path);
  }

  cv::FileNode n;
  n = fs[OPENCV_STORAGE];
  this->_grayTrashHoldLevel = (int)n[GRAY_SCALE];

  for (int i = 0; i < NUMBEROFCOLOR; i++) {
    n = fs[this->_colorLabels[i]];
    this->_calibrationParameters[i].max.y = (int) n[YMAXLABEL];
    this->_calibrationParameters[i].max.u = (int) n[UMAXLABEL];
    this->_calibrationParameters[i].max.v = (int) n[VMAXLABEL];
    this->_calibrationParameters[i].min.y = (int) n[YMINLABEL];
    this->_calibrationParameters[i].min.u = (int) n[UMINLABEL];
    this->_calibrationParameters[i].min.v = (int) n[VMINLABEL];
  }

  fs.release();
  this->initLUT();
}

void LUTSegmentation::setQuantizationBool(bool quantization) {
    this->_quantizationLock.lock();
    this->_quantization = quantization;
    this->_quantizationLock.unlock();
}

bool LUTSegmentation::getQuantizationBool() {
  this->_quantizationLock.lock();
  bool ret = this->_quantization;
  this->_quantizationLock.unlock();
  return ret;
}


int *LUTSegmentation::getLUT() {
  return this->_LUT;
}
