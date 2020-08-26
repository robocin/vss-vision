#ifndef MAGGICSEGMENTATIONDIALOG_H
#define MAGGICSEGMENTATIONDIALOG_H

#include <QDialog>
#include <QTimer>
#include <Timer/Timer.h>
#include <stdio.h>

#include <Vision/Vision.h>
#include <CameraManager/CameraManager.h>
#include <Vision/ImageProcessing/MaggicSegmentation.h>
#include <sstream>

namespace Ui {
  class MaggicSegmentationDialog;
  class FieldPointsCalibrateDialog;
}

class MaggicSegmentationDialog : public QDialog
{
  Q_OBJECT

public:
  explicit MaggicSegmentationDialog(QWidget *parent = 0);
  ~MaggicSegmentationDialog();
private slots:

void updateFrame();
void setFrameOnScreen();
#define entitiesButtonClicked( elbo ) void on_entitiesButton_ ## elbo ## _clicked()
entitiesButtonClicked(1);
entitiesButtonClicked(2);
entitiesButtonClicked(3);
entitiesButtonClicked(4);
entitiesButtonClicked(5);
entitiesButtonClicked(6);
entitiesButtonClicked(7);
#undef entitiesButtonClicked

void on_tabWidget_currentChanged(int index);
void on_minimumVerticalSlider_valueChanged();
void on_maximumVerticalSlider_valueChanged();
void on_threshGrayHorizontalSlider_valueChanged();
void on_resetButton_clicked();
void clearEntitiesCheck();

void on_playpauseButton_clicked(bool checked);


void on_applyLUTButton_clicked();

void on_fixCameraButton_clicked();

void on_buttonBox_accepted();

void on_loadButton_clicked();

void on_vectorscopeCheckBox_toggled(bool checked);

void on_FilterCheckBox_toggled(bool checked);

void on_NormalizedCheckBox_toggled(bool checked);

private:
  Ui::MaggicSegmentationDialog *ui;
  Vision* _vision;
  CameraManager* _cameraMan;
  cv::Mat _actualFrame, _segmentedFrame;

  bool paused;

  MaggicSegmentation *maggicSegmentation;

  QPushButton *entities[8];

  QTimer *_updateFrameTimer;

  bool eventFilter(QObject *f_object, QEvent *f_event);

public:
  QTimer *getUpdateFrameTimer();
};

#endif // MAGGICSEGMENTATIONDIALOG_H
