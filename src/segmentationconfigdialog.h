#ifndef SEGMENTATIONCONFIGDIALOG_H
#define SEGMENTATIONCONFIGDIALOG_H

#include <QDialog>
#include <QMouseEvent>
#include <Vision/ColorSpace.h>
#include <Vision/ImageProcessing/LUTSegmentation.h>
#include <QTimer>
#include <CameraManager/CameraManager.h>
#include <Vision/Vision.h>
#include <QFileDialog>
#include <dirent.h>
#include <Windows/FileConstants.h>
#define SEGMENTATION_SALAMANHA_FILE  "Config/Segmentation/SalaManha.xml"
#define SEGMENTATION_SALANOITE_FILE  "Config/Segmentation/SalaNoite.xml"
#define SEGMENTATION_VIDEO_FILE  "Config/Segmentation/Video.xml"
#define SEGMENTATION_ZEROS_FILE  "Config/Segmentation/Zeros.xml"
#define SEGMENTATION_XML "Config/Segmentation/"
#define ZOOM_ADJUST_X_MAX 30
#define ZOOM_ADJUST_X_MIN 0
#define ZOOM_ADJUST_Y 30


enum fileTypes {
  DefaultFile,
  Video,
  SalaManha,
  SalaNoite,
  Zeros
};

namespace Ui {
class SegmentationConfigDialog;
}

class SegmentationConfigDialog : public QDialog
{
  Q_OBJECT

public:
  explicit SegmentationConfigDialog(const bool videoFlag, QWidget *parent = nullptr);
  ~SegmentationConfigDialog();
  bool getQuantizationBool();

private slots:
  void on_ParametersListWidget_clicked();

  void on_YMinHorizontalSlider_valueChanged(int value);

  void on_UMinHorizontalSlider_valueChanged(int value);

  void on_VMinHorizontalSlider_valueChanged(int value);

  void on_YMaxHorizontalSlider_valueChanged(int value);

  void on_UMaxHorizontalSlider_valueChanged(int value);

  void on_VMaxHorizontalSlider_valueChanged(int value);

  void updateFrame();

  void on_selectColorComboBox_currentIndexChanged(int index);

  void on_buttonBox_accepted();

  void on_buttonBox_rejected();

  bool eventFilter(QObject *f_object, QEvent *f_event);

  /**
   *  putZoom take the region of interest and resize that ROI to 100x100
   * @param Frame
   */
  void putZoom(cv::Mat Frame);


  /**
   * @brief on_saveSegmentationPushButton_clicked
   * Save a new segmentation xml file
   */
  void on_saveSegmentationPushButton_clicked();

  /**
   * @brief initList load and update the display of all Xml files in segmentation folder
   */
  void initList();

  void on_NoCOLCheckBox_clicked(bool checked);

  void on_OrangeCheckBox_clicked(bool checked);

  void on_BlueCheckBox_clicked(bool checked);

  void on_YellowCheckBox_clicked(bool checked);

  void on_RedCheckBox_clicked(bool checked);

  void on_GreenCheckBox_clicked(bool checked);

  void on_PinkCheckBox_clicked(bool checked);

  void on_LightBlueCheckBox_clicked(bool checked);

  void on_PurpleCheckBox_clicked(bool checked);

  void on_ColorStrangeCheckBox_clicked(bool checked);

  void on_checkAll_clicked();

  void on_UnCheckAll_clicked();
  void on_QuantizationCheckBox_clicked(bool checked);

  void on_pushButton_CloseColor_clicked();

  void on_pushButton_OpenColor_clicked();

  void resizeCamera(void);

  void on_horizontalSlider_grayScale_valueChanged(int value);

private:

  void setAllCheckBoxUi(bool check);

  cv::Mat _zoom;
  cv::Rect _zoomrect;
  bool _click;
  QPoint _qpoint;
  Ui::SegmentationConfigDialog *ui;
  ColorInterval* _calibrationParameters;
  int _actualColorIndex;
  QTimer* _updateFrameTimer;
  cv::Mat _actualFrame;
  bool _visibleColors[NUMBEROFCOLOR];
  std::string _colorLabels[NUMBEROFCOLOR] = { NOCOLLABEL,
                        ORANGELABEL,
                        BLUELABEL,
                        YELLOWLABEL,
                        REDLABEL,
                        GREENLABEL,
                        PINKLABEL,
                        LIGHTBLUELABEL,
                        PURPLELABEL,
                        BROWNLABEL,
                        COLORSTRANGELABEL };

  void readFromFile();
  void saveInFile();
  void setup(int color,int minY,int minU,int minV,int maxY,int maxU,int maxV);
  void attSliders();
  void setFrameOnScreen();
  void setOriginalFrameOnScreen();
  std::string _newSegmentationStdFile;
  cv::Mat getFrame();
  bool getClick();
  cv::Mat segmentFrameWithIntervals(cv::Mat frame);
  bool _videoFlag;
  bool _quantization;
  int _grayTrashHoldLevel;
};

#endif // SEGMENTATIONCONFIGDIALOG_H
