#include "MaggicSegmentation.h"
#if CV_MAJOR_VERSION == 2
  #include "Vision/ImageProcessing/OpenCV/connectedcomponents.hpp"
#endif
//#include <omp.h>

#define LUT_SIZE 16777216*3

//#define USE_CUDA
#ifdef USE_CUDA

#include "Vision/ImageProcessing/Cuda/LUT/lut_gpu.h"
#include "Vision/ImageProcessing/Cuda/LUT/Utils.h"

#define LUT_SECOND_SIZE 65536

extern int makeLUTGPU(uint size);
extern int getLUTFromGPU(uchar *c, uint size);

uchar *LUT_GPU_V = NULL;

// Prepare memory in GPU for LUT
void PREPARE_LUT_GPU() {
  initGPU(LUT_SIZE);
}

// Make calculations to LUT
void LUT_GPU() {
  makeLUTGPU(LUT_SIZE/3);
}

void GET_LUT_GPU_DATA() {
  getLUTFromGPU(LUT_GPU_V, LUT_SIZE);
}
void FINISH_LUT_GPU() {
  releaseGPU();
}

void APPLY_LUT_GPU(cv::Mat &mat) {
  applyLUTGPU(mat.data, mat.cols*mat.rows);
}

#endif

MaggicSegmentation::MaggicSegmentation()
{
  this->isLUTReady = false;
  this->_LUT = new int[LUT_SIZE/3];
  memset(this->_LUT,0,LUT_SIZE/3  *sizeof(int)); // clear _LUT
  this->_HUETable = new int[256];
  memset(this->_HUETable,0,256*sizeof(int)); // clear HUETable
  this->_calibrationParameters = new ColorInterval[NUMBEROFCOLOR];

  colorPalette = cv::Mat::zeros(1, 10, CV_8UC3);
  colorPalette.at<cv::Vec3b>(0, 0) = cv::Vec3b(0, 255, 255); // No Color
  colorPalette.at<cv::Vec3b>(0, 1) = cv::Vec3b(0, 69, 255); // Laranja
  colorPalette.at<cv::Vec3b>(0, 2) = cv::Vec3b(255, 47, 0); // Azul
  //colorPalette.at<cv::Vec3b>(0, 2) = cv::Vec3b(255, 27, 0); // Azul new
  colorPalette.at<cv::Vec3b>(0, 3) = cv::Vec3b(0, 255, 255); // Amarelo
  colorPalette.at<cv::Vec3b>(0, 4) = cv::Vec3b(0, 0, 255); // Vermelho
  colorPalette.at<cv::Vec3b>(0, 5) = cv::Vec3b(0, 255, 0); // Verde
  //colorPalette.at<cv::Vec3b>(0, 5) = cv::Vec3b(168, 255, 0); // Verde new
  colorPalette.at<cv::Vec3b>(0, 6) = cv::Vec3b(147, 20, 255); // Rosa
  //colorPalette.at<cv::Vec3b>(0, 7) = cv::Vec3b(250, 206, 135); // Azul Claro
  colorPalette.at<cv::Vec3b>(0, 7) = cv::Vec3b(252, 252, 119); // Azul Claro que bugava com verde- ou verde
  //colorPalette.at<cv::Vec3b>(0, 7) = cv::Vec3b(252, 197, 119); // Azul Claro bom
  //colorPalette.at<cv::Vec3b>(0, 2) = cv::Vec3b(255, 180, 90); // Azul escuro teste

  //colorPalette.at<cv::Vec3b>(0, 7) = cv::Vec3b(252, 208, 0); // Azul Claro melhor
  colorPalette.at<cv::Vec3b>(0, 8) = cv::Vec3b(128, 0, 128); // Roxo
  colorPalette.at<cv::Vec3b>(0, 9) = cv::Vec3b(0, 0, 128); // Marrom

  cv::cvtColor(colorPalette, colorPaletteYUV, cv::COLOR_BGR2YUV);
  cv::cvtColor(colorPalette, colorPaletteHSV, cv::COLOR_BGR2HSV_FULL);

  this->loadDefaultHue();
  this->setHUETable();
  this->generateLUTFromHUE();
  /*puts("COLOR PALETTE\nHUE(f) TAG");
  defaultHueList.clear();
  for(int i=1;i<8;i++) {
    int h = (int)colorPaletteHSV.at<cv::Vec3b>(0,i)[0];
    float hf = (float) h/255.f;
    defaultHueList.push_back(std::make_pair(hf,i));
    printf("%d(%.2f) %d\n", h, hf, i);
  }
  puts("\n\n");*/
  //colorPaletteHSV.at<cv::Vec3b>(0, 0)[0] += 10;
  //colorPaletteHSV.at<cv::Vec3b>(0, 4)[0] = (colorPaletteHSV.at<cv::Vec3b>(0, 4)[0])%256;



  // constructing color palette

  cv::Mat cores = cv::Mat::zeros(cv::Size(32+32,32*10), CV_8UC3);
  cv::Mat compara = cv::Mat::zeros(cv::Size(512,20), CV_8UC3);
  cv::Mat colorPlane = cv::Mat::zeros(cv::Size(512,512), CV_8UC3);

  //std::cout << "Cores from color palette HSV" << std::endl;

  for (int i=0;i<256;i++) {
    for(int j=0;j<256;j++) {
      cv::rectangle(colorPlane,cv::Rect(j << 1,i << 1,2,2),cv::Scalar(j,255,i),-1);
    }
  }
  for(int i=0;i<10;++i) {
    cv::Vec3b vec = colorPaletteHSV.at<cv::Vec3b>(0,i);
    float e = static_cast<float>(vec[0]);
     // std::cout << e << std::endl;
    cv::rectangle(cores,cv::Rect(32,i*32,32,32),cv::Scalar(e,255,255),-1);
    cv::rectangle(cores,cv::Rect(0,i*32,32,32),cv::Scalar(vec),-1);
    cv::line(compara,cv::Point((int)e << 1,0),cv::Point((int)e << 1,20),cv::Scalar(vec),2);

    cv::circle(colorPlane,cv::Point(vec[0] << 1,vec[2] << 1),5,cv::Scalar(255,0,255),-1);
  }

  cv::cvtColor(cores, cores, cv::COLOR_HSV2BGR_FULL);
  cv::cvtColor(compara, compara, cv::COLOR_HSV2BGR_FULL);
  cv::cvtColor(colorPlane, colorPlane, cv::COLOR_HSV2BGR_FULL);
  //cv::imshow("colorPalette", cores);
  //cv::imshow("compara", compara);
  //cv::imshow("colorPlane", colorPlane);





//  SetColorPalette(colorPaletteHSV);

  this->histo = cv::Mat::zeros(cv::Size(256, 1), CV_32F);

  this->paused = false;
  this->enableEstimateRobots = true;
  this->normalized_color = true;
  this->_manyTimes = 6;
  this->_entitiesCount = 7;
  this->_debugSelection = MaggicVisionDebugSelection_Thresholded;
  memset(this->_thresholdFrequency,0,256*sizeof(uint));
  this->_learningThresholdValue = false;
  this->_calibrationFrames = 0;
  this->_learningThresholdFrames = 120;

  this->_segmentationFrame = cv::Mat::zeros(1,1,CV_8UC3);
  this->_multipliedResults = cv::Mat::zeros(1,1,CV_8UC3);
  this->_extremeSaturation = cv::Mat::zeros(1,1,CV_8UC3);
  this->_firstThreshold = cv::Mat::zeros(1,1,CV_8UC3);


  this->_maggicSegmentationSessionFileName = "Config/Segmentation/MaggicSegmentation.txt";

  //std::cout << "THRESHOLD FROM MAGGIC SEGMENTATION ON CONSTRUCTING" << this->getFilterGrayThresholdValue() << std::endl;

  //this->openLastSession();

  //std::cout << "THRESHOLD FROM MAGGIC SEGMENTATION ON CONSTRUCTING AFTER " << this->getFilterGrayThresholdValue() << std::endl;

}

