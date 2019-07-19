
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QPainter>
#include <QFileDialog>
#include <QMutex>
#include <CameraManager/CameraManager.h>
#include <Entity/Player.h>
#include <Utils/Utils.h>
#include <Vision/Vision.h>
#include <QAbstractListModel>
#include <visionconfigdialog.h>
#include "cameraconfigurationdialog.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include <QTimer>
#include <QTime>
#include <QShortcut>
#include <time.h>
#include <QMessageBox>
#include <queue>
#include <maggicsegmentationdialog.h>
#include <Timer/Timer.h>

#define SECONDARY_COLOR_XML "Config/SecondaryColor.xml"
#define ROBOT0_LABEL "ROBOT0"
#define ROBOT1_LABEL "ROBOT1"
#define ROBOT2_LABEL "ROBOT2"
#define TEAM_LABEL "TEAM"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

private:

  Ui::MainWindow *ui;

  cv::Mat _currentFrame;
  cv::VideoWriter _videoRecordManager;
  Job _currentJob;
  std::vector<Entity> _robotPositions;

  bool _openCameraFlag;
  bool _openVideoFlag;
  bool _isCaptureOpen;
  bool _hasVisionStarted;
  bool _hasStrategyStarted;
  bool _communicationRunning;
  bool _fieldCheck;
  bool _debugFowardEnabled;
  bool _saveSecondaryColor;
  bool _firstTimeOpeningCamera;
  bool _isRecording;
  bool _maggicSegmentationRunning;
  bool _static_decisions;
  bool _bezierLines;

  cv::Point _limitPoints[4];

  QString _videoFileName;
  QString _savedVideofileName;
  QString _strategyConfigDialogFileName;
  QString _navigationConfigDialogFileName;
  QString _gkConfigDialogFileName;
  QString _dfConfigDialogFileName;
  QString _atkConfigDialogFileName;
  QString _dfDefenderConfigFileName;
  QString _dfMiddleConfigFileName;

  QTimer* _updateMainWindowFrameTimer;

  int _half;
  int _currentFieldIndex;
  int _secColor[3];
  double _fps;
  cv::Point2d _allyRobotsPosition[3];

  char roleIcon[3][256] = {":/image/icon/026-goalkeeper.png",
              ":/image/icon/025-defender.png",
              ":/image/icon/024-attacker.png"};

  FieldPointsCalibrateDialog* _fieldDialog;
  CameraConfigurationDialog* _cameraDialog;
  VisionConfigDialog* _visionDialog;
  MaggicSegmentationDialog* _maggicSegmentationDialog;

  QLabel *mousePositionLabel;
  QLabel *fpsLabel;
  QLabel *strategyTimeLabel;
  QLabel *visionTimeLabel;

  int LonelyPlayerRole;

  void closeWindow();
  void pauseGame();
  void initColorBoxes();
  void clearCameraFrame();
  void saveCurrentVideo();
  void startVideoRecording();
  bool eventFilter(QObject *f_object, QEvent *f_event);
  void getPointsFromXML(std::string path);
  void getHalfFromXML(std::string path);
  void saveColorXML();
  void initColorXML();
  void toggleMaggicSegmentationDialog();
  void setCameraFrame();
  void record();

  /**
   * @brief gameSetUi Display the position in the gameSet
   */
  void setRobotInfoInUi();
  /**
   * @brief getQString format the string to be display in the gameSet
   * @param position the position of the robot in pair<double>
   * @return a formated QString
   */
  QString getQString(cv::Point2d position);

protected:
  void keyPressEvent(QKeyEvent *e);

private slots:
  void on_visionConfigurePushButton_clicked();
  void on_robot_1_secondaryColorComboBox_currentIndexChanged(int RadioIndexbyColor);
  void on_robot_2_secondaryColorComboBox_currentIndexChanged(int RadioIndexbyColor);
  void on_robot_3_secondaryColorComboBox_currentIndexChanged(int RadioIndexbyColor);
  void on_capturePushButton_clicked();
  void on_strategyConfigurePushButton_clicked();
  void on_visualizationComboBox_currentIndexChanged(const QString &arg1);
  void on_calibrateFieldPointspushButton_clicked();
  void on_videoPathBrowsePushButton_clicked();
  void on_cameraIndexComboBox_activated(const QString &arg1);
  void on_cameraConfigPushButton_clicked();
  void on_cutFieldPushButton_clicked();
  void on_strategyInitPushButton_clicked();
  void on_visionInitPushButton_clicked();
  void on_maggicSegmentationButton_clicked();
  void on_communicationPushButton_clicked();
  void on_communicationResetPushButton_clicked();
  void on_startAllPushButton_clicked(bool checked);
  void on_checkBox_clicked(bool checked);
  void on_halfPushButton_clicked();
  void on_planning_clicked(bool checked);
  void on_primaryColor_clicked(bool checked);
  void on_sourceTab_currentChanged(int index);
  void on_actionExit_triggered();
  void on_rolePotentialField3dPushButton_clicked();
  void on_tabWidget_currentChanged(int index);
  void on_gameSetDock_dockLocationChanged(const Qt::DockWidgetArea &area);
  void on_actionRight_triggered();
  void on_actionLeft_triggered();
  void on_actionRight_2_triggered();
  void on_actionLeft_2_triggered();
  void on_actionBottom_triggered();
  void on_actionMenu_2_triggered(bool checked);
  void on_actionInfo_3_triggered(bool checked);
  void on_communicationModeComboBox_currentIndexChanged(const QString &arg1);
  void on_fps_checkBox_clicked(bool checked);
  void on_LonelyPlayerRole_currentIndexChanged(int playerRole);
  void on_static_decisions_checkbox_clicked(bool checked);
  void on_bezierlines_checkbox_clicked(bool checked);

  void resizeCamera();
  void updateMainWindow();

  void on_DistortionComboBox_currentIndexChanged(const QString &arg1);

signals:
  void startCameraUpdate();
  void pauseCameraUpdate();
  void finishVisionThread();
  void enableVisionThread(bool enabled);
  void enableStrategyThread(bool enabled);
};

#endif // MAINWINDOW_H
