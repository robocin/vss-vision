/********************************************************************************
** Form generated from reading UI file 'cameraconfigurationdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERACONFIGURATIONDIALOG_H
#define UI_CAMERACONFIGURATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraConfigurationDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *contrast_value_label;
    QLabel *brightness_value_label;
    QLabel *saturation_value_label;
    QLabel *label_7;
    QSlider *horizontalSlider_brightness;
    QSlider *horizontalSlider_contrast;
    QSlider *horizontalSlider_saturation;
    QLabel *label_4;
    QSlider *horizontalSlider_exposure;
    QLabel *exposure_value_label;
    QLabel *brightness_min_label;
    QLabel *contrast_min_label;
    QLabel *saturation_min_label;
    QLabel *exposure_min_label;
    QLabel *brightness_max_label;
    QLabel *contrast_max_label;
    QLabel *saturation_max_label;
    QLabel *exposure_max_label;
    QLabel *brightness_default_label;
    QLabel *contrast_default_label;
    QLabel *saturation_default_label;
    QLabel *exposure_default_label;
    QLabel *min_label;
    QLabel *max_label;
    QLabel *default_label;
    QPushButton *setBrigtnessDefaultButton;
    QPushButton *setContrastDefaultButton;
    QPushButton *setSaturationDefaultButton;
    QPushButton *setExposureDefaultButton;
    QPushButton *setDefaultAll;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_readXML_D;
    QPushButton *pushButton_readXML_L;
    QDialogButtonBox *buttonBox;
    QLabel *label_5;
    QLabel *label_6;
    QCheckBox *focus_auto_checkBox;
    QLabel *label_8;
    QLabel *white_balance_min_label;
    QSlider *horizontalSlider_white_balance;
    QLabel *white_balance_max_label;
    QLabel *white_balance_default_label;
    QPushButton *setExposureAutoDefaultButton;
    QLabel *white_balance_value_label;
    QPushButton *setWhiteBalanceDefaultButton;
    QLabel *label_9;
    QCheckBox *white_balance_auto_checkBox;
    QPushButton *setWhiteBalanceAutoDefaultButton;
    QLabel *label_10;
    QLabel *blacklight_min_label;
    QSlider *horizontalSlider_blacklight;
    QLabel *blacklight_value_label;
    QLabel *blacklight_max_label;
    QLabel *blacklight_default_label;
    QPushButton *setBlacklightDefaultButton;
    QPushButton *setFocusAutoDefaultButton;
    QLabel *label_11;
    QLabel *gain_min_label;
    QSlider *horizontalSlider_gain;
    QLabel *gain_value_label;
    QLabel *gain_max_label;
    QLabel *gain_default_label;
    QPushButton *setGainDefaultButton;
    QLabel *exposureAuto_min_label;
    QSlider *horizontalSlider_exposureAuto;
    QLabel *exposureAuto_max_label;
    QLabel *exposureAuto_default_label;
    QLabel *exposureAuto_value_label;
    QCheckBox *exposureAutoPriority_checkBox;
    QPushButton *setExposureAutoPriorityDefaultButton;

    void setupUi(QDialog *CameraConfigurationDialog)
    {
        if (CameraConfigurationDialog->objectName().isEmpty())
            CameraConfigurationDialog->setObjectName(QString::fromUtf8("CameraConfigurationDialog"));
        CameraConfigurationDialog->resize(547, 646);
        label = new QLabel(CameraConfigurationDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1, 40, 100, 30));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(CameraConfigurationDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(-5, 90, 100, 30));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(CameraConfigurationDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(0, 140, 100, 30));
        label_3->setAlignment(Qt::AlignCenter);
        contrast_value_label = new QLabel(CameraConfigurationDialog);
        contrast_value_label->setObjectName(QString::fromUtf8("contrast_value_label"));
        contrast_value_label->setGeometry(QRect(240, 115, 67, 17));
        contrast_value_label->setAlignment(Qt::AlignCenter);
        brightness_value_label = new QLabel(CameraConfigurationDialog);
        brightness_value_label->setObjectName(QString::fromUtf8("brightness_value_label"));
        brightness_value_label->setGeometry(QRect(240, 65, 67, 17));
        brightness_value_label->setAlignment(Qt::AlignCenter);
        saturation_value_label = new QLabel(CameraConfigurationDialog);
        saturation_value_label->setObjectName(QString::fromUtf8("saturation_value_label"));
        saturation_value_label->setGeometry(QRect(240, 165, 67, 17));
        saturation_value_label->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(CameraConfigurationDialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(-7, 190, 161, 30));
        label_7->setAlignment(Qt::AlignCenter);
        horizontalSlider_brightness = new QSlider(CameraConfigurationDialog);
        horizontalSlider_brightness->setObjectName(QString::fromUtf8("horizontalSlider_brightness"));
        horizontalSlider_brightness->setGeometry(QRect(190, 50, 160, 16));
        horizontalSlider_brightness->setCursor(QCursor(Qt::ArrowCursor));
        horizontalSlider_brightness->setMouseTracking(false);
        horizontalSlider_brightness->setFocusPolicy(Qt::StrongFocus);
        horizontalSlider_brightness->setContextMenuPolicy(Qt::ActionsContextMenu);
        horizontalSlider_brightness->setMaximum(100);
        horizontalSlider_brightness->setOrientation(Qt::Horizontal);
        horizontalSlider_contrast = new QSlider(CameraConfigurationDialog);
        horizontalSlider_contrast->setObjectName(QString::fromUtf8("horizontalSlider_contrast"));
        horizontalSlider_contrast->setGeometry(QRect(190, 100, 160, 16));
        horizontalSlider_contrast->setOrientation(Qt::Horizontal);
        horizontalSlider_saturation = new QSlider(CameraConfigurationDialog);
        horizontalSlider_saturation->setObjectName(QString::fromUtf8("horizontalSlider_saturation"));
        horizontalSlider_saturation->setGeometry(QRect(190, 150, 160, 16));
        horizontalSlider_saturation->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(CameraConfigurationDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(-2, 290, 111, 30));
        label_4->setAlignment(Qt::AlignCenter);
        horizontalSlider_exposure = new QSlider(CameraConfigurationDialog);
        horizontalSlider_exposure->setObjectName(QString::fromUtf8("horizontalSlider_exposure"));
        horizontalSlider_exposure->setGeometry(QRect(189, 297, 160, 16));
        horizontalSlider_exposure->setOrientation(Qt::Horizontal);
        exposure_value_label = new QLabel(CameraConfigurationDialog);
        exposure_value_label->setObjectName(QString::fromUtf8("exposure_value_label"));
        exposure_value_label->setGeometry(QRect(240, 311, 67, 17));
        exposure_value_label->setAlignment(Qt::AlignCenter);
        brightness_min_label = new QLabel(CameraConfigurationDialog);
        brightness_min_label->setObjectName(QString::fromUtf8("brightness_min_label"));
        brightness_min_label->setGeometry(QRect(130, 50, 67, 17));
        brightness_min_label->setAlignment(Qt::AlignCenter);
        contrast_min_label = new QLabel(CameraConfigurationDialog);
        contrast_min_label->setObjectName(QString::fromUtf8("contrast_min_label"));
        contrast_min_label->setGeometry(QRect(130, 100, 67, 17));
        contrast_min_label->setAlignment(Qt::AlignCenter);
        saturation_min_label = new QLabel(CameraConfigurationDialog);
        saturation_min_label->setObjectName(QString::fromUtf8("saturation_min_label"));
        saturation_min_label->setGeometry(QRect(130, 150, 67, 17));
        saturation_min_label->setAlignment(Qt::AlignCenter);
        exposure_min_label = new QLabel(CameraConfigurationDialog);
        exposure_min_label->setObjectName(QString::fromUtf8("exposure_min_label"));
        exposure_min_label->setGeometry(QRect(130, 296, 67, 17));
        exposure_min_label->setAlignment(Qt::AlignCenter);
        brightness_max_label = new QLabel(CameraConfigurationDialog);
        brightness_max_label->setObjectName(QString::fromUtf8("brightness_max_label"));
        brightness_max_label->setGeometry(QRect(350, 50, 67, 17));
        brightness_max_label->setAlignment(Qt::AlignCenter);
        contrast_max_label = new QLabel(CameraConfigurationDialog);
        contrast_max_label->setObjectName(QString::fromUtf8("contrast_max_label"));
        contrast_max_label->setGeometry(QRect(350, 100, 67, 17));
        contrast_max_label->setAlignment(Qt::AlignCenter);
        saturation_max_label = new QLabel(CameraConfigurationDialog);
        saturation_max_label->setObjectName(QString::fromUtf8("saturation_max_label"));
        saturation_max_label->setGeometry(QRect(350, 150, 67, 17));
        saturation_max_label->setAlignment(Qt::AlignCenter);
        exposure_max_label = new QLabel(CameraConfigurationDialog);
        exposure_max_label->setObjectName(QString::fromUtf8("exposure_max_label"));
        exposure_max_label->setGeometry(QRect(352, 296, 67, 17));
        exposure_max_label->setAlignment(Qt::AlignCenter);
        brightness_default_label = new QLabel(CameraConfigurationDialog);
        brightness_default_label->setObjectName(QString::fromUtf8("brightness_default_label"));
        brightness_default_label->setGeometry(QRect(410, 50, 67, 17));
        brightness_default_label->setAlignment(Qt::AlignCenter);
        contrast_default_label = new QLabel(CameraConfigurationDialog);
        contrast_default_label->setObjectName(QString::fromUtf8("contrast_default_label"));
        contrast_default_label->setGeometry(QRect(410, 100, 67, 17));
        contrast_default_label->setAlignment(Qt::AlignCenter);
        saturation_default_label = new QLabel(CameraConfigurationDialog);
        saturation_default_label->setObjectName(QString::fromUtf8("saturation_default_label"));
        saturation_default_label->setGeometry(QRect(410, 150, 67, 17));
        saturation_default_label->setAlignment(Qt::AlignCenter);
        exposure_default_label = new QLabel(CameraConfigurationDialog);
        exposure_default_label->setObjectName(QString::fromUtf8("exposure_default_label"));
        exposure_default_label->setGeometry(QRect(412, 296, 67, 17));
        exposure_default_label->setAlignment(Qt::AlignCenter);
        min_label = new QLabel(CameraConfigurationDialog);
        min_label->setObjectName(QString::fromUtf8("min_label"));
        min_label->setGeometry(QRect(130, 20, 67, 17));
        min_label->setAlignment(Qt::AlignCenter);
        max_label = new QLabel(CameraConfigurationDialog);
        max_label->setObjectName(QString::fromUtf8("max_label"));
        max_label->setGeometry(QRect(350, 20, 67, 17));
        max_label->setAlignment(Qt::AlignCenter);
        default_label = new QLabel(CameraConfigurationDialog);
        default_label->setObjectName(QString::fromUtf8("default_label"));
        default_label->setGeometry(QRect(410, 20, 67, 17));
        default_label->setAlignment(Qt::AlignCenter);
        setBrigtnessDefaultButton = new QPushButton(CameraConfigurationDialog);
        setBrigtnessDefaultButton->setObjectName(QString::fromUtf8("setBrigtnessDefaultButton"));
        setBrigtnessDefaultButton->setGeometry(QRect(474, 40, 61, 25));
        setContrastDefaultButton = new QPushButton(CameraConfigurationDialog);
        setContrastDefaultButton->setObjectName(QString::fromUtf8("setContrastDefaultButton"));
        setContrastDefaultButton->setGeometry(QRect(474, 90, 61, 25));
        setSaturationDefaultButton = new QPushButton(CameraConfigurationDialog);
        setSaturationDefaultButton->setObjectName(QString::fromUtf8("setSaturationDefaultButton"));
        setSaturationDefaultButton->setGeometry(QRect(474, 140, 61, 25));
        setExposureDefaultButton = new QPushButton(CameraConfigurationDialog);
        setExposureDefaultButton->setObjectName(QString::fromUtf8("setExposureDefaultButton"));
        setExposureDefaultButton->setGeometry(QRect(474, 289, 61, 25));
        setDefaultAll = new QPushButton(CameraConfigurationDialog);
        setDefaultAll->setObjectName(QString::fromUtf8("setDefaultAll"));
        setDefaultAll->setGeometry(QRect(440, 580, 101, 25));
        layoutWidget = new QWidget(CameraConfigurationDialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 610, 536, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_readXML_D = new QPushButton(layoutWidget);
        pushButton_readXML_D->setObjectName(QString::fromUtf8("pushButton_readXML_D"));

        horizontalLayout->addWidget(pushButton_readXML_D);

        pushButton_readXML_L = new QPushButton(layoutWidget);
        pushButton_readXML_L->setObjectName(QString::fromUtf8("pushButton_readXML_L"));

        horizontalLayout->addWidget(pushButton_readXML_L);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);

        label_5 = new QLabel(CameraConfigurationDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(19, 246, 101, 17));
        label_6 = new QLabel(CameraConfigurationDialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 496, 101, 17));
        focus_auto_checkBox = new QCheckBox(CameraConfigurationDialog);
        focus_auto_checkBox->setObjectName(QString::fromUtf8("focus_auto_checkBox"));
        focus_auto_checkBox->setGeometry(QRect(188, 493, 81, 23));
        label_8 = new QLabel(CameraConfigurationDialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 397, 101, 17));
        white_balance_min_label = new QLabel(CameraConfigurationDialog);
        white_balance_min_label->setObjectName(QString::fromUtf8("white_balance_min_label"));
        white_balance_min_label->setGeometry(QRect(130, 397, 67, 17));
        white_balance_min_label->setAlignment(Qt::AlignCenter);
        horizontalSlider_white_balance = new QSlider(CameraConfigurationDialog);
        horizontalSlider_white_balance->setObjectName(QString::fromUtf8("horizontalSlider_white_balance"));
        horizontalSlider_white_balance->setGeometry(QRect(189, 397, 160, 16));
        horizontalSlider_white_balance->setOrientation(Qt::Horizontal);
        white_balance_max_label = new QLabel(CameraConfigurationDialog);
        white_balance_max_label->setObjectName(QString::fromUtf8("white_balance_max_label"));
        white_balance_max_label->setGeometry(QRect(352, 397, 67, 17));
        white_balance_max_label->setAlignment(Qt::AlignCenter);
        white_balance_default_label = new QLabel(CameraConfigurationDialog);
        white_balance_default_label->setObjectName(QString::fromUtf8("white_balance_default_label"));
        white_balance_default_label->setGeometry(QRect(410, 397, 67, 17));
        white_balance_default_label->setAlignment(Qt::AlignCenter);
        setExposureAutoDefaultButton = new QPushButton(CameraConfigurationDialog);
        setExposureAutoDefaultButton->setObjectName(QString::fromUtf8("setExposureAutoDefaultButton"));
        setExposureAutoDefaultButton->setGeometry(QRect(474, 240, 61, 25));
        white_balance_value_label = new QLabel(CameraConfigurationDialog);
        white_balance_value_label->setObjectName(QString::fromUtf8("white_balance_value_label"));
        white_balance_value_label->setGeometry(QRect(237, 407, 67, 17));
        white_balance_value_label->setAlignment(Qt::AlignCenter);
        setWhiteBalanceDefaultButton = new QPushButton(CameraConfigurationDialog);
        setWhiteBalanceDefaultButton->setObjectName(QString::fromUtf8("setWhiteBalanceDefaultButton"));
        setWhiteBalanceDefaultButton->setGeometry(QRect(475, 392, 61, 25));
        label_9 = new QLabel(CameraConfigurationDialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(19, 345, 111, 20));
        white_balance_auto_checkBox = new QCheckBox(CameraConfigurationDialog);
        white_balance_auto_checkBox->setObjectName(QString::fromUtf8("white_balance_auto_checkBox"));
        white_balance_auto_checkBox->setGeometry(QRect(189, 343, 92, 23));
        setWhiteBalanceAutoDefaultButton = new QPushButton(CameraConfigurationDialog);
        setWhiteBalanceAutoDefaultButton->setObjectName(QString::fromUtf8("setWhiteBalanceAutoDefaultButton"));
        setWhiteBalanceAutoDefaultButton->setGeometry(QRect(474, 340, 61, 25));
        label_10 = new QLabel(CameraConfigurationDialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 447, 101, 17));
        blacklight_min_label = new QLabel(CameraConfigurationDialog);
        blacklight_min_label->setObjectName(QString::fromUtf8("blacklight_min_label"));
        blacklight_min_label->setGeometry(QRect(130, 447, 67, 17));
        blacklight_min_label->setAlignment(Qt::AlignCenter);
        horizontalSlider_blacklight = new QSlider(CameraConfigurationDialog);
        horizontalSlider_blacklight->setObjectName(QString::fromUtf8("horizontalSlider_blacklight"));
        horizontalSlider_blacklight->setGeometry(QRect(190, 447, 160, 16));
        horizontalSlider_blacklight->setOrientation(Qt::Horizontal);
        blacklight_value_label = new QLabel(CameraConfigurationDialog);
        blacklight_value_label->setObjectName(QString::fromUtf8("blacklight_value_label"));
        blacklight_value_label->setGeometry(QRect(238, 457, 67, 17));
        blacklight_value_label->setAlignment(Qt::AlignCenter);
        blacklight_max_label = new QLabel(CameraConfigurationDialog);
        blacklight_max_label->setObjectName(QString::fromUtf8("blacklight_max_label"));
        blacklight_max_label->setGeometry(QRect(352, 447, 67, 17));
        blacklight_max_label->setAlignment(Qt::AlignCenter);
        blacklight_default_label = new QLabel(CameraConfigurationDialog);
        blacklight_default_label->setObjectName(QString::fromUtf8("blacklight_default_label"));
        blacklight_default_label->setGeometry(QRect(411, 447, 67, 17));
        blacklight_default_label->setAlignment(Qt::AlignCenter);
        setBlacklightDefaultButton = new QPushButton(CameraConfigurationDialog);
        setBlacklightDefaultButton->setObjectName(QString::fromUtf8("setBlacklightDefaultButton"));
        setBlacklightDefaultButton->setGeometry(QRect(476, 440, 61, 25));
        setFocusAutoDefaultButton = new QPushButton(CameraConfigurationDialog);
        setFocusAutoDefaultButton->setObjectName(QString::fromUtf8("setFocusAutoDefaultButton"));
        setFocusAutoDefaultButton->setGeometry(QRect(476, 486, 61, 25));
        label_11 = new QLabel(CameraConfigurationDialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 544, 101, 17));
        gain_min_label = new QLabel(CameraConfigurationDialog);
        gain_min_label->setObjectName(QString::fromUtf8("gain_min_label"));
        gain_min_label->setGeometry(QRect(130, 544, 67, 17));
        gain_min_label->setAlignment(Qt::AlignCenter);
        horizontalSlider_gain = new QSlider(CameraConfigurationDialog);
        horizontalSlider_gain->setObjectName(QString::fromUtf8("horizontalSlider_gain"));
        horizontalSlider_gain->setGeometry(QRect(190, 544, 160, 16));
        horizontalSlider_gain->setOrientation(Qt::Horizontal);
        gain_value_label = new QLabel(CameraConfigurationDialog);
        gain_value_label->setObjectName(QString::fromUtf8("gain_value_label"));
        gain_value_label->setGeometry(QRect(240, 554, 67, 17));
        gain_value_label->setAlignment(Qt::AlignCenter);
        gain_max_label = new QLabel(CameraConfigurationDialog);
        gain_max_label->setObjectName(QString::fromUtf8("gain_max_label"));
        gain_max_label->setGeometry(QRect(353, 544, 67, 17));
        gain_max_label->setAlignment(Qt::AlignCenter);
        gain_default_label = new QLabel(CameraConfigurationDialog);
        gain_default_label->setObjectName(QString::fromUtf8("gain_default_label"));
        gain_default_label->setGeometry(QRect(410, 544, 67, 17));
        gain_default_label->setAlignment(Qt::AlignCenter);
        setGainDefaultButton = new QPushButton(CameraConfigurationDialog);
        setGainDefaultButton->setObjectName(QString::fromUtf8("setGainDefaultButton"));
        setGainDefaultButton->setGeometry(QRect(475, 537, 61, 25));
        exposureAuto_min_label = new QLabel(CameraConfigurationDialog);
        exposureAuto_min_label->setObjectName(QString::fromUtf8("exposureAuto_min_label"));
        exposureAuto_min_label->setGeometry(QRect(130, 250, 67, 17));
        exposureAuto_min_label->setAlignment(Qt::AlignCenter);
        horizontalSlider_exposureAuto = new QSlider(CameraConfigurationDialog);
        horizontalSlider_exposureAuto->setObjectName(QString::fromUtf8("horizontalSlider_exposureAuto"));
        horizontalSlider_exposureAuto->setGeometry(QRect(190, 250, 160, 16));
        horizontalSlider_exposureAuto->setOrientation(Qt::Horizontal);
        exposureAuto_max_label = new QLabel(CameraConfigurationDialog);
        exposureAuto_max_label->setObjectName(QString::fromUtf8("exposureAuto_max_label"));
        exposureAuto_max_label->setGeometry(QRect(350, 250, 67, 17));
        exposureAuto_max_label->setAlignment(Qt::AlignCenter);
        exposureAuto_default_label = new QLabel(CameraConfigurationDialog);
        exposureAuto_default_label->setObjectName(QString::fromUtf8("exposureAuto_default_label"));
        exposureAuto_default_label->setGeometry(QRect(410, 250, 67, 17));
        exposureAuto_default_label->setAlignment(Qt::AlignCenter);
        exposureAuto_value_label = new QLabel(CameraConfigurationDialog);
        exposureAuto_value_label->setObjectName(QString::fromUtf8("exposureAuto_value_label"));
        exposureAuto_value_label->setGeometry(QRect(240, 270, 67, 17));
        exposureAuto_value_label->setAlignment(Qt::AlignCenter);
        exposureAutoPriority_checkBox = new QCheckBox(CameraConfigurationDialog);
        exposureAutoPriority_checkBox->setObjectName(QString::fromUtf8("exposureAutoPriority_checkBox"));
        exposureAutoPriority_checkBox->setGeometry(QRect(189, 195, 92, 23));
        setExposureAutoPriorityDefaultButton = new QPushButton(CameraConfigurationDialog);
        setExposureAutoPriorityDefaultButton->setObjectName(QString::fromUtf8("setExposureAutoPriorityDefaultButton"));
        setExposureAutoPriorityDefaultButton->setGeometry(QRect(474, 190, 61, 25));

        retranslateUi(CameraConfigurationDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CameraConfigurationDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CameraConfigurationDialog, SLOT(reject()));
        QObject::connect(horizontalSlider_exposureAuto, SIGNAL(valueChanged(int)), exposureAuto_value_label, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(CameraConfigurationDialog);
    } // setupUi

    void retranslateUi(QDialog *CameraConfigurationDialog)
    {
        CameraConfigurationDialog->setWindowTitle(QApplication::translate("CameraConfigurationDialog", "Camera Configuration", nullptr));
        label->setText(QApplication::translate("CameraConfigurationDialog", "Brightness", nullptr));
        label_2->setText(QApplication::translate("CameraConfigurationDialog", "Contrast", nullptr));
        label_3->setText(QApplication::translate("CameraConfigurationDialog", "Saturation", nullptr));
        contrast_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        brightness_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        saturation_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        label_7->setText(QApplication::translate("CameraConfigurationDialog", "ExposurePriority*", nullptr));
        label_4->setText(QApplication::translate("CameraConfigurationDialog", "Exposure*", nullptr));
        exposure_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        brightness_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        contrast_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        saturation_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        exposure_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        brightness_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        contrast_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        saturation_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        exposure_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        brightness_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        contrast_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        saturation_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        exposure_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        min_label->setText(QApplication::translate("CameraConfigurationDialog", "Min", nullptr));
        max_label->setText(QApplication::translate("CameraConfigurationDialog", "Max", nullptr));
        default_label->setText(QApplication::translate("CameraConfigurationDialog", "Default", nullptr));
        setBrigtnessDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", nullptr));
        setContrastDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", nullptr));
        setSaturationDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", nullptr));
        setExposureDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", nullptr));
        setDefaultAll->setText(QApplication::translate("CameraConfigurationDialog", "All Default", nullptr));
        pushButton->setText(QApplication::translate("CameraConfigurationDialog", "Save D XML", nullptr));
        pushButton_readXML_D->setText(QApplication::translate("CameraConfigurationDialog", "Read D XML", nullptr));
        pushButton_readXML_L->setText(QApplication::translate("CameraConfigurationDialog", "Read Last XML", nullptr));
        label_5->setText(QApplication::translate("CameraConfigurationDialog", "Exposure_auto", nullptr));
        label_6->setText(QApplication::translate("CameraConfigurationDialog", "Focus_auto", nullptr));
        focus_auto_checkBox->setText(QApplication::translate("CameraConfigurationDialog", "Enabled", nullptr));
        label_8->setText(QApplication::translate("CameraConfigurationDialog", "WhiteBalance", nullptr));
        white_balance_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        white_balance_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        white_balance_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        setExposureAutoDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", nullptr));
        white_balance_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        setWhiteBalanceDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", nullptr));
        label_9->setText(QApplication::translate("CameraConfigurationDialog", "WhiteBalanceAuto", nullptr));
        white_balance_auto_checkBox->setText(QApplication::translate("CameraConfigurationDialog", "Enabled", nullptr));
        setWhiteBalanceAutoDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", nullptr));
        label_10->setText(QApplication::translate("CameraConfigurationDialog", "Blacklight", nullptr));
        blacklight_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        blacklight_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        blacklight_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        blacklight_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        setBlacklightDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", nullptr));
        setFocusAutoDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", nullptr));
        label_11->setText(QApplication::translate("CameraConfigurationDialog", "Gain", nullptr));
        gain_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        gain_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        gain_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        gain_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        setGainDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", nullptr));
        exposureAuto_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        exposureAuto_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        exposureAuto_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        exposureAuto_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", nullptr));
        exposureAutoPriority_checkBox->setText(QApplication::translate("CameraConfigurationDialog", "Enabled", nullptr));
        setExposureAutoPriorityDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraConfigurationDialog: public Ui_CameraConfigurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERACONFIGURATIONDIALOG_H
