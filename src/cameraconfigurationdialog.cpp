#include "cameraconfigurationdialog.h"
#include "ui_cameraconfigurationdialog.h"

CameraConfigurationDialog::CameraConfigurationDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::CameraConfigurationDialog)
{
  ui->setupUi(this);
  this->_camera = &this->_camera->singleton();
  this->_isSetup = true;
  // Set Current Value in UI
  ui->brightness_value_label->setText(QString::number(this->_camera->getBrightness().currentValue));
  ui->contrast_value_label->setText(QString::number(this->_camera->getContrast().currentValue));
  ui->saturation_value_label->setText(QString::number(this->_camera->getSaturation().currentValue));
  ui->exposureAutoPriority_checkBox->setChecked(this->_camera->getExposureAutoPriority().currentValue);
  ui->exposureAuto_value_label->setText(QString::number(this->_camera->getExposureAuto().currentValue));
  ui->exposure_value_label->setText(QString::number(this->_camera->getExposureAbsolute().currentValue));
  ui->blacklight_value_label->setText(QString::number(this->_camera->getBlacklightComp().currentValue));
  ui->white_balance_auto_checkBox->setChecked(this->_camera->getWhiteBalanceAuto().currentValue);
  ui->white_balance_value_label->setText(QString::number(this->_camera->getWhiteBalance().currentValue));
  ui->gain_value_label->setText(QString::number(this->_camera->getGain().currentValue));
  ui->focus_auto_checkBox->setChecked(this->_camera->getFocusAuto().currentValue);

  // Set Min, Max and Slider Position
  ui->horizontalSlider_brightness->setMinimum(this->_camera->getBrightness().minValue);
  ui->horizontalSlider_brightness->setMaximum(this->_camera->getBrightness().maxValue);
  ui->horizontalSlider_brightness->setSliderPosition(this->_camera->getBrightness().currentValue);

  ui->horizontalSlider_contrast->setMinimum(this->_camera->getContrast().minValue);
  ui->horizontalSlider_contrast->setMaximum(this->_camera->getContrast().maxValue);
  ui->horizontalSlider_contrast->setSliderPosition(this->_camera->getContrast().currentValue);

  ui->horizontalSlider_exposure->setMinimum(this->_camera->getExposureAbsolute().minValue);
  ui->horizontalSlider_exposure->setMaximum(this->_camera->getExposureAbsolute().maxValue);
  ui->horizontalSlider_exposure->setSliderPosition(this->_camera->getExposureAbsolute().currentValue);

  ui->horizontalSlider_exposureAuto->setMinimum(this->_camera->getExposureAuto().minValue);
  ui->horizontalSlider_exposureAuto->setMaximum(this->_camera->getExposureAuto().maxValue);
  ui->horizontalSlider_exposureAuto->setSliderPosition(this->_camera->getExposureAuto().currentValue);

  ui->horizontalSlider_saturation->setMinimum(this->_camera->getSaturation().minValue);
  ui->horizontalSlider_saturation->setMaximum(this->_camera->getSaturation().maxValue);
  ui->horizontalSlider_saturation->setSliderPosition(this->_camera->getSaturation().currentValue);

  ui->horizontalSlider_blacklight->setMinimum(this->_camera->getBlacklightComp().minValue);
  ui->horizontalSlider_blacklight->setMaximum(this->_camera->getBlacklightComp().maxValue);
  ui->horizontalSlider_blacklight->setSliderPosition(this->_camera->getBlacklightComp().currentValue);

  ui->horizontalSlider_white_balance->setMinimum(this->_camera->getWhiteBalance().minValue);
  ui->horizontalSlider_white_balance->setMaximum(this->_camera->getWhiteBalance().maxValue);
  ui->horizontalSlider_white_balance->setSliderPosition(this->_camera->getWhiteBalance().currentValue);

  ui->horizontalSlider_gain->setMinimum(this->_camera->getGain().minValue);
  ui->horizontalSlider_gain->setMaximum(this->_camera->getGain().maxValue);
  ui->horizontalSlider_gain->setSliderPosition(this->_camera->getGain().currentValue);

  // Set Min Values in UI
  ui->brightness_min_label->setText(QString::number(this->_camera->getBrightness().minValue));
  ui->contrast_min_label->setText(QString::number(this->_camera->getContrast().minValue));
  ui->saturation_min_label->setText(QString::number(this->_camera->getSaturation().minValue));
  ui->exposure_min_label->setText(QString::number(this->_camera->getExposureAbsolute().minValue));
  ui->exposureAuto_min_label->setText(QString::number(this->_camera->getExposureAuto().minValue));
  ui->blacklight_min_label->setText(QString::number(this->_camera->getBlacklightComp().minValue));
  ui->white_balance_min_label->setText(QString::number(this->_camera->getWhiteBalance().minValue));
  ui->gain_min_label->setText(QString::number(this->_camera->getGain().minValue));

  // Set Max Values in UI
  ui->brightness_max_label->setText(QString::number(this->_camera->getBrightness().maxValue));
  ui->contrast_max_label->setText(QString::number(this->_camera->getContrast().maxValue));
  ui->saturation_max_label->setText(QString::number(this->_camera->getSaturation().maxValue));
  ui->exposure_max_label->setText(QString::number(this->_camera->getExposureAbsolute().maxValue));
  ui->exposureAuto_max_label->setText(QString::number(this->_camera->getExposureAuto().maxValue));
  ui->blacklight_max_label->setText(QString::number(this->_camera->getBlacklightComp().maxValue));
  ui->white_balance_max_label->setText(QString::number(this->_camera->getWhiteBalance().maxValue));
  ui->gain_max_label->setText(QString::number(this->_camera->getGain().maxValue));

  // Set Default Values in UI
  ui->brightness_default_label->setText(QString::number(this->_camera->getBrightness().defaultValue));
  ui->contrast_default_label->setText(QString::number(this->_camera->getContrast().defaultValue));
  ui->saturation_default_label->setText(QString::number(this->_camera->getSaturation().defaultValue));
  ui->exposure_default_label->setText(QString::number(this->_camera->getExposureAbsolute().defaultValue));
  ui->exposureAuto_default_label->setText(QString::number(this->_camera->getExposureAuto().defaultValue));
  ui->blacklight_default_label->setText(QString::number(this->_camera->getBlacklightComp().defaultValue));
  ui->white_balance_default_label->setText(QString::number(this->_camera->getWhiteBalance().defaultValue));
  ui->gain_default_label->setText(QString::number(this->_camera->getGain().defaultValue));
  this->_isSetup = false;
}

