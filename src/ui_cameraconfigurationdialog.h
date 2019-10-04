/********************************************************************************
** Form generated from reading UI file 'cameraconfigurationdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERACONFIGURATIONDIALOG_H
#define UI_CAMERACONFIGURATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            CameraConfigurationDialog->setObjectName(QStringLiteral("CameraConfigurationDialog"));
        CameraConfigurationDialog->resize(547, 646);
        label = new QLabel(CameraConfigurationDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(1, 40, 100, 30));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(CameraConfigurationDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(-5, 90, 100, 30));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(CameraConfigurationDialog);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(0, 140, 100, 30));
        label_3->setAlignment(Qt::AlignCenter);
        contrast_value_label = new QLabel(CameraConfigurationDialog);
        contrast_value_label->setObjectName(QStringLiteral("contrast_value_label"));
        contrast_value_label->setGeometry(QRect(240, 115, 67, 17));
        contrast_value_label->setAlignment(Qt::AlignCenter);
        brightness_value_label = new QLabel(CameraConfigurationDialog);
        brightness_value_label->setObjectName(QStringLiteral("brightness_value_label"));
        brightness_value_label->setGeometry(QRect(240, 65, 67, 17));
        brightness_value_label->setAlignment(Qt::AlignCenter);
        saturation_value_label = new QLabel(CameraConfigurationDialog);
        saturation_value_label->setObjectName(QStringLiteral("saturation_value_label"));
        saturation_value_label->setGeometry(QRect(240, 165, 67, 17));
        saturation_value_label->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(CameraConfigurationDialog);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(-7, 190, 161, 30));
        label_7->setAlignment(Qt::AlignCenter);
        horizontalSlider_brightness = new QSlider(CameraConfigurationDialog);
        horizontalSlider_brightness->setObjectName(QStringLiteral("horizontalSlider_brightness"));
        horizontalSlider_brightness->setGeometry(QRect(190, 50, 160, 16));
        horizontalSlider_brightness->setCursor(QCursor(Qt::ArrowCursor));
        horizontalSlider_brightness->setMouseTracking(false);
        horizontalSlider_brightness->setFocusPolicy(Qt::StrongFocus);
        horizontalSlider_brightness->setContextMenuPolicy(Qt::ActionsContextMenu);
        horizontalSlider_brightness->setMaximum(100);
        horizontalSlider_brightness->setOrientation(Qt::Horizontal);
        horizontalSlider_contrast = new QSlider(CameraConfigurationDialog);
        horizontalSlider_contrast->setObjectName(QStringLiteral("horizontalSlider_contrast"));
        horizontalSlider_contrast->setGeometry(QRect(190, 100, 160, 16));
        horizontalSlider_contrast->setOrientation(Qt::Horizontal);
        horizontalSlider_saturation = new QSlider(CameraConfigurationDialog);
        horizontalSlider_saturation->setObjectName(QStringLiteral("horizontalSlider_saturation"));
        horizontalSlider_saturation->setGeometry(QRect(190, 150, 160, 16));
        horizontalSlider_saturation->setOrientation(Qt::Horizontal);
        label_4 = new QLabel(CameraConfigurationDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(-2, 290, 111, 30));
        label_4->setAlignment(Qt::AlignCenter);
        horizontalSlider_exposure = new QSlider(CameraConfigurationDialog);
        horizontalSlider_exposure->setObjectName(QStringLiteral("horizontalSlider_exposure"));
        horizontalSlider_exposure->setGeometry(QRect(189, 297, 160, 16));
        horizontalSlider_exposure->setOrientation(Qt::Horizontal);
        exposure_value_label = new QLabel(CameraConfigurationDialog);
        exposure_value_label->setObjectName(QStringLiteral("exposure_value_label"));
        exposure_value_label->setGeometry(QRect(240, 311, 67, 17));
        exposure_value_label->setAlignment(Qt::AlignCenter);
        brightness_min_label = new QLabel(CameraConfigurationDialog);
        brightness_min_label->setObjectName(QStringLiteral("brightness_min_label"));
        brightness_min_label->setGeometry(QRect(130, 50, 67, 17));
        brightness_min_label->setAlignment(Qt::AlignCenter);
        contrast_min_label = new QLabel(CameraConfigurationDialog);
        contrast_min_label->setObjectName(QStringLiteral("contrast_min_label"));
        contrast_min_label->setGeometry(QRect(130, 100, 67, 17));
        contrast_min_label->setAlignment(Qt::AlignCenter);
        saturation_min_label = new QLabel(CameraConfigurationDialog);
        saturation_min_label->setObjectName(QStringLiteral("saturation_min_label"));
        saturation_min_label->setGeometry(QRect(130, 150, 67, 17));
        saturation_min_label->setAlignment(Qt::AlignCenter);
        exposure_min_label = new QLabel(CameraConfigurationDialog);
        exposure_min_label->setObjectName(QStringLiteral("exposure_min_label"));
        exposure_min_label->setGeometry(QRect(130, 296, 67, 17));
        exposure_min_label->setAlignment(Qt::AlignCenter);
        brightness_max_label = new QLabel(CameraConfigurationDialog);
        brightness_max_label->setObjectName(QStringLiteral("brightness_max_label"));
        brightness_max_label->setGeometry(QRect(350, 50, 67, 17));
        brightness_max_label->setAlignment(Qt::AlignCenter);
        contrast_max_label = new QLabel(CameraConfigurationDialog);
        contrast_max_label->setObjectName(QStringLiteral("contrast_max_label"));
        contrast_max_label->setGeometry(QRect(350, 100, 67, 17));
        contrast_max_label->setAlignment(Qt::AlignCenter);
        saturation_max_label = new QLabel(CameraConfigurationDialog);
        saturation_max_label->setObjectName(QStringLiteral("saturation_max_label"));
        saturation_max_label->setGeometry(QRect(350, 150, 67, 17));
        saturation_max_label->setAlignment(Qt::AlignCenter);
        exposure_max_label = new QLabel(CameraConfigurationDialog);
        exposure_max_label->setObjectName(QStringLiteral("exposure_max_label"));
        exposure_max_label->setGeometry(QRect(352, 296, 67, 17));
        exposure_max_label->setAlignment(Qt::AlignCenter);
        brightness_default_label = new QLabel(CameraConfigurationDialog);
        brightness_default_label->setObjectName(QStringLiteral("brightness_default_label"));
        brightness_default_label->setGeometry(QRect(410, 50, 67, 17));
        brightness_default_label->setAlignment(Qt::AlignCenter);
        contrast_default_label = new QLabel(CameraConfigurationDialog);
        contrast_default_label->setObjectName(QStringLiteral("contrast_default_label"));
        contrast_default_label->setGeometry(QRect(410, 100, 67, 17));
        contrast_default_label->setAlignment(Qt::AlignCenter);
        saturation_default_label = new QLabel(CameraConfigurationDialog);
        saturation_default_label->setObjectName(QStringLiteral("saturation_default_label"));
        saturation_default_label->setGeometry(QRect(410, 150, 67, 17));
        saturation_default_label->setAlignment(Qt::AlignCenter);
        exposure_default_label = new QLabel(CameraConfigurationDialog);
        exposure_default_label->setObjectName(QStringLiteral("exposure_default_label"));
        exposure_default_label->setGeometry(QRect(412, 296, 67, 17));
        exposure_default_label->setAlignment(Qt::AlignCenter);
        min_label = new QLabel(CameraConfigurationDialog);
        min_label->setObjectName(QStringLiteral("min_label"));
        min_label->setGeometry(QRect(130, 20, 67, 17));
        min_label->setAlignment(Qt::AlignCenter);
        max_label = new QLabel(CameraConfigurationDialog);
        max_label->setObjectName(QStringLiteral("max_label"));
        max_label->setGeometry(QRect(350, 20, 67, 17));
        max_label->setAlignment(Qt::AlignCenter);
        default_label = new QLabel(CameraConfigurationDialog);
        default_label->setObjectName(QStringLiteral("default_label"));
        default_label->setGeometry(QRect(410, 20, 67, 17));
        default_label->setAlignment(Qt::AlignCenter);
        setBrigtnessDefaultButton = new QPushButton(CameraConfigurationDialog);
        setBrigtnessDefaultButton->setObjectName(QStringLiteral("setBrigtnessDefaultButton"));
        setBrigtnessDefaultButton->setGeometry(QRect(474, 40, 61, 25));
        setContrastDefaultButton = new QPushButton(CameraConfigurationDialog);
        setContrastDefaultButton->setObjectName(QStringLiteral("setContrastDefaultButton"));
        setContrastDefaultButton->setGeometry(QRect(474, 90, 61, 25));
        setSaturationDefaultButton = new QPushButton(CameraConfigurationDialog);
        setSaturationDefaultButton->setObjectName(QStringLiteral("setSaturationDefaultButton"));
        setSaturationDefaultButton->setGeometry(QRect(474, 140, 61, 25));
        setExposureDefaultButton = new QPushButton(CameraConfigurationDialog);
        setExposureDefaultButton->setObjectName(QStringLiteral("setExposureDefaultButton"));
        setExposureDefaultButton->setGeometry(QRect(474, 289, 61, 25));
        setDefaultAll = new QPushButton(CameraConfigurationDialog);
        setDefaultAll->setObjectName(QStringLiteral("setDefaultAll"));
        setDefaultAll->setGeometry(QRect(440, 580, 101, 25));
        layoutWidget = new QWidget(CameraConfigurationDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 610, 536, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_readXML_D = new QPushButton(layoutWidget);
        pushButton_readXML_D->setObjectName(QStringLiteral("pushButton_readXML_D"));

        horizontalLayout->addWidget(pushButton_readXML_D);

        pushButton_readXML_L = new QPushButton(layoutWidget);
        pushButton_readXML_L->setObjectName(QStringLiteral("pushButton_readXML_L"));

        horizontalLayout->addWidget(pushButton_readXML_L);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);

        label_5 = new QLabel(CameraConfigurationDialog);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(19, 246, 101, 17));
        label_6 = new QLabel(CameraConfigurationDialog);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(20, 496, 101, 17));
        focus_auto_checkBox = new QCheckBox(CameraConfigurationDialog);
        focus_auto_checkBox->setObjectName(QStringLiteral("focus_auto_checkBox"));
        focus_auto_checkBox->setGeometry(QRect(188, 493, 81, 23));
        label_8 = new QLabel(CameraConfigurationDialog);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(20, 397, 101, 17));
        white_balance_min_label = new QLabel(CameraConfigurationDialog);
        white_balance_min_label->setObjectName(QStringLiteral("white_balance_min_label"));
        white_balance_min_label->setGeometry(QRect(130, 397, 67, 17));
        white_balance_min_label->setAlignment(Qt::AlignCenter);
        horizontalSlider_white_balance = new QSlider(CameraConfigurationDialog);
        horizontalSlider_white_balance->setObjectName(QStringLiteral("horizontalSlider_white_balance"));
        horizontalSlider_white_balance->setGeometry(QRect(189, 397, 160, 16));
        horizontalSlider_white_balance->setOrientation(Qt::Horizontal);
        white_balance_max_label = new QLabel(CameraConfigurationDialog);
        white_balance_max_label->setObjectName(QStringLiteral("white_balance_max_label"));
        white_balance_max_label->setGeometry(QRect(352, 397, 67, 17));
        white_balance_max_label->setAlignment(Qt::AlignCenter);
        white_balance_default_label = new QLabel(CameraConfigurationDialog);
        white_balance_default_label->setObjectName(QStringLiteral("white_balance_default_label"));
        white_balance_default_label->setGeometry(QRect(410, 397, 67, 17));
        white_balance_default_label->setAlignment(Qt::AlignCenter);
        setExposureAutoDefaultButton = new QPushButton(CameraConfigurationDialog);
        setExposureAutoDefaultButton->setObjectName(QStringLiteral("setExposureAutoDefaultButton"));
        setExposureAutoDefaultButton->setGeometry(QRect(474, 240, 61, 25));
        white_balance_value_label = new QLabel(CameraConfigurationDialog);
        white_balance_value_label->setObjectName(QStringLiteral("white_balance_value_label"));
        white_balance_value_label->setGeometry(QRect(237, 407, 67, 17));
        white_balance_value_label->setAlignment(Qt::AlignCenter);
        setWhiteBalanceDefaultButton = new QPushButton(CameraConfigurationDialog);
        setWhiteBalanceDefaultButton->setObjectName(QStringLiteral("setWhiteBalanceDefaultButton"));
        setWhiteBalanceDefaultButton->setGeometry(QRect(475, 392, 61, 25));
        label_9 = new QLabel(CameraConfigurationDialog);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(19, 345, 111, 20));
        white_balance_auto_checkBox = new QCheckBox(CameraConfigurationDialog);
        white_balance_auto_checkBox->setObjectName(QStringLiteral("white_balance_auto_checkBox"));
        white_balance_auto_checkBox->setGeometry(QRect(189, 343, 92, 23));
        setWhiteBalanceAutoDefaultButton = new QPushButton(CameraConfigurationDialog);
        setWhiteBalanceAutoDefaultButton->setObjectName(QStringLiteral("setWhiteBalanceAutoDefaultButton"));
        setWhiteBalanceAutoDefaultButton->setGeometry(QRect(474, 340, 61, 25));
        label_10 = new QLabel(CameraConfigurationDialog);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 447, 101, 17));
        blacklight_min_label = new QLabel(CameraConfigurationDialog);
        blacklight_min_label->setObjectName(QStringLiteral("blacklight_min_label"));
        blacklight_min_label->setGeometry(QRect(130, 447, 67, 17));
        blacklight_min_label->setAlignment(Qt::AlignCenter);
        horizontalSlider_blacklight = new QSlider(CameraConfigurationDialog);
        horizontalSlider_blacklight->setObjectName(QStringLiteral("horizontalSlider_blacklight"));
        horizontalSlider_blacklight->setGeometry(QRect(190, 447, 160, 16));
        horizontalSlider_blacklight->setOrientation(Qt::Horizontal);
        blacklight_value_label = new QLabel(CameraConfigurationDialog);
        blacklight_value_label->setObjectName(QStringLiteral("blacklight_value_label"));
        blacklight_value_label->setGeometry(QRect(238, 457, 67, 17));
        blacklight_value_label->setAlignment(Qt::AlignCenter);
        blacklight_max_label = new QLabel(CameraConfigurationDialog);
        blacklight_max_label->setObjectName(QStringLiteral("blacklight_max_label"));
        blacklight_max_label->setGeometry(QRect(352, 447, 67, 17));
        blacklight_max_label->setAlignment(Qt::AlignCenter);
        blacklight_default_label = new QLabel(CameraConfigurationDialog);
        blacklight_default_label->setObjectName(QStringLiteral("blacklight_default_label"));
        blacklight_default_label->setGeometry(QRect(411, 447, 67, 17));
        blacklight_default_label->setAlignment(Qt::AlignCenter);
        setBlacklightDefaultButton = new QPushButton(CameraConfigurationDialog);
        setBlacklightDefaultButton->setObjectName(QStringLiteral("setBlacklightDefaultButton"));
        setBlacklightDefaultButton->setGeometry(QRect(476, 440, 61, 25));
        setFocusAutoDefaultButton = new QPushButton(CameraConfigurationDialog);
        setFocusAutoDefaultButton->setObjectName(QStringLiteral("setFocusAutoDefaultButton"));
        setFocusAutoDefaultButton->setGeometry(QRect(476, 486, 61, 25));
        label_11 = new QLabel(CameraConfigurationDialog);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(20, 544, 101, 17));
        gain_min_label = new QLabel(CameraConfigurationDialog);
        gain_min_label->setObjectName(QStringLiteral("gain_min_label"));
        gain_min_label->setGeometry(QRect(130, 544, 67, 17));
        gain_min_label->setAlignment(Qt::AlignCenter);
        horizontalSlider_gain = new QSlider(CameraConfigurationDialog);
        horizontalSlider_gain->setObjectName(QStringLiteral("horizontalSlider_gain"));
        horizontalSlider_gain->setGeometry(QRect(190, 544, 160, 16));
        horizontalSlider_gain->setOrientation(Qt::Horizontal);
        gain_value_label = new QLabel(CameraConfigurationDialog);
        gain_value_label->setObjectName(QStringLiteral("gain_value_label"));
        gain_value_label->setGeometry(QRect(240, 554, 67, 17));
        gain_value_label->setAlignment(Qt::AlignCenter);
        gain_max_label = new QLabel(CameraConfigurationDialog);
        gain_max_label->setObjectName(QStringLiteral("gain_max_label"));
        gain_max_label->setGeometry(QRect(353, 544, 67, 17));
        gain_max_label->setAlignment(Qt::AlignCenter);
        gain_default_label = new QLabel(CameraConfigurationDialog);
        gain_default_label->setObjectName(QStringLiteral("gain_default_label"));
        gain_default_label->setGeometry(QRect(410, 544, 67, 17));
        gain_default_label->setAlignment(Qt::AlignCenter);
        setGainDefaultButton = new QPushButton(CameraConfigurationDialog);
        setGainDefaultButton->setObjectName(QStringLiteral("setGainDefaultButton"));
        setGainDefaultButton->setGeometry(QRect(475, 537, 61, 25));
        exposureAuto_min_label = new QLabel(CameraConfigurationDialog);
        exposureAuto_min_label->setObjectName(QStringLiteral("exposureAuto_min_label"));
        exposureAuto_min_label->setGeometry(QRect(130, 250, 67, 17));
        exposureAuto_min_label->setAlignment(Qt::AlignCenter);
        horizontalSlider_exposureAuto = new QSlider(CameraConfigurationDialog);
        horizontalSlider_exposureAuto->setObjectName(QStringLiteral("horizontalSlider_exposureAuto"));
        horizontalSlider_exposureAuto->setGeometry(QRect(190, 250, 160, 16));
        horizontalSlider_exposureAuto->setOrientation(Qt::Horizontal);
        exposureAuto_max_label = new QLabel(CameraConfigurationDialog);
        exposureAuto_max_label->setObjectName(QStringLiteral("exposureAuto_max_label"));
        exposureAuto_max_label->setGeometry(QRect(350, 250, 67, 17));
        exposureAuto_max_label->setAlignment(Qt::AlignCenter);
        exposureAuto_default_label = new QLabel(CameraConfigurationDialog);
        exposureAuto_default_label->setObjectName(QStringLiteral("exposureAuto_default_label"));
        exposureAuto_default_label->setGeometry(QRect(410, 250, 67, 17));
        exposureAuto_default_label->setAlignment(Qt::AlignCenter);
        exposureAuto_value_label = new QLabel(CameraConfigurationDialog);
        exposureAuto_value_label->setObjectName(QStringLiteral("exposureAuto_value_label"));
        exposureAuto_value_label->setGeometry(QRect(240, 270, 67, 17));
        exposureAuto_value_label->setAlignment(Qt::AlignCenter);
        exposureAutoPriority_checkBox = new QCheckBox(CameraConfigurationDialog);
        exposureAutoPriority_checkBox->setObjectName(QStringLiteral("exposureAutoPriority_checkBox"));
        exposureAutoPriority_checkBox->setGeometry(QRect(189, 195, 92, 23));
        setExposureAutoPriorityDefaultButton = new QPushButton(CameraConfigurationDialog);
        setExposureAutoPriorityDefaultButton->setObjectName(QStringLiteral("setExposureAutoPriorityDefaultButton"));
        setExposureAutoPriorityDefaultButton->setGeometry(QRect(474, 190, 61, 25));

        retranslateUi(CameraConfigurationDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), CameraConfigurationDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), CameraConfigurationDialog, SLOT(reject()));
        QObject::connect(horizontalSlider_exposureAuto, SIGNAL(valueChanged(int)), exposureAuto_value_label, SLOT(setNum(int)));

        QMetaObject::connectSlotsByName(CameraConfigurationDialog);
    } // setupUi

    void retranslateUi(QDialog *CameraConfigurationDialog)
    {
        CameraConfigurationDialog->setWindowTitle(QApplication::translate("CameraConfigurationDialog", "Camera Configuration", Q_NULLPTR));
        label->setText(QApplication::translate("CameraConfigurationDialog", "Brightness", Q_NULLPTR));
        label_2->setText(QApplication::translate("CameraConfigurationDialog", "Contrast", Q_NULLPTR));
        label_3->setText(QApplication::translate("CameraConfigurationDialog", "Saturation", Q_NULLPTR));
        contrast_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        brightness_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        saturation_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        label_7->setText(QApplication::translate("CameraConfigurationDialog", "ExposurePriority*", Q_NULLPTR));
        label_4->setText(QApplication::translate("CameraConfigurationDialog", "Exposure*", Q_NULLPTR));
        exposure_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        brightness_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        contrast_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        saturation_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        exposure_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        brightness_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        contrast_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        saturation_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        exposure_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        brightness_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        contrast_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        saturation_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        exposure_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        min_label->setText(QApplication::translate("CameraConfigurationDialog", "Min", Q_NULLPTR));
        max_label->setText(QApplication::translate("CameraConfigurationDialog", "Max", Q_NULLPTR));
        default_label->setText(QApplication::translate("CameraConfigurationDialog", "Default", Q_NULLPTR));
        setBrigtnessDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", Q_NULLPTR));
        setContrastDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", Q_NULLPTR));
        setSaturationDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", Q_NULLPTR));
        setExposureDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", Q_NULLPTR));
        setDefaultAll->setText(QApplication::translate("CameraConfigurationDialog", "All Default", Q_NULLPTR));
        pushButton->setText(QApplication::translate("CameraConfigurationDialog", "Save D XML", Q_NULLPTR));
        pushButton_readXML_D->setText(QApplication::translate("CameraConfigurationDialog", "Read D XML", Q_NULLPTR));
        pushButton_readXML_L->setText(QApplication::translate("CameraConfigurationDialog", "Read Last XML", Q_NULLPTR));
        label_5->setText(QApplication::translate("CameraConfigurationDialog", "Exposure_auto", Q_NULLPTR));
        label_6->setText(QApplication::translate("CameraConfigurationDialog", "Focus_auto", Q_NULLPTR));
        focus_auto_checkBox->setText(QApplication::translate("CameraConfigurationDialog", "Enabled", Q_NULLPTR));
        label_8->setText(QApplication::translate("CameraConfigurationDialog", "WhiteBalance", Q_NULLPTR));
        white_balance_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        white_balance_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        white_balance_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        setExposureAutoDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", Q_NULLPTR));
        white_balance_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        setWhiteBalanceDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", Q_NULLPTR));
        label_9->setText(QApplication::translate("CameraConfigurationDialog", "WhiteBalanceAuto", Q_NULLPTR));
        white_balance_auto_checkBox->setText(QApplication::translate("CameraConfigurationDialog", "Enabled", Q_NULLPTR));
        setWhiteBalanceAutoDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", Q_NULLPTR));
        label_10->setText(QApplication::translate("CameraConfigurationDialog", "Blacklight", Q_NULLPTR));
        blacklight_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        blacklight_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        blacklight_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        blacklight_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        setBlacklightDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", Q_NULLPTR));
        setFocusAutoDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", Q_NULLPTR));
        label_11->setText(QApplication::translate("CameraConfigurationDialog", "Gain", Q_NULLPTR));
        gain_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        gain_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        gain_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        gain_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        setGainDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", Q_NULLPTR));
        exposureAuto_min_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        exposureAuto_max_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        exposureAuto_default_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        exposureAuto_value_label->setText(QApplication::translate("CameraConfigurationDialog", "0", Q_NULLPTR));
        exposureAutoPriority_checkBox->setText(QApplication::translate("CameraConfigurationDialog", "Enabled", Q_NULLPTR));
        setExposureAutoPriorityDefaultButton->setText(QApplication::translate("CameraConfigurationDialog", "Default", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class CameraConfigurationDialog: public Ui_CameraConfigurationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERACONFIGURATIONDIALOG_H
