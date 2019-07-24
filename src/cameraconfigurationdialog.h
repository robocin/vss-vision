#ifndef CAMERACONFIGURATIONDIALOG_H
#define CAMERACONFIGURATIONDIALOG_H
#include <iostream>
#include <QDialog>
#include <CameraManager/CameraManager.h>


namespace Ui {
class CameraConfigurationDialog;
}

class CameraConfigurationDialog : public QDialog
{
  Q_OBJECT

public:
  explicit CameraConfigurationDialog(QWidget *parent = 0);
  ~CameraConfigurationDialog();
  CameraManager* _camera;


private slots:
  void on_horizontalSlider_brightness_valueChanged(int value);

  void on_horizontalSlider_contrast_valueChanged(int value);

  void on_horizontalSlider_saturation_valueChanged(int value);

  void on_horizontalSlider_exposure_valueChanged(int value);

  void on_buttonBox_accepted();

  void on_setBrigtnessDefaultButton_clicked();

  void on_setContrastDefaultButton_clicked();

  void on_setSaturationDefaultButton_clicked();

  void on_setExposureDefaultButton_clicked();

  void on_setDefaultAll_clicked();

  void on_pushButton_clicked();

  void on_pushButton_readXML_D_clicked();

  void on_pushButton_readXML_L_clicked();

  void on_white_balance_auto_checkBox_clicked(bool checked);

  void on_focus_auto_checkBox_clicked(bool checked);

  void on_horizontalSlider_blacklight_valueChanged(int value);

  void on_horizontalSlider_white_balance_valueChanged(int value);

  void on_horizontalSlider_gain_valueChanged(int value);

  void on_setExposureAutoDefaultButton_clicked();

  void on_setWhiteBalanceAutoDefaultButton_clicked();

  void on_setWhiteBalanceDefaultButton_clicked();

  void on_setBlacklightDefaultButton_clicked();

  void on_setFocusAutoDefaultButton_clicked();

  void on_setGainDefaultButton_clicked();

  void on_buttonBox_rejected();

  void on_horizontalSlider_exposureAuto_valueChanged(int value);

  void on_exposureAutoPriority_checkBox_clicked(bool checked);

  void on_setExposureAutoPriorityDefaultButton_clicked();

private:
  Ui::CameraConfigurationDialog *ui;
  bool _isSetup;
};

#endif // CAMERACONFIGURATIONDIALOG_H