MaggicSegmentation::~MaggicSegmentation()
{
#ifdef USE_CUDA
  delete LUT_GPU_V;
  FINISH_LUT_GPU();
#endif
  delete this->_LUT;
  delete this->_HUETable;
  delete this->_calibrationParameters;
}

void MaggicSegmentation::openLastSession() {
  //std::cout << "Opening last session on MaggicSegmentation" << std::endl;
  std::string str;
  std::ifstream fin;
  int numa, numb;
  fin.open(this->_maggicSegmentationSessionFileName);

  if (fin.is_open()) {
    fin >> str;
    //std::cout << "STR : '" << str << "'" << std::endl;
    if (str.compare("Maggic") == 0) {// Test if the files has any valid content, then read it all
      fin >> this->_minimumGrayThreshold >>  this->_maximumGrayThreshold;
      fin >> this->filterGrayThreshold;
      //std::cout << "THRESHOLD FROM MAGGIC SEGMENTATION FROM OPEN" << this->filterGrayThreshold << std::endl;
      this->hueList.clear();
      // read all the number's pairs
      while(true) {
        fin >> numa >> numb;
        //std::cout << "numa numb " << numa << " " << numb << std::endl;
        if (fin.eof()) break;
        this->hueList.push_back(std::make_pair((float)numa,(int)numb));
      }
    }
    this->setHUETable(true);
    this->generateLUTFromHUE();
    this->useLoadedValues = true;
  } else {
    this->useLoadedValues = false;
    spdlog::get("Vision")->info("MaggicSegmentation::openFromLastSession: Arquivo não encontrado {}",this->_maggicSegmentationSessionFileName);
  }

  fin.close();
}

void MaggicSegmentation::saveSession() {
  std::string str;
  std::ofstream fout;
  fout.open(this->_maggicSegmentationSessionFileName);
  // write all the number's pairs
  if (fout.is_open()) {
     std::cout << "Opened " << this->_maggicSegmentationSessionFileName << std::endl;
     fout << "Maggic\n";
     fout << this->_minimumGrayThreshold << " " << this->_maximumGrayThreshold << "\n";
     fout << this->getFilterGrayThresholdValue() << "\n";
     for(size_t i=0;i<this->hueList.size();i++) {
      fout << (int)this->hueList[i].first << " " << (int)this->hueList[i].second << "\n";
     }

  } else {
     spdlog::get("Vision")->error("MaggicSegmentation::saveSession: Acesso negado ao arquivo {}",this->_maggicSegmentationSessionFileName);
  }
  fout.close();
}

void MaggicSegmentation::init(std::map<std::string, int> paramaters)
{
  for (int i = 0; i < 11; i++) {

     this->_calibrationParameters[i].max.y = paramaters[this->_colorLabels[i]+YMAXLABEL];
     this->_calibrationParameters[i].max.u = paramaters[this->_colorLabels[i]+UMAXLABEL];
     this->_calibrationParameters[i].max.v = paramaters[this->_colorLabels[i]+VMAXLABEL];

     this->_calibrationParameters[i].min.y = paramaters[this->_colorLabels[i]+YMINLABEL];
     this->_calibrationParameters[i].min.u = paramaters[this->_colorLabels[i]+UMINLABEL];
     this->_calibrationParameters[i].min.v = paramaters[this->_colorLabels[i]+VMINLABEL];

  }

  this->initLUT();
}

void MaggicSegmentation::setup(std::string parameter, int value)
{

  for (int i = 0; i < NUMBEROFCOLOR; i++) {

    if (!parameter.compare(this->_colorLabels[i]+YMAXLABEL)) {

      this->_calibrationParameters[i].max.y = value;

    } else if (!parameter.compare(this->_colorLabels[i]+UMAXLABEL)) {

      this->_calibrationParameters[i].max.u = value;

    } else if (!parameter.compare(this->_colorLabels[i]+VMAXLABEL)) {

      this->_calibrationParameters[i].max.v = value;

    } else if (!parameter.compare(this->_colorLabels[i]+YMINLABEL)) {

      this->_calibrationParameters[i].min.y = value;

    } else if (!parameter.compare(this->_colorLabels[i]+UMINLABEL)) {

      this->_calibrationParameters[i].min.u = value;

    } else if (!parameter.compare(this->_colorLabels[i]+VMINLABEL)) {

      this->_calibrationParameters[i].min.v = value;

    }

  }

  this->initLUT();
}


void MaggicSegmentation::calibrate(cv::Mat &frame) {
  if (!paused) {
    frame.copyTo(this->_imageBuffer);
    this->_calibrationFrames++;
  }


  cv::Mat &image = this->_imageBuffer;
  //imwrite("robocin.png",image);

  if (this->_calibrationFrames > this->_learningThresholdFrames) {
    this->setLearningThresholdValue(false);
    updateFilterGrayThresholdValue();
  }
enableEstimateRobots = !(this->_debugSelection == MaggicVisionDebugSelection_DetailsFrame && this->paused);
this->_manyTimes = 1;
this->_entitiesCount = 7;
  if (enableEstimateRobots) estimateRobots(image,this->_manyTimes, this->_entitiesCount);
  doDetails();

  /*switch(this->_debugSelection) {
    case MaggicVisionDebugSelection_Thresholded:
      this->_segmentationFrame = this->_firstThreshold.clone();
    break;
    case MaggicVisionDebugSelection_ExtremeSaturation:
      this->_segmentationFrame = this->_extremeSaturation.clone();
    break;
    case MaggicVisionDebugSelection_MultipliedResults:
      this->_segmentationFrame = this->_multipliedResults.clone();
    break;
    default:
      this->_segmentationFrame = cv::Mat::zeros(1,1,CV_8UC3);

  }*/

}

void MaggicSegmentation::setDebugSelection(MaggicVisionDebugSelection selection) {
  this->_debugSelection = selection;
}


void MaggicSegmentation::setManyTimes(int manyTimes) {
  if (manyTimes > 0) this->_manyTimes = manyTimes;
}

void MaggicSegmentation::setEntitiesCount(int entitiesCount) {
  if (entitiesCount > 0 && entitiesCount < 8) this->_entitiesCount = entitiesCount;
}

int MaggicSegmentation::getEntitiesCount() {
  return this->_entitiesCount;
}

void MaggicSegmentation::filterGray(cv::Mat &d, cv::Mat &o) {
  cv::Mat res = cv::Mat::zeros(d.size(), d.type());


  for (int r = 0; r < o.rows; ++r) {
    for (int c = 0; c < o.cols; ++c) {
      cv::Vec3b coloro = o.at<cv::Vec3b>(r, c);
      cv::Vec3b color;
      //if (abs(coloro[0] - coloro[1]) < thre && abs(coloro[1] - coloro[2]) < thre && abs(coloro[2] - coloro[0]) < thre) {
      if (normalized_color) {
        float x = coloro[0];
        float y = coloro[1];
        float z = coloro[2];
        x *= x;
        y *= y;
        z *= z;
        float a = 1.f / (float)sqrt(x + y + z);
        coloro[0] = (uchar)(x*a);
        coloro[1] = (uchar)(y*a);
        coloro[2] = (uchar)(z*a);
      }
      /*float dx = coloro[0] - coloro[1];
      float dy = coloro[1] - coloro[2];
      float dz = coloro[2] - coloro[0];
      if (filterGrayThreshold*filterGrayThreshold > dx*dx + dy*dy + dz*dz) {*/
      float x = coloro[0];
      float y = coloro[1];
      float z = coloro[2];
      float men = min(min(x, y), z);
      float x1 = max(men - filterGrayThreshold, 0);
      float y1 = max(men - filterGrayThreshold, 0);
      float z1 = max(men - filterGrayThreshold, 0);
      float x2 = min(men + filterGrayThreshold, 255);
      float y2 = min(men + filterGrayThreshold, 255);
      float z2 = min(men + filterGrayThreshold, 255);
      if (x >= x1 && x <= x2 &&
        y >= y1 && y <= y2 &&
        z >= z1 && z <= z2) {

      }
      else {
        color = coloro;
      }
      res.at<cv::Vec3b>(r, c) = color;
    }
  }

  d = res;
}

void MaggicSegmentation::filterBinarizeColored(cv::Mat &d, cv::Mat &o) {
  cv::Mat res = cv::Mat::zeros(d.size(), CV_8UC1);

  for (int r = 0; r < o.rows; ++r) {
    for (int c = 0; c < o.cols; ++c) {
      cv::Vec3b coloro = o.at<cv::Vec3b>(r, c);
      if (coloro[0] == 0 && coloro[1] == 0 && coloro[2] == 0)	res.at<cv::Vec3b>(r, c) = 0;
      else res.at<uchar>(r, c) = 255;
    }
  }

  d = res;
}

void MaggicSegmentation::filterExtremeSaturation(cv::Mat &d, cv::Mat &o) {
    cv::Mat res = cv::Mat::zeros(d.size(), d.type());

    for (int r = 0; r < o.rows; ++r) {
      for (int c = 0; c < o.cols; ++c) {
        cv::Vec3b color = o.at<cv::Vec3b>(r, c);
        color[2] = (uchar)255;
        res.at<cv::Vec3b>(r, c) = color;
      }
    }

    d = res;
  }

void MaggicSegmentation::updateHistogramDescriptors() {
  int last = 0;
  colorDescriptors.clear();

  for (int jj = 1; jj < 256; ++jj) {
    if (histo.at<float>(0, jj) > 0.1f) {
      if (histo.at<float>(0, jj - 1) < histo.at<float>(0, jj)) {
        last = jj;
      }
      else {
        colorDescriptors.push_back(last*div255);
      }
    }
  }
  if (colorDescriptors.size() == 0 || colorDescriptors.back() != last) colorDescriptors.push_back(last*div255);
}

void MaggicSegmentation::filterGrain(ColorDescriptor &dest, ColorDescriptor &orig) {
  if (orig.size() == 0) return;
  const float grainThreshold = 17.f / 255.f;

  dest.clear();
  float first = orig[0];

  if (orig.size() == 1) {
    dest.push_back(first);
    return;
  }
  else if (orig.size() == 2) {
    if (orig[1] - orig[0] > grainThreshold) {
      dest.push_back(orig[0]);
      dest.push_back(orig[1]);
    }
    else dest.push_back((orig[1] + orig[0])*0.5f);
    return;
  }

  for (size_t i = 1; i < orig.size(); ++i) {
    if (orig[i] - orig[i - 1] > grainThreshold) {
      dest.push_back((orig[i - 1] + first)*0.5f);
      first = orig[i];
    }
  }
  if (orig[orig.size() - 1] - orig[orig.size() - 2] < grainThreshold) {
    dest.push_back(orig[orig.size() - 1]);
  }
  if (dest.size() == 0) {
    dest.push_back((orig[0] + orig[orig.size()-1])*0.5f);
  }
}

void MaggicSegmentation::_layeredAdd(cv::Mat &out, cv::Mat imgA, cv::Mat imgB) {
  CV_Assert(imgA.cols == imgB.cols && imgA.rows == imgB.rows && imgA.channels() == imgB.channels() && imgA.channels()==3);

  for (int i = 0; i < imgA.cols*imgA.rows*imgA.channels(); ++i) {
    int pixel = (i / imgA.channels())*3;
    int pixel1 = pixel + 1;
    int pixel2 = pixel + 2;
    if (imgB.data[pixel] == 0 && imgB.data[pixel1] == 0 && imgB.data[pixel2] == 0) {
      out.data[pixel] = imgA.data[pixel];
      out.data[pixel1] = imgA.data[pixel1];
      out.data[pixel2] = imgA.data[pixel2];
    }
    else {
      out.data[pixel] = imgB.data[pixel];
      out.data[pixel1] = imgB.data[pixel1];
      out.data[pixel2] = imgB.data[pixel2];
    }
  }
}

void MaggicSegmentation::setHUETable(bool fromFile) {
  this->isLUTReady = false;

  if (!fromFile) {// if it's not from file run normally

    //std::cout << "Loading default hue list" << std::endl;
    spdlog::get("Vision")->info("MaggicSegmentation::Loading default hue list\n");

    // clear the vector of pair
    hueList.clear();

    // get all default color palette into hueList
    //puts("setting hue table");
    for(int i=0;i<defaultHueList.size();i++) {
      float hueChannel = defaultHueList[i].first*255.0f;
      //printf("%.0f %d\n", hueChannel, defaultHueList[i].second);
      hueList.push_back(std::make_pair(hueChannel,defaultHueList[i].second));
    }


    // get all color descriptors into hueList
    for(int i=1;i<8;i++) {
      ColorDescriptor &colors = this->robotsDescriptors[i].colors;
      for (size_t j=0;j<colors.size();j++) {
        float hueChannel = colors[j]*255.f;
        float bd = 1000.f;
        int bid = 0;
        for (int k=0;k<defaultHueList.size();k++) {
          //float d = fabs(colorPaletteHSV.at<cv::Vec3b>(0,k)[0] - hueChannel);
          float x = defaultHueList[k].first*255.0f;
          float y = hueChannel;
          float d = min(fabs(x- y),min(fabs((256 + x) - y), fabs(x - y-256)));
          if (d < bd) {
            bd = d;
            bid = defaultHueList[k].second;
          }
        }
        hueList.push_back(std::make_pair(hueChannel, (int)bid));
      }
    }

  }


  std::sort(hueList.begin(),hueList.end());

  for(int i = 0; i < 256;i++) {
    int bd = 1000;
    int bl = 0;

    for (size_t j=0;j<hueList.size();j++) {
      int l = hueList[j].second;
      int x = hueList[j].first;
      int d = min(abs(x- i),min(abs((256 + x) - i), abs(x - i-256)));

      if (d < bd) {
        bd = d;
        bl = l;
      }

    }
     // std::cout << i << " " << _colorLabels[bl] << std::endl;
    this->_HUETable[i] = bl;
  }

}

void MaggicSegmentation::generateLUTFromHUE() {
  this->isLUTReady = false;
  static cv::Mat LUT_BGR2HSV = cv::Mat::zeros(1,LUT_SIZE/3,CV_8UC3);
  static bool preprocessed = false;
  if (!preprocessed) {

    for (int i=0;i<LUT_SIZE/3;i++) {
      int r = (i&0x00ff0000) >> 16;
      int g = (i&0x0000ff00) >> 8;
      int b = i&0x000000ff;
      LUT_BGR2HSV.at<cv::Vec3b>(0,i) = cv::Vec3b(b,g,r);
    }

    cv::cvtColor(LUT_BGR2HSV,LUT_BGR2HSV,cv::COLOR_BGR2HSV_FULL);

     // std::cout << "PREPROCESSED" << std::endl;

    preprocessed = true;
  }

  for (int i=0;i<LUT_SIZE/3;i++) {
    int r = (i&0x00ff0000) >> 16;
    int g = (i&0x0000ff00) >> 8;
    int b = i&0x000000ff;
    cv::Vec3b &coloro = LUT_BGR2HSV.at<cv::Vec3b>(0,i);

    float x = b;
    float y = g;
    float z = r;
    float men = min(min(x, y), z);
    float x1 = max(men - filterGrayThreshold, 0);
    float y1 = max(men - filterGrayThreshold, 0);
    float z1 = max(men - filterGrayThreshold, 0);
    float x2 = min(men + filterGrayThreshold, 255);
    float y2 = min(men + filterGrayThreshold, 255);
    float z2 = min(men + filterGrayThreshold, 255);
    if (x >= x1 && x <= x2 &&
      y >= y1 && y <= y2 &&
      z >= z1 && z <= z2) {
      this->_LUT[i] = 0; // black
    }
    else {
      this->_LUT[i] = this->_HUETable[coloro[0]];
    }

  }
  //std::cout << "Done generating LUT from Hue.\n";
  spdlog::get("Vision")->info("MaggicSegmentation::Done generating LUT from Hue.\n");
  this->isLUTReady = true;
}

int* MaggicSegmentation::getLUT() {
  return this->_LUT;
}


bool MaggicSegmentation::estimateRobots(cv::Mat img, int manyTimes, int n_components_reference) {
  CV_Assert(img.empty() == false && manyTimes > 0 && n_components_reference > 0);

  ++n_components_reference;
  static int original_filterGrayThreshold = rand()%_intervalGrayThreshold +_minimumGrayThreshold;
  original_filterGrayThreshold = filterGrayThreshold;
  int actualAdditive = 1, components_amount = 0;
  bool found = false;

//#if CV_MAJOR_VERSION == 3

  if (this->_debugSelection > MaggicVisionDebugSelection_Undefined) this->_multipliedResults = img.clone();

  if (!this->_learningThresholdValue)  manyTimes = 2;

  for (int times = 0; times < manyTimes && !found; ++times) {

    if (this->_learningThresholdValue) filterGrayThreshold = original_filterGrayThreshold + actualAdditive;
    //filterGrayThreshold = original_filterGrayThreshold -times;

    cv::Mat d, extremeSaturation;
    img.copyTo(d);
    cv::resize(d, d, cv::Size(d.cols >> 1, d.rows >> 1),0,0);

    componentsCentroids.clear();
    componentsRectangles.clear();
    cv::Mat t;

    // First pass to get the main connected components
    {
      //cv::GaussianBlur(d, d, cv::Size(7, 7), 3, 3);
      filterGray(d, d);
      //imwrite("robocin-afg.png", d);

      //imshow("after filter gray", d);
      t = cv::Mat::zeros(d.size(), CV_8UC1);
      cv::cvtColor(d, t, cv::COLOR_BGR2GRAY);
      //imshow("gray", t);
      //filterBinarizeColored(t,d);
      //imshow("binarized", t);
      t = t > 0;
      uint erosion_size = 1;
      cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS,
        cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
        cv::Point(erosion_size, erosion_size));
      cv::dilate(t, t, element, cv::Point(-1, -1), 1);
      cv::GaussianBlur(t, t, cv::Size(3, 3), 1, 1);
      t = t > 127;
      cv::erode(t, t, element, cv::Point(-1, -1), 2);

      //std::cout << "thresh t " << filterGrayThreshold << "actual additive " << actualAdditive <<  std::endl;

      //cv::imshow("thresh t", t);
      if (this->_debugSelection > MaggicVisionDebugSelection_Undefined) {
        cv::cvtColor(t,this->_firstThreshold,cv::COLOR_GRAY2BGR);

      }

      //cvtColor(d, d, COLOR_BGR2GRAY);
      /*cvtColor(d, d, COLOR_BGR2HLS_FULL);
      filterIncreaseSaturation(d, d);

      cvtColor(d, d, COLOR_HSV2BGR_FULL);*/
      cv::cvtColor(d, d, cv::COLOR_BGR2HSV_FULL);
      d.copyTo(extremeSaturation);
      filterExtremeSaturation(extremeSaturation,extremeSaturation);
      cv::cvtColor(extremeSaturation, extremeSaturation, cv::COLOR_HSV2BGR_FULL);
      cv::resize(extremeSaturation,extremeSaturation,cv::Size(extremeSaturation.cols<<1,extremeSaturation.rows<<1));
      //cv::imshow("ExtremeSaturation",extremeSaturation);
      if (this->_debugSelection > MaggicVisionDebugSelection_Undefined) this->_extremeSaturation = extremeSaturation.clone();

      //cvtColor(d, d, COLOR_BGR2HSV);
      //cvtColor(d, d, COLOR_BGR2RGB);

      //filterIncreaseSaturation(d, d);

      cv::Mat components, stats, centroids;
      //cv::resize(histo, histo, cv::Size(256, 1), 0, 0, INTER_NEAREST);

      n_components = cv::connectedComponentsWithStats(t, components, stats, centroids, 8, CV_32S,cv::CCL_DEFAULT);
      found = n_components >= n_components_reference;
      if (!found);//  goto applyAdditive;
      else
      //#pragma omp parallel sections
      {
        //#pragma omp section
        {
          cv::cvtColor(t, t, cv::COLOR_GRAY2BGR);
        }
        //#pragma omp section
        {
          for (int i = 1; i < n_components; ++i)
          {
            componentsCentroids.push_back(cv::Point2i(centroids.at<double>(i, 0), centroids.at<double>(i, 1)));

            //int area = stats.at<int>(i, cv::CC_STAT_AREA);
            int top = stats.at<int>(i, cv::CC_STAT_TOP);
            int left = stats.at<int>(i, cv::CC_STAT_LEFT);

            int bb_width = stats.at<int>(i, cv::CC_STAT_WIDTH);
            int bb_height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
            int bb_area = bb_width * bb_height;
            cv::Rect rct(left, top, bb_width, bb_height);
            if (bb_area < 200 && bb_area > 4) {
              components_amount++;
              componentsRectangles.push_back(rct);
            }
            //if (i == component_id) {
            //	cv::rectangle(t, rct, cv::Scalar(0, 0, 255));
            //	for (int x = left; x < left + bb_width; x++) {
            //		for (int y = top; y < top + bb_height; y++) {
            //			histo.at<float>(0, d.at<Vec3b>(y, x)[0]) += 1;
            //		}
            //	}
            //	doHistogram(d, rct, t);

            //	//cv::line(RB, cv::Point(0, 255 - xmed), cv::Point(256, 255 - xmed), cv::Scalar(0, 255, 0));
            //	//cv::line(RB, cv::Point(0, 255 - colorDescriptor), cv::Point(256, 255 - colorDescriptor), cv::Scalar(0, 0, 255));
            //	for (auto &e : colorDescriptors) {
            //		uchar hue = e * 255;
            //		cv::line(RB, cv::Point(0, 255 - hue), cv::Point(256, 255 - hue), cv::Scalar(0, 0, 255));
            //	}
            //}
            //else cv::rectangle(t, rct, cv::Scalar(0, 255, 255));
          }
        }
      }
    }
        //imshow("components", t);
        //std::cout << "components amount and reference " << components_amount << " " << n_components_reference << std::endl;
        if (components_amount != n_components_reference-1) {
          found = false;
          break;
        }



        greatestSumOfAreas = 0;
        //for (int te=0;te<4;++te);
        // int sumOfAreas = 0;
        //img.copyTo(d);
        //cv::resize(d, d, cv::Size(d.cols >> 1, d.rows >> 1),0,0);
//        // Second pass to get the bigger connected components crossed with main connected components
//        {
//          //cv::GaussianBlur(d, d, cv::Size(7, 7), 3, 3);
//          int oldFilterGrayThreshold = filterGrayThreshold;
//          //filterGrayThreshold -= 1;
//          filterGray(d, d);
//          filterGrayThreshold = oldFilterGrayThreshold;
//          //imshow("after filter gray 2", d);
//          cv::Mat t = cv::Mat::zeros(d.size(), CV_8UC1);
//          cv::cvtColor(d, t, cv::COLOR_BGR2GRAY);
//          //imshow("gray 2", t);
//          //filterBinarizeColored(t, d);
//          //cv::imshow("binarized", t);
//          t = t > 2;
//          uint erosion_size = 1;
//          cv::Mat element = cv::getStructuringElement(cv::MORPH_CROSS,
//            cv::Size(2 * erosion_size + 1, 2 * erosion_size + 1),
//            cv::Point(erosion_size, erosion_size));
//          cv::dilate(t, t, element, cv::Point(-1, -1), 1);
//          cv::GaussianBlur(t, t, cv::Size(3, 3), 1, 1);
//          t = t > 20;
//          cv::erode(t, t, element, cv::Point(-1, -1), 2);
//          //cv::imshow("thresh t 2", t);

//          cv::Mat components, stats, centroids;
//          //cv::resize(histo, histo, cv::Size(256, 1), 0, 0, INTER_NEAREST);

//          n_components = cv::connectedComponentsWithStats(t, components, stats, centroids,8,CV_32S,cv::CCL_DEFAULT);
//          //found = n_components == n_components_reference-1;
//          std::cout << "n components and reference " << n_components << " " << n_components_reference << std::endl;
//          if (n_components == n_components_reference) {
//            found = true;
//          } else found = false;
//          if (!found) ;// goto applyAdditive;
//          else
//          //#pragma omp parallel sections
//          {
//            //#pragma omp section
//            {
//              cv::cvtColor(t, t, cv::COLOR_GRAY2BGR);
//            }
//            //#pragma omp section
//            {
////              for (size_t j = 0; j < componentsCentroids.size(); j++) {
////                cv::Rect brct(0, 0, 0, 0);
////                int bestArea = 100000;

////                for (int i = 1; i < n_components; ++i) {
////                  int area = stats.at<int>(i, cv::CC_STAT_AREA);
////                  int top = stats.at<int>(i, cv::CC_STAT_TOP);
////                  int left = stats.at<int>(i, cv::CC_STAT_LEFT);

////                  int bb_width = stats.at<int>(i, cv::CC_STAT_WIDTH);
////                  int bb_height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
////                  //int bb_area = bb_width * bb_height;
////                  cv::Rect rct(left, top, bb_width, bb_height);

////                  if (left <= componentsCentroids[j].first &&
////                    left + bb_width > componentsCentroids[j].first &&
////                    top <= componentsCentroids[j].y &&
////                    top + bb_height > componentsCentroids[j].second &&
////                    area < bestArea
////                    ) {

////                    bestArea = area;
////                    brct = rct;
////                  }
////                }
////                if (bestArea < 150 && bestArea > 8) componentsRectangles.push_back(brct);
////              }
//            }
          //for (int i = 1; i < n_components; ++i) {

          //	cv::rectangle(t, rct, cv::Scalar(0, 0, 255));
          //	for (int x = left; x < left + bb_width; x++) {
          //		for (int y = top; y < top + bb_height; y++) {
          //			histo.at<float>(0, d.at<Vec3b>(y, x)[0]) += 1;
          //		}
          //	}
          //	doHistogram(d, rct, t);

          //	//cv::line(RB, cv::Point(0, 255 - xmed), cv::Point(256, 255 - xmed), cv::Scalar(0, 255, 0));
          //	//cv::line(RB, cv::Point(0, 255 - colorDescriptor), cv::Point(256, 255 - colorDescriptor), cv::Scalar(0, 0, 255));
          //	for (auto &e : colorDescriptors) {
          //		uchar hue = e * 255;
          //		cv::line(RB, cv::Point(0, 255 - hue), cv::Point(256, 255 - hue), cv::Scalar(0, 0, 255));
          //	}
          //}
//          if (componentsRectangles.size() < (size_t) n_components_reference && componentsRectangles.size() > 9) {
//            found = false;
//            break;
//          }
        {
          img.copyTo(d);
          //resize(d, d, Size(d.cols / 2, d.rows / 2),0,0);
          cv::cvtColor(d, d, cv::COLOR_BGR2HSV_FULL);
          //std::cout << "Descriptors : " <<  std::endl;
          //std::cout << "componentsRectangles.size() " << componentsRectangles.size() <<  std::endl;
          // Third pass
          for (size_t i = 0; i < componentsRectangles.size(); ++i) {
            memset(histo.data, 0, sizeof(float)*histo.cols*histo.rows*histo.channels());

            cv::Rect &r = componentsRectangles[i];
            r.x = max(r.x-2,0);
            r.y = max(r.y-2,0);
            r.width = min(r.width+2,d.cols);
            r.height = min(r.height+2,d.rows);
            cv::rectangle(t, r, cv::Scalar(255, 0,0));

            for (int x = (r.x << 1); x < (r.x << 1) + (r.width << 1); x++) {
              for (int y = (r.y << 1); y < (r.y << 1) + (r.height << 1); y++) {
                histo.at<float>(0, (int)d.at<cv::Vec3b>(y, x)[0]) += 1;
              }
            }
            // doHistogram(d, r, t);
            float maior = max_element_of<float>((float*)histo.data, histo.cols*histo.rows);
            //std::cout << "maior : " << maior <<  std::endl;
            histo /= (maior > 0 ? maior : 1);
            //std::cout << histo <<  std::endl;
            updateHistogramDescriptors();
            //std::cout << "colors size " << colorDescriptors.size() <<  std::endl;
            filterGrain(robotsDescriptors[i].colors, colorDescriptors);
            //std::cout << "robots descriptors[" << i << "] size " << robotsDescriptors[i].colors.size() <<  std::endl;
            /*for (float &e : robotsDescriptors[i].colors) {
              //std::cout << e << " ";
            }*/

            //std::cout << std::endl;

          }
          int colorsize = 0;
          for(int i=0;i<7;++i) colorsize = max(colorsize,(int)robotsDescriptors[i].colors.size());
          colorsize++;
          cv::Mat cores = cv::Mat::zeros(cv::Size(colorsize*32,32*7), CV_8UC3);

          cv::cvtColor(t, t, cv::COLOR_BGR2HSV_FULL);
          for(int i=0;i<7;++i) {
          cv::rectangle(cores,cv::Rect(0,i*32,32,32),cv::Scalar(i*255/7,255,255),-1);
          cv::rectangle(t,componentsRectangles[i],cv::Scalar(i*255/7,255,255),-1);
            for (size_t ii=0;ii<robotsDescriptors[i].colors.size();++ii) {
              float &e = robotsDescriptors[i].colors[ii];
              cv::rectangle(cores,cv::Rect(ii*32+32,i*32,32,32),cv::Scalar(e*255,255,255),-1);
            }
          }
          cv::cvtColor(cores, cores, cv::COLOR_HSV2BGR_FULL);
          cv::cvtColor(t, t, cv::COLOR_HSV2BGR_FULL);
          static char str[2000];
          sprintf(str,"robocin-robotColors.png");
          //cv::imwrite(str, cores);
          //cv::imshow(str,cores);

          //cv::imshow("biggerComponents", t);

          // testing multiplication
          cv::resize(t, t, cv::Size(t.cols << 1, t.rows << 1),0,0);
          cv::Mat mt = cv::Mat::zeros(t.size(), CV_8UC3);
          _layeredAdd(mt, img, t);
          if (this->_debugSelection > MaggicVisionDebugSelection_Undefined) this->_multipliedResults = mt.clone();
          //this->_thresholdFrequency[filterGrayThreshold]++;
          //cv::imshow("multiplied results", mt);
          //cv::imwrite("robocin-mt.png", mt);


          cv::Mat colorPlane = cv::Mat::zeros(cv::Size(512,512), CV_8UC3);
          for (int i=0;i<256;i++) {
            for(int j=0;j<256;j++) {
              cv::rectangle(colorPlane,cv::Rect(j << 1,i << 1,2,2),cv::Scalar(j,255,i),-1);
            }
          }

          {
            for(int i=0;i<8;i++) {
              for (size_t j=0;j<robotsDescriptors[i].colors.size();j++) {
                cv::Vec3b vec;
                vec[0] = robotsDescriptors[i].colors[j]*255;
                vec[1] = 0;
                vec[2] = 255;
                cv::circle(colorPlane,cv::Point(vec[0] << 1,vec[2] << 1),5,cv::Scalar(255,0,255),-1);
              }
            }
          }
          for(int i=0;i<10;++i) {
            cv::Vec3b vec = colorPaletteHSV.at<cv::Vec3b>(0,i);
            // float e = static_cast<float>(vec[0]);
            cv::circle(colorPlane,cv::Point(vec[0] << 1,vec[2] << 1),5,cv::Scalar(255,255,0),-1);
          }

          cv::cvtColor(colorPlane, colorPlane, cv::COLOR_HSV2BGR_FULL);
          cv::Scalar blackAndWhite[2] = {cv::Scalar(0,0,0), cv::Scalar(255,255,255)};
          //std::cout << "hueList.size() " << hueList.size() << std::endl;
          int begin = 0;
          int end = 1;
          for(size_t i=0;i<hueList.size();i++) {
            while (i+1 < hueList.size() && hueList[i+1].second == hueList[i].second) i++;
            end = (int)hueList[i].first << 1;

            cv::line(colorPlane,cv::Point(begin, 500), cv::Point(end, 500), blackAndWhite[i%2],4);

            begin = end;
          }

//          cv::imshow("colorPlane", colorPlane);


        }

      if (found) {
        //this->_thresholdFrequency[filterGrayThreshold]++;
        break;
      }

      //applyAdditive:
      --actualAdditive;
      --actualAdditive;


      // Change the number in this sequence : 1, -1, 2, -2, 3, -3, ...
/*
      if (actualAdditive < 0) {
        actualAdditive = -actualAdditive;
        ++actualAdditive;
        ++actualAdditive;
      }
      else {
        actualAdditive = -actualAdditive;
      }
*/

    }

    if (this->_learningThresholdValue) {
      if (found)
        this->_thresholdFrequency[filterGrayThreshold]++;
    //filterGrayThreshold = original_filterGrayThreshold;
      if (filterGrayThreshold < _minimumGrayThreshold || filterGrayThreshold > _maximumGrayThreshold || n_components != n_components_reference - 1)
        filterGrayThreshold = _maximumGrayThreshold;//rand()%_intervalGrayThreshold +_minimumGrayThreshold;//filterGrayThreshold = original_filterGrayThreshold;
    }
  //if (!found && this->_debugSelection == MaggicVisionDebugSelection_MultipliedResults) this->_segmentationFrame = img.clone();
