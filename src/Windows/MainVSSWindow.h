#ifndef MAINVSSWINDOW_H
#define MAINVSSWINDOW_H

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QKeyEvent>
#include <QMainWindow>
#include <QMessageBox>
#include "GameInfo/GameInfo.h"
#include "QFrame"
#include "QLine"
#include "QPalette"
#include "QVBoxLayout"
#include "RobotWidget.h"
#include "Vision/Vision.h"
#include "maggicsegmentationdialog.h"
#include "visionconfigdialog.h"
#include "Network/Network.h"

#define SECONDARY_COLOR_FILE "Config/SecondaryColor.json"
#define HALF_FILE "Config/Half.json"
#define TEAM_LABEL "team"

namespace Ui {
class MainVSSWindow;
}

class MainVSSWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainVSSWindow(QWidget* parent = nullptr);
  ~MainVSSWindow();

 private slots:
  void update();

  void on_capturePushButton_clicked();

  void on_cutFieldPushButton_clicked();

  void on_visionInitPushButton_clicked();

  void on_calibrateFieldPointspushButton_clicked();

  void on_visionConfigurePushButton_clicked();

  void on_maggicSegmentationButton_clicked();

  void toggleMaggicSegmentationDialog();

  void on_primaryColor_clicked(bool checked);

  void on_videoPathBrowsePushButton_clicked();

  void on_numberOfPlayersSpinBox_valueChanged(int arg1);

  void on_numbetOfPlayersConfirm_clicked();

  void on_fieldSizeComboBox_currentIndexChanged(const QString &arg1);

  void on_halfPushButton_clicked();

  void on_playNNButton_clicked(bool checked);

  void on_stopButton_clicked();

  void readMainWindowConfig();

  void saveMainWindowConfig();


private:
  Ui::MainVSSWindow* m_ui;
  QTimer* m_mainWindowFrameTimer;
  // Redimensiona os frames para o preenchimento certo
  void resizeSimulationFrame();
  void resizeFrames();
  void setFrame(QImage image);
  void setFrame();
  void clearFrame();
  void saveColorFile();
  void initColors();
  void rebuildRobotsScrollArea();
  void getPointsFromFile();
  void savePointsToFile();
  void getHalfFromFile();
  void saveHalf();
  void mirrorLimitPoints();
  void selectCorrectFrame();


  bool m_isCaptureOpen;
  bool m_videoCapture;

  int m_half;

  cv::Mat m_currentFrame;
  cv::Point m_limitPoints[4];

  QString m_videoFileName;
  QString m_savedVideofileName;

  Array<RobotWidget*, MAX_PLAYERS> m_robotWidgets;
  Array<QFrame*, MAX_PLAYERS - 1> m_robotLines;

  FieldPointsCalibrateDialog* m_fieldDialog;  // crop window
  VisionConfigDialog* m_visionDialog;
  MaggicSegmentationDialog* m_maggicSegmentationDialog;

  QJsonObject m_secondaryColorJson;
  QLabel *m_visionTimer;

  std::mutex m_currentFrameLocker;

  QJsonObject _mainWindowConfig;

protected:
  void keyPressEvent(QKeyEvent *e);
};

#endif  // MAINVSSWINDOW_H
