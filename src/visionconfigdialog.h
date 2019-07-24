#ifndef VISIONCONFIGDIALOG_H
#define VISIONCONFIGDIALOG_H

#include <QDialog>

#include <fieldpointscalibratedialog.h>
#include <segmentationconfigdialog.h>
#include <trackconfigdialog.h>
#include <QPainter>
#include <Vision/ColorSpace.h>
#include <QAbstractButton>

namespace Ui {
class VisionConfigDialog;
}

class VisionConfigDialog : public QDialog
{
  Q_OBJECT

public:
  explicit VisionConfigDialog(bool videoFlag, QWidget *parent = 0);
  ~VisionConfigDialog();
  void setHasStarted(bool visionStarted);
  bool getHasStarted();
private slots:
  void on_calibrateTrackingPushButton_clicked();
  void on_calibrateSegmentationPushButton_clicked();
  void updateLabels();

  void on_buttonBox_clicked();

private:
  Ui::VisionConfigDialog *ui;
  Vision* _vision;
  TrackConfigDialog* _trackDialog;
  SegmentationConfigDialog* _segmentationDialog;
  bool _videoFlag;
  QPixmap _fieldPixmap;
  QTimer* _updateLabelsTimer;
  std::vector<Entity> _robotPositions;
  bool _visionStarted;

};

#endif // VISIONCONFIGDIALOG_H