//#endif
  return found; // return whether it found or not a threshold value that gets only 7 components (if searching for all components, 3 players x2 teams + 1 ball)
}


void MaggicSegmentation::setFilterGrayThresholdValue(int newFilterGrayThreshold) {
  this->filterGrayThreshold = newFilterGrayThreshold;
  this->updateColors = true;
}

int MaggicSegmentation::getFilterGrayThresholdValue() {
  return this->filterGrayThreshold;
}

void MaggicSegmentation::getFilterGrayThresholdValues(int &minimum, int &maximum) {
  minimum = _minimumGrayThreshold;
  maximum = _maximumGrayThreshold;
}

void MaggicSegmentation::setFilterGrayThresholdValues(int minimum, int maximum) {
  if (minimum > 0 && maximum > minimum) {
    _minimumGrayThreshold = minimum;
    _maximumGrayThreshold = maximum;
    _intervalGrayThreshold = _maximumGrayThreshold - _minimumGrayThreshold;
    memset(this->_thresholdFrequency,0,256*sizeof(uint));
    this->_calibrationFrames = 0;
  }
}

void MaggicSegmentation::setLearningThresholdValue(bool enabled) {
  if (!this->_learningThresholdValue && enabled) {
    memset(this->_thresholdFrequency,0,256*sizeof(uint));
    this->_calibrationFrames = 0;
  }
  this->_learningThresholdValue = enabled;
}

void MaggicSegmentation::updateFilterGrayThresholdValue() {
  if (this->_learningThresholdValue) {
    int bi = 0;
    for(int i=0;i<256;i++) {
      if (this->_thresholdFrequency[i] > this->_thresholdFrequency[bi]) {
        bi = i;
      }
    }
    this->filterGrayThreshold = bi;
  }
}

void MaggicSegmentation::getLearningThresholdValue(bool &enabled) {
  enabled = this->_learningThresholdValue;
}


void MaggicSegmentation::setLearningThresholdFrames(uint frames) {
  this->_learningThresholdFrames = frames;
}

void MaggicSegmentation::getLearningThresholdFrames(uint &frames) {
  frames = this->_learningThresholdFrames;
}

bool MaggicSegmentation::isLearning() {
  return this->_learningThresholdValue;
}

void MaggicSegmentation::getCalibrationFrames(uint &frames) {
  frames = this->_calibrationFrames;
}

cv::Mat MaggicSegmentation::run(cv::Mat &frame)
{
  if (!paused) frame.copyTo(this->_imageBuffer);
  if (!this->isLUTReady)return cv::Mat::zeros(480,640,CV_8U);

#ifdef USE_CUDA
    APPLY_LUT_GPU(frame);
    this->_segmentationFrame = frame.clone();

    cv::Mat returnFrame = cv::Mat::zeros(frame.rows,frame.cols,CV_8U);

    return returnFrame;
#else
  int label = 0;
  this->_segmentationFrame = cv::Mat::zeros(frame.rows,frame.cols,CV_8UC3);
  cv::Mat returnFrame = cv::Mat::zeros(frame.rows,frame.cols,CV_8U);

//  #pragma omp parallel for num_threads(8)
  for (int i = 0; i < frame.rows; i++) {

    const RGB* row = frame.ptr<RGB>(i);

    for (int j = 0; j < frame.cols; j++) {
      label = this->_LUT[(row[j].red<<16) + (row[j].green<<8) + row[j].blue];
      this->_segmentationFrame.ptr<RGB>(i)[j] = ColorSpace::markerColors[label];
      returnFrame.ptr<uchar>(i)[j] = (uchar) label;
     }
  }

  return returnFrame;
#endif

}

