#ifndef VSS_VISION_TRACKCONFIGDIALOG_H
#define VSS_VISION_TRACKCONFIGDIALOG_H

#include <QDialog>
#include <iostream>
#include <Vision/Vision.h>
#include <QTimer>
#include <CameraManager/CameraManager.h>

namespace Ui {
  class TrackConfigDialog;
}

class TrackConfigDialog : public QDialog {
  Q_OBJECT

 public:
  explicit TrackConfigDialog(QWidget* parent = 0);
  ~TrackConfigDialog();

 private slots:

  /**
   * @brief    On click on menu
   *
   * @param[in]  index  The index of the clicked item
   */
  void on_treeWidget_activated(const QModelIndex& index);

  /**
   * @brief    update the display of minSize
   *
   * @param[in]  value  The new value of minSize
   */
  void on_verticalSlider__MinSize_valueChanged(int value);

  /**
   * @brief    update the display of maxSize
   *
   * @param[in]  value  The new value of maxSize
   */
  void on_verticalSlider__MaxSize_valueChanged(int value);

  /**
   * @brief    update the display of minSizeBall
   *
   * @param[in]  value  The new value of minSizeBall
   */
  void on_verticalSlider__MinSizeBall_valueChanged(int value);

  /**
   * @brief    update the display of maxSizeBall
   *
   * @param[in]  value  The new value of maxSizeBall
   */
  void on_verticalSlider__MaxSizeBall_valueChanged(int value);

  /**
   * @brief    Reads a xml.
   */
  void readXML();

  /**
   * @brief    Shows the frame.
   */
  void showFrame();

  /**
   * @brief    initial function.
   */
  void init();
  /**
   * @brief setIntoPossitionProcessing call setDetectionParam or setTrackParam
   * @param str string with the label of the var
   * @param value value of the new var
   */
  void setIntoPossitionProcessing(std::string str, int value);

  /**
   * @brief    update the display: number of orange clusters
   *
   * @param[in]  value  The new number of orange clusters
   */
  void on_verticalSlider_orange_valueChanged(int value);

  /**
   * @brief    update the display: number of blue clusters
   *
   * @param[in]  value  The new number of blue clusters
   */
  void on_verticalSlider_blue_valueChanged(int value);

  /**
   * @brief    update the display: number of yellow clusters
   *
   * @param[in]  value  The new number of yellow clusters
   */
  void on_verticalSlider_yellow_valueChanged(int value);

  /**
   * @brief    update the display: number of red clusters
   *
   * @param[in]  value  The new number of red clusters
   */
  void on_verticalSlider_red_valueChanged(int value);

  /**
   * @brief    update the display: number of green clusters
   *
   * @param[in]  value  The new number of green clusters
   */
  void on_verticalSlider_green_valueChanged(int value);

  /**
   * @brief    update the display: number of pink clusters
   *
   * @param[in]  value  The new number of pink clusters
   */
  void on_verticalSlider_pink_valueChanged(int value);

  /**
   * @brief    update the display: number of light blue clusters
   *
   * @param[in]  value  The new number of light blue clusters
   */
  void on_verticalSlider_light_blue_valueChanged(int value);

  /**
   * @brief    update the display: number of purple clusters
   *
   * @param[in]  value  The new number of purple clusters
   */
  void on_verticalSlider_purple_valueChanged(int value);

  /**
   * @brief    update the display: number of unknown clusters
   *
   * @param[in]  value  The new number of unknown clusters
   */
  void on_verticalSlider_unknown_valueChanged(int value);

  /**
   * @brief readXML again
   */
  void on_pushButton_Reset_clicked();

  void updateFrame();

  void on_comboBox_EnemySearch_currentIndexChanged(int index);

 private:
  Vision* _vision;
  enum Detection { WHEREARETHOSE, NONE };
  enum Track { Default };
  enum Processing { DETECTION, TRACKING };
  QTimer* _updateFrameTimer;
  Ui::TrackConfigDialog* ui;
  int _parentIndex;
  int _index;
  cv::Mat _PositionFrame;
  Entity _robotsPositions[7];
  QPalette _paletteColor[10];
  QString colorLabel[11] = {"white",
                            "orange",
                            "blue",
                            "yellow",
                            "red",
                            "green",
                            "pink",
                            "cyan",
                            "purple",
                            "gray",
                            "darkGray"};
};

#endif // VSS_VISION_TRACKCONFIGDIALOG_H