CameraConfigurationDialog::~CameraConfigurationDialog()
{
  delete ui;
}

void CameraConfigurationDialog::on_horizontalSlider_brightness_valueChanged(int value)
{
  if (!this->_isSetup) {
    ui->brightness_value_label->setText(QString::number(value));
    this->_camera->setBrightness(value);
  }
}

void CameraConfigurationDialog::on_horizontalSlider_contrast_valueChanged(int value)
{
  if (!this->_isSetup) {
    ui->contrast_value_label->setText(QString::number(value));
    this->_camera->setContrast(value);
  }
}

void CameraConfigurationDialog::on_horizontalSlider_saturation_valueChanged(int value)
{
  if (!this->_isSetup) {
    ui->saturation_value_label->setText(QString::number(value));
    this->_camera->setSaturation(value);
  }
}

void CameraConfigurationDialog::on_horizontalSlider_exposure_valueChanged(int value)
{
  if (!this->_isSetup) {
    ui->exposure_value_label->setText(QString::number(value));
    this->_camera->setExposureAbsolute(value);
  }
}

void CameraConfigurationDialog::on_horizontalSlider_blacklight_valueChanged(int value)
{
  if (!this->_isSetup) {
    ui->blacklight_value_label->setText(QString::number(value));
    this->_camera->setBacklightComp(value);
  }
}

void CameraConfigurationDialog::on_horizontalSlider_white_balance_valueChanged(int value)
{
  if (!this->_isSetup) {
    ui->white_balance_value_label->setText(QString::number(value));
    this->_camera->setWhiteBalance(value);
  }
}

void CameraConfigurationDialog::on_horizontalSlider_gain_valueChanged(int value)
{
  if (!this->_isSetup) {
    ui->gain_value_label->setText(QString::number(value));
    this->_camera->setGain(value);
  }
}

void CameraConfigurationDialog::on_white_balance_auto_checkBox_clicked(bool checked)
{
  if (!this->_isSetup) {
    this->_camera->setWhiteBalanceAuto((int) checked);
  }
}

void CameraConfigurationDialog::on_focus_auto_checkBox_clicked(bool checked)
{
  if (!this->_isSetup) {
    this->_camera->setFocusAuto((int) checked);
   }
}

void CameraConfigurationDialog::on_buttonBox_accepted()
{
  this->_camera->saveFile(CAMERA_CONFIG_L_JSON_PATH);
}

void CameraConfigurationDialog::on_setBrigtnessDefaultButton_clicked()
{
  int defaultValue = this->_camera->getBrightness().defaultValue;
  ui->brightness_value_label->setText(QString::number(defaultValue));
  ui->horizontalSlider_brightness->setSliderPosition(defaultValue);
  this->_camera->setBrightness(defaultValue);
}

void CameraConfigurationDialog::on_setContrastDefaultButton_clicked()
{
  int defaultValue = this->_camera->getContrast().defaultValue;
  ui->contrast_value_label->setText(QString::number(defaultValue));
  ui->horizontalSlider_contrast->setSliderPosition(defaultValue);
  this->_camera->setContrast(defaultValue);
}

void CameraConfigurationDialog::on_setSaturationDefaultButton_clicked()
{
  int defaultValue = this->_camera->getSaturation().defaultValue;
  ui->saturation_value_label->setText(QString::number(defaultValue));
  ui->horizontalSlider_saturation->setSliderPosition(defaultValue);
  this->_camera->setContrast(defaultValue);
}

void CameraConfigurationDialog::on_setExposureAutoPriorityDefaultButton_clicked()
{
  int defaultValue = this->_camera->getExposureAutoPriority().defaultValue;
  ui->exposureAutoPriority_checkBox->setChecked(defaultValue);
  this->_camera->setExposureAutoPriority(defaultValue);
}

void CameraConfigurationDialog::on_setExposureDefaultButton_clicked()
{
   int defaultValue = this->_camera->getExposureAbsolute().defaultValue;
   ui->exposure_value_label->setText(QString::number(defaultValue));
   ui->horizontalSlider_exposure->setSliderPosition(defaultValue);
   this->_camera->setExposureAbsolute(defaultValue);
}

void CameraConfigurationDialog::on_setWhiteBalanceDefaultButton_clicked()
{
  int defaultValue = this->_camera->getWhiteBalance().defaultValue;
  ui->white_balance_value_label->setText(QString::number(defaultValue));
  ui->horizontalSlider_white_balance->setSliderPosition(defaultValue);
  this->_camera->setWhiteBalance(defaultValue);
}

void CameraConfigurationDialog::on_setBlacklightDefaultButton_clicked()
{
  int defaultValue = this->_camera->getBlacklightComp().defaultValue;
  ui->blacklight_value_label->setText(QString::number(defaultValue));
  ui->horizontalSlider_blacklight->setSliderPosition(defaultValue);
  this->_camera->setBacklightComp(defaultValue);
}

void CameraConfigurationDialog::on_setGainDefaultButton_clicked()
{
  int defaultValue = this->_camera->getGain().defaultValue;
  ui->gain_value_label->setText(QString::number(defaultValue));
  ui->horizontalSlider_gain->setSliderPosition(defaultValue);
  this->_camera->setGain(defaultValue);
}

void CameraConfigurationDialog::on_setFocusAutoDefaultButton_clicked()
{
  int defaultValue = this->_camera->getFocusAuto().defaultValue;
  ui->focus_auto_checkBox->setChecked(defaultValue);
  this->_camera->setFocusAuto(defaultValue);
}

void CameraConfigurationDialog::on_setExposureAutoDefaultButton_clicked()
{
  int defaultValue = this->_camera->getExposureAuto().defaultValue;
  ui->horizontalSlider_exposureAuto->setSliderPosition(defaultValue);
  this->_camera->setExposureAuto(defaultValue);
}

void CameraConfigurationDialog::on_setWhiteBalanceAutoDefaultButton_clicked()
{
  int defaultValue = this->_camera->getWhiteBalanceAuto().defaultValue;
  ui->white_balance_auto_checkBox->setChecked(defaultValue);
  this->_camera->setWhiteBalanceAuto(defaultValue);
}

void CameraConfigurationDialog::on_setDefaultAll_clicked()
{
  this->on_setExposureAutoDefaultButton_clicked();
  this->on_setExposureDefaultButton_clicked();
  this->on_setFocusAutoDefaultButton_clicked();
  this->on_setGainDefaultButton_clicked();
  this->on_setExposureAutoPriorityDefaultButton_clicked();
  this->on_setSaturationDefaultButton_clicked();
  this->on_setWhiteBalanceAutoDefaultButton_clicked();
  this->on_setWhiteBalanceDefaultButton_clicked();
  this->on_setBlacklightDefaultButton_clicked();
  this->on_setBrigtnessDefaultButton_clicked();
  this->on_setContrastDefaultButton_clicked();
}

void CameraConfigurationDialog::on_pushButton_clicked()
{
  this->_camera->saveFile(CAMERA_CONFIG_D_JSON_PATH);
}

void CameraConfigurationDialog::on_pushButton_readXML_D_clicked()
{
  this->_camera->loadAndApplyFile(CAMERA_CONFIG_D_JSON_PATH);

  ui->horizontalSlider_brightness->setSliderPosition(this->_camera->getBrightness().currentValue);
  ui->horizontalSlider_contrast->setSliderPosition(this->_camera->getContrast().currentValue);
  ui->horizontalSlider_exposure->setSliderPosition(this->_camera->getExposureAbsolute().currentValue);
  ui->horizontalSlider_saturation->setSliderPosition(this->_camera->getSaturation().currentValue);
  ui->horizontalSlider_blacklight->setSliderPosition(this->_camera->getBlacklightComp().currentValue);
  ui->horizontalSlider_gain->setSliderPosition(this->_camera->getGain().currentValue);
  ui->horizontalSlider_white_balance->setSliderPosition(this->_camera->getWhiteBalance().currentValue);
  ui->focus_auto_checkBox->setChecked(this->_camera->getFocusAuto().currentValue);
  ui->white_balance_auto_checkBox->setChecked(this->_camera->getWhiteBalanceAuto().currentValue);
  ui->horizontalSlider_exposureAuto->setSliderPosition(this->_camera->getExposureAuto().currentValue);
  ui->exposureAutoPriority_checkBox->setChecked(this->_camera->getExposureAutoPriority().currentValue);
}

void CameraConfigurationDialog::on_pushButton_readXML_L_clicked()
{
  this->_camera->loadAndApplyFile(CAMERA_CONFIG_L_JSON_PATH);

  ui->horizontalSlider_brightness->setSliderPosition(this->_camera->getBrightness().currentValue);
  ui->horizontalSlider_contrast->setSliderPosition(this->_camera->getContrast().currentValue);
  ui->horizontalSlider_exposure->setSliderPosition(this->_camera->getExposureAbsolute().currentValue);
  ui->exposureAutoPriority_checkBox->setChecked(this->_camera->getExposureAutoPriority().currentValue);
  ui->horizontalSlider_saturation->setSliderPosition(this->_camera->getSaturation().currentValue);
  ui->horizontalSlider_blacklight->setSliderPosition(this->_camera->getBlacklightComp().currentValue);
  ui->horizontalSlider_gain->setSliderPosition(this->_camera->getGain().currentValue);
  ui->horizontalSlider_white_balance->setSliderPosition(this->_camera->getWhiteBalance().currentValue);
  ui->focus_auto_checkBox->setChecked(this->_camera->getFocusAuto().currentValue);
  ui->white_balance_auto_checkBox->setChecked(this->_camera->getWhiteBalanceAuto().currentValue);
  ui->horizontalSlider_exposureAuto->setSliderPosition(this->_camera->getExposureAuto().currentValue);
  ui->exposureAutoPriority_checkBox->setChecked(this->_camera->getExposureAutoPriority().currentValue);
}

void CameraConfigurationDialog::on_buttonBox_rejected()
{
  //this->_camera->loadAndApplyXML(CAMERA_CONFIG_L_XML_PATH);

}

void CameraConfigurationDialog::on_horizontalSlider_exposureAuto_valueChanged(int value)
{
  if (!this->_isSetup) {
    this->_camera->setExposureAuto(value);
  }
}

void CameraConfigurationDialog::on_exposureAutoPriority_checkBox_clicked(bool checked)
{
  if (!this->_isSetup) {
     this->_camera->setExposureAutoPriority((int) checked);
  }
}