void MaggicSegmentation::initLUT()
{
  return;
#define USE_LEGACY
#ifdef USE_LEGACY
  int index;
  YUV color;

  for (int r = 0; r < 256; r++) {
    for (int g = 0; g < 256; g++) {
      for (int b = 0; b < 256; b++) {

        color.y = (9798 * r + 19235 * g + 3736 * b) >> 15;
        color.u = (18514 * (b - color.y) >> 15) + 128;
        color.v = (23364 * (r - color.y) >> 15) + 128;

        index = r * 65536 + g * 256 + b;

        *(((RGB*)this->_LUT) + (index)) = ColorSpace::markerColors[this->getColorLabel(color)];
      }
    }
  }
#else
    int colorsSize = NUMBEROFCOLOR;
    cv::Mat colors = cv::Mat::zeros(1,colorsSize,CV_8UC3);
    for (int i=0;i<colorsSize;i++) {
      colors.ptr<RGB>(0)[i] = ColorSpace::markerColors[i];
    }
    cv::cvtColor(colors,colors,CV_BGR2HSV_FULL);
    int index = 0;
    cv::Mat cor = cv::Mat::zeros(1,1,CV_8UC3);

    for (int r = 0; r < 256; r++) {
      for (int g = 0; g < 256; g++) {
        for (int b = 0; b < 256; b++) {
          cor.ptr<cv::Vec3b>(0)[0][0] = b;
          cor.ptr<cv::Vec3b>(0)[0][1] = g;
          cor.ptr<cv::Vec3b>(0)[0][2] = r;
          cv::cvtColor(cor,cor,CV_BGR2HSV_FULL);
          index++;
          int bc = 0, bd = 1024;
          for (int c = 0; c < colorsSize; c++) {
            int d = abs(colors.ptr<cv::Vec3b>(0)[c][0] - cor.ptr<cv::Vec3b>(0)[0][0]);
            if (d < bd) {
              bc = c;
              bd = d;
            }
          }
          //this->_LUT[index] = bc;// saving indexes
          *(((RGB*)this->_LUT)+index) = ColorSpace::markerColors[bc];
        }
      }
    }
#endif

#ifdef USE_CUDA
  LUT_GPU_V = new uchar[LUT_SIZE];
  memset(LUT_GPU_V, 0, LUT_SIZE);
  PREPARE_LUT_GPU();
  //LUT_GPU();
  setLUTToGPU((uchar*)this->_LUT,LUT_SIZE);
#else


#endif

}

cv::Mat MaggicSegmentation::getDebugFrame()
{
  switch(this->_debugSelection) {
    case MaggicVisionDebugSelection_Thresholded:
      return this->_firstThreshold.clone();
    case MaggicVisionDebugSelection_ExtremeSaturation:
      return this->_extremeSaturation.clone();
    case MaggicVisionDebugSelection_MultipliedResults:
      return this->_multipliedResults.clone();
    case MaggicVisionDebugSelection_SegmentationFrame:
      return this->_segmentationFrame.clone();
    case MaggicVisionDebugSelection_DetailsFrame:
      mut.lock();
      cv::Mat tmp = this->_detailsFrame.clone();
      mut.unlock();
      return tmp;
    break;
  }
}

//void MaggicSegmentation::setLUTPixel(YUV &color, int id)
//{
//  if (id < LUT_SIZE) {
//    this->_LUT[id] = this->getColorLabel(color);
//  }
//}

int MaggicSegmentation::getColorLabel(YUV& color)
{
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

  return -1;
}

void MaggicSegmentation::initFromFile(std::string path)
{

  cv::FileStorage fs(path, cv::FileStorage::READ);
  if(!fs.isOpened()) {
    spdlog::get("Vision")->error("MaggicSegmentation::initFromFile: Diretorio não encontrado {}",path);
  }
  cv::FileNode n;

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

cv::Mat MaggicSegmentation::getSegmentationFrameFromLUT()
{
  return this->_segmentationFrame;
}


void MaggicSegmentation::loadDefaultHue() {
  const static char* defaultHueListFileName = "Config/Segmentation/DefaultMaggicSegmentation.txt";
  FILE *f = fopen(defaultHueListFileName, "rt");
  if (f) {
    fscanf(f,"Maggic\n");
    fscanf(f,"%*d %*d %*d");
    //puts("COLOR PALETTE\nHUE(f) TAG");
    defaultHueList.clear();
    while(true) {
      int h, l;
      if (fscanf(f,"%d %d", &h, &l) == EOF) break;
      float hf = (float) h/255.f;
      hf = h;
      defaultHueList.push_back(std::make_pair(hf,l));
      //printf("%d(%.2f) %d\n", h, hf, l);
    }
    hueList.assign(defaultHueList.begin(), defaultHueList.end());
    //puts("\n\n");
    fclose(f);
  } else {
    spdlog::get("Vision")->error("MaggicSegmentation::loadDefaultHue: Acesso negado ao arquivo {}",defaultHueListFileName);
  }
}


void MaggicSegmentation::setMousePosition(cv::Point2f mpos) {
  mut.lock();
  if (!this->_detailsFrame.empty()) {
    this->lastCursorPos.push_back(this->cursorPos);
    this->cursorPos = cv::Point2d (mpos.x*this->_detailsFrame.cols, mpos.y*this->_detailsFrame.rows);
  }
  mut.unlock();
}

void MaggicSegmentation::setMouseButtonPress(int btnId) {
  mut.lock();
  if (!this->_detailsFrame.empty()) {
    this->pressedId = btnId;
    this->releasedId = 0;
    //std::cout << "pressed " << btnId << std::endl;
    this->pressedMouse = true;
  }
  mut.unlock();
}
void MaggicSegmentation::setMouseButtonRelease(int btnId) {
  mut.lock();
  if (!this->_detailsFrame.empty()) {
    this->releasedId = btnId;
    this->pressedId = 0;
    this->mouseDrag = false;
    this->releasedMouse = true;
  }
  mut.unlock();
}

void MaggicSegmentation::doDetails() {
  static int selectionCircleRadius = 6;
  static int borderDistance = 3;
  static cv::Rect colorFrame(30,30,512,400);
  static cv::Rect colorSelectionRecRef(colorFrame.x+colorFrame.width+16,colorFrame.y+2,32,32);
  static std::vector<cv::Rect> colorSelection;
  static bool colorSelectionReady = false;
  static bool pressedRight = false, pressedLeft = false;
  static int pivotForPaletteId = 0;
  static int colorSelectionId = -1;

  if (!colorSelectionReady) {
    colorSelectionReady = true;
    for(int i=0;i<7;i++) {
      colorSelection.push_back(colorSelectionRecRef);
      colorSelectionRecRef.y += 32+4;
    }
  }

  if (this->_debugSelection == MaggicVisionDebugSelection_DetailsFrame) {
    assert(selectionCircleRadius > 1);
    if (this->_colorDetailsFrame.empty() || this->updateColors) {
      this->_colorDetailsFrame = cv::Mat::zeros(cv::Size(colorFrame.width, colorFrame.height), CV_8UC3);
      int h2, h, s, v;
      for (int i=0;i<colorFrame.height;i++) {
        for(int j=0;j<colorFrame.width;j++) {
          h2 = (colorFrame.height>>1);
          if (i<h2) {
            h = j*255/colorFrame.width;
            s = 255;
            v = i*255/h2;
          }
          else {
            h = (j*255)/colorFrame.width;
            s = (255-(((i-h2)*255)/h2));
            v = 255;
          }
          this->_colorDetailsFrame.at<cv::Vec3b>(i,j) = cv::Vec3b(h,s,v);
        }
      }
      cv::cvtColor( this->_colorDetailsFrame,  this->_colorDetailsFrame, cv::COLOR_HSV2BGR_FULL);
      filterGray(this->_colorDetailsFrame,this->_colorDetailsFrame);
      this->updateColors = false;
    }

    mut.lock();
    if (this->_detailsFrame.empty()) {
      this->_detailsFrame = cv::Mat::zeros(cv::Size(640,480),CV_8UC3);
    }

    // erase old lastCursors
    if (lastCursorPos.size()>0) {
      for(cv::Point2d &last : this->lastCursorPos) {
        cv::circle(this->_detailsFrame,last,selectionCircleRadius+1,cv::Scalar(0,0,0),-1);
      }
      this->lastCursorPos.clear();
    }

    // draw color frame
    this->_colorDetailsFrame.copyTo(this->_detailsFrame(colorFrame));
    colorSelectionId = -1;
    for(int i=0;i<7;i++) {
      cv::Scalar cor(colorPalette.at<cv::Vec3b>(0,i+1));
      cv::rectangle(this->_detailsFrame,colorSelection[i],cor,-1);
        cv::Rect tr = colorSelection[i];
        tr.x-=1;
        tr.y-=1;
        tr.width+=2;
        tr.height+=2;
        if (colorSelection[i].contains(this->cursorPos)) {
          cv::rectangle(this->_detailsFrame,colorSelection[i],cv::Scalar(0,0,0),1);
          cv::rectangle(this->_detailsFrame,tr,cv::Scalar(255,255,255),1);
          colorSelectionId = i;
          //std::cout << "colorSelectionId " << colorSelectionId << std::endl;
        } else {
          cv::rectangle(this->_detailsFrame,colorSelection[i],cv::Scalar(0,0,0),1);
          cv::rectangle(this->_detailsFrame,tr,cv::Scalar(0,0,0),1);
        }
    }

    // draw color frame border
    cv::rectangle(this->_detailsFrame,cv::Rect(colorFrame.x-borderDistance,colorFrame.y-borderDistance, colorFrame.width+(borderDistance<<1), colorFrame.height+(borderDistance<<1)),cv::Scalar(255,255,255),1);
    cv::rectangle(this->_detailsFrame,cv::Rect(colorFrame.x-borderDistance+1,colorFrame.y-borderDistance+1, colorFrame.width+(borderDistance<<1)-2, colorFrame.height+(borderDistance<<1)-2),cv::Scalar(0,0,0),1);
    int pivotId = -1;
    for(int i =0;i<this->hueList.size();i++) {
      std::pair<float, int> &hue = this->hueList[i];
      int theX = hue.first*colorFrame.width/255 + colorFrame.x;
      int theDist = abs(this->cursorPos.x-theX);
      if (theDist < 6 && colorFrame.contains(this->cursorPos)) {
        if (pivotId == -1 ||
            theDist < abs(this->cursorPos.x - (this->hueList[pivotId].first*colorFrame.width/255 + colorFrame.x))) {
          pivotId = i;
        }

      }
      if (pivotForPaletteId-1 == i) cv::line(this->_detailsFrame,cv::Point(theX,colorFrame.y+1),cv::Point(theX,colorFrame.y+colorFrame.height-2), cv::Scalar(255,0,255),2);
      else cv::line(this->_detailsFrame,cv::Point(theX,colorFrame.y),cv::Point(theX,colorFrame.y+colorFrame.height-1), cv::Scalar(255,255,255),1);
    }

    if (this->pressedId == 1 && this->pressedMouse && !this->mouseDrag) {
      if (pivotId != -1) {
        std::cout << "start Drag" << std::endl;
        this->dragpivotId = pivotId;
        this->mouseDrag = true;
      }
    }
    //std::cout << "pressedId " << this->pressedId << std::endl;
    if (this->pressedId == 2) pressedRight = true;
    else if(pressedRight && this->releasedId == 2) {
      //std::cout << "Right Clicked" << std::endl;
      if (pivotId != -1) {
        pivotForPaletteId = pivotId+1;
      } else pivotForPaletteId = 0;
      pressedRight = false;
    }
    if (this->pressedId == 1) pressedLeft = true;
    else if (pressedLeft && this->releasedId == 1) {
      std::cout << "Left Clicked" << std::endl;
      if (pivotForPaletteId && colorSelectionId != -1) {
         this->hueList[pivotForPaletteId-1].second = colorSelectionId+1;
        std::cout << "Selected color " << colorSelectionId+1 << " for " << pivotForPaletteId-1 << std::endl;
        saveSession();
        std::cout << "Saved session values" << std::endl;
      }
    }
    if (pivotForPaletteId) {
      int colorForPaletteId = this->hueList[pivotForPaletteId-1].second-1;
      cv::Rect tr = colorSelection[colorForPaletteId];
      tr.x-=1;
      tr.y-=1;
      tr.width+=2;
      tr.height+=2;
      cv::rectangle(this->_detailsFrame,tr,cv::Scalar(255,0,255),1);
    }
    if (this->pressedId == 1 && this->mouseDrag) {
      std::cout << "dragging " << dragpivotId << std::endl;
      if (dragpivotId != -1) {
        //int theX = this->hueList[dragpivotId].x*colorFrame.width/255 + colorFrame.x;
        int theX = this->cursorPos.x;
        cv::line(this->_detailsFrame,cv::Point(theX,colorFrame.y+1),cv::Point(theX,colorFrame.y+colorFrame.height-2), cv::Scalar(0,255,0),2);
      }
    } else if (this->releasedId == 1 && this->releasedMouse && this->dragpivotId != -1) {
      float newHue = (this->cursorPos.x-colorFrame.x)*255.0/colorFrame.width;
      this->hueList[this->dragpivotId].first = newHue;
      this->dragpivotId = -1;
    } else {
      //std::cout << "hover" << std::endl;
      if (pivotId != -1) {
        int theX = this->hueList[pivotId].first*colorFrame.width/255 + colorFrame.x;
        cv::line(this->_detailsFrame,cv::Point(theX,colorFrame.y+1),cv::Point(theX,colorFrame.y+colorFrame.height-2), cv::Scalar(0,255,255),2);
      }
    }

    // draw vertical line for reference, only when mouse over color frame and not over pivots
    /*if (colorFrame.contains(this->cursorPos) && pivotId == -1) {
      cv::line(this->_detailsFrame,cv::Point(this->cursorPos.x-1,colorFrame.y),cv::Point(this->cursorPos.x-1,colorFrame.y+colorFrame.height-1),cv::Scalar(0,0,0),1);
      cv::line(this->_detailsFrame,cv::Point(this->cursorPos.x,colorFrame.y),cv::Point(this->cursorPos.x,colorFrame.y+colorFrame.height-1),cv::Scalar(255,255,255),1);
      cv::line(this->_detailsFrame,cv::Point(this->cursorPos.x+1,colorFrame.y),cv::Point(this->cursorPos.x+1,colorFrame.y+colorFrame.height-1),cv::Scalar(0,0,0),1);
    }*/

    // draw selection circle cursor
    cv::circle(this->_detailsFrame,this->cursorPos,selectionCircleRadius+1,cv::Scalar(0,0,0),1);
    cv::circle(this->_detailsFrame,this->cursorPos,selectionCircleRadius,cv::Scalar(255,255,255),1);
    cv::circle(this->_detailsFrame,this->cursorPos,selectionCircleRadius-1,cv::Scalar(0,0,0),1);

    this->releasedId = 0;
    this->releasedMouse = this->pressedMouse = false;
    mut.unlock();
  }
}