/********************************************************************************
** Form generated from reading UI file 'segmentationconfigdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEGMENTATIONCONFIGDIALOG_H
#define UI_SEGMENTATIONCONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SegmentationConfigDialog
{
public:
    QGridLayout *gridLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_5;
    QGridLayout *gridLayout_2;
    QCheckBox *NoCOLCheckBox;
    QCheckBox *GreenCheckBox;
    QCheckBox *OrangeCheckBox;
    QCheckBox *PinkCheckBox;
    QCheckBox *BlueCheckBox;
    QCheckBox *LightBlueCheckBox;
    QCheckBox *YellowCheckBox;
    QCheckBox *PurpleCheckBox;
    QCheckBox *RedCheckBox;
    QCheckBox *ColorStrangeCheckBox;
    QPushButton *UnCheckAll;
    QPushButton *checkAll;
    QGroupBox *groupBox_5;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout_6;
    QLabel *label;
    QSlider *horizontalSlider_grayScale;
    QLabel *GrayLevel;
    QCheckBox *QuantizationCheckBox;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_10;
    QGridLayout *gridLayout_9;
    QGridLayout *gridLayout_3;
    QLabel *label_11;
    QSlider *YMinHorizontalSlider;
    QLabel *YMinLabel;
    QLabel *label_12;
    QSlider *UMinHorizontalSlider;
    QLabel *UMinLabel;
    QLabel *label_13;
    QSlider *VMinHorizontalSlider;
    QLabel *VMinLabel;
    QGridLayout *gridLayout_4;
    QSlider *UMaxHorizontalSlider;
    QLabel *UMaxLabel;
    QSlider *YMaxHorizontalSlider;
    QLabel *YMaxLabel;
    QLabel *label_15;
    QSlider *VMaxHorizontalSlider;
    QLabel *VMaxLabel;
    QLabel *label_14;
    QLabel *label_16;
    QLabel *YUVMaxColorSampleLabel;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_CloseColor;
    QPushButton *pushButton_OpenColor;
    QLabel *YUVMinColorSampleLabel;
    QComboBox *selectColorComboBox;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_8;
    QLabel *zoomlabel;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_7;
    QListWidget *ParametersListWidget;
    QPushButton *saveSegmentationPushButton;
    QDialogButtonBox *buttonBox;
    QFrame *leftFrame;
    QLabel *originalLabel;
    QFrame *rightFrame;
    QLabel *visualizationLabel;

    void setupUi(QDialog *SegmentationConfigDialog)
    {
        if (SegmentationConfigDialog->objectName().isEmpty())
            SegmentationConfigDialog->setObjectName(QStringLiteral("SegmentationConfigDialog"));
        SegmentationConfigDialog->resize(1203, 607);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SegmentationConfigDialog->sizePolicy().hasHeightForWidth());
        SegmentationConfigDialog->setSizePolicy(sizePolicy);
        SegmentationConfigDialog->setMinimumSize(QSize(1203, 607));
        SegmentationConfigDialog->setMouseTracking(true);
        SegmentationConfigDialog->setAcceptDrops(true);
        SegmentationConfigDialog->setSizeGripEnabled(true);
        SegmentationConfigDialog->setModal(true);
        gridLayout = new QGridLayout(SegmentationConfigDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        frame = new QFrame(SegmentationConfigDialog);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(1185, 160));
        frame->setMaximumSize(QSize(16777215, 160));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setAutoFillBackground(true);
        gridLayout_5 = new QGridLayout(groupBox_2);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        NoCOLCheckBox = new QCheckBox(groupBox_2);
        NoCOLCheckBox->setObjectName(QStringLiteral("NoCOLCheckBox"));
        NoCOLCheckBox->setAutoFillBackground(true);
        NoCOLCheckBox->setStyleSheet(QStringLiteral(""));
        NoCOLCheckBox->setChecked(true);

        gridLayout_2->addWidget(NoCOLCheckBox, 0, 0, 1, 1);

        GreenCheckBox = new QCheckBox(groupBox_2);
        GreenCheckBox->setObjectName(QStringLiteral("GreenCheckBox"));
        GreenCheckBox->setAutoFillBackground(false);
        GreenCheckBox->setStyleSheet(QStringLiteral("background-color: rgb(115, 210, 22);"));
        GreenCheckBox->setChecked(true);

        gridLayout_2->addWidget(GreenCheckBox, 0, 1, 1, 1);

        OrangeCheckBox = new QCheckBox(groupBox_2);
        OrangeCheckBox->setObjectName(QStringLiteral("OrangeCheckBox"));
        OrangeCheckBox->setStyleSheet(QStringLiteral("background-color: rgb(252, 175, 62);"));
        OrangeCheckBox->setChecked(true);

        gridLayout_2->addWidget(OrangeCheckBox, 1, 0, 1, 1);

        PinkCheckBox = new QCheckBox(groupBox_2);
        PinkCheckBox->setObjectName(QStringLiteral("PinkCheckBox"));
        PinkCheckBox->setAutoFillBackground(false);
        PinkCheckBox->setStyleSheet(QLatin1String("background-color: rgb(232, 17, 224);\n"
"color: rgb(255, 255, 255);"));
        PinkCheckBox->setChecked(true);

        gridLayout_2->addWidget(PinkCheckBox, 1, 1, 1, 1);

        BlueCheckBox = new QCheckBox(groupBox_2);
        BlueCheckBox->setObjectName(QStringLiteral("BlueCheckBox"));
        BlueCheckBox->setAutoFillBackground(false);
        BlueCheckBox->setStyleSheet(QLatin1String("background-color: rgb(14, 68, 241);\n"
"color: rgb(255, 255, 255);"));
        BlueCheckBox->setChecked(true);

        gridLayout_2->addWidget(BlueCheckBox, 2, 0, 1, 1);

        LightBlueCheckBox = new QCheckBox(groupBox_2);
        LightBlueCheckBox->setObjectName(QStringLiteral("LightBlueCheckBox"));
        LightBlueCheckBox->setAutoFillBackground(false);
        LightBlueCheckBox->setStyleSheet(QStringLiteral("background-color: rgb(0, 255, 231);"));
        LightBlueCheckBox->setChecked(true);

        gridLayout_2->addWidget(LightBlueCheckBox, 2, 1, 1, 1);

        YellowCheckBox = new QCheckBox(groupBox_2);
        YellowCheckBox->setObjectName(QStringLiteral("YellowCheckBox"));
        YellowCheckBox->setAutoFillBackground(false);
        YellowCheckBox->setStyleSheet(QStringLiteral("background-color: rgb(252, 233, 79);"));
        YellowCheckBox->setChecked(true);

        gridLayout_2->addWidget(YellowCheckBox, 3, 0, 1, 1);

        PurpleCheckBox = new QCheckBox(groupBox_2);
        PurpleCheckBox->setObjectName(QStringLiteral("PurpleCheckBox"));
        PurpleCheckBox->setAutoFillBackground(false);
        PurpleCheckBox->setStyleSheet(QLatin1String("background-color: rgb(194, 98, 244);\n"
"color: rgb(255, 255, 255);"));
        PurpleCheckBox->setChecked(true);

        gridLayout_2->addWidget(PurpleCheckBox, 3, 1, 1, 1);

        RedCheckBox = new QCheckBox(groupBox_2);
        RedCheckBox->setObjectName(QStringLiteral("RedCheckBox"));
        RedCheckBox->setAutoFillBackground(false);
        RedCheckBox->setStyleSheet(QStringLiteral("background-color: rgb(239, 41, 41);"));
        RedCheckBox->setChecked(true);

        gridLayout_2->addWidget(RedCheckBox, 4, 0, 1, 1);

        ColorStrangeCheckBox = new QCheckBox(groupBox_2);
        ColorStrangeCheckBox->setObjectName(QStringLiteral("ColorStrangeCheckBox"));
        ColorStrangeCheckBox->setAutoFillBackground(false);
        ColorStrangeCheckBox->setStyleSheet(QLatin1String("background-color: rgb(125, 125, 125);\n"
"color: rgb(255, 255, 255);"));
        ColorStrangeCheckBox->setChecked(true);

        gridLayout_2->addWidget(ColorStrangeCheckBox, 4, 1, 1, 1);


        gridLayout_5->addLayout(gridLayout_2, 0, 0, 3, 1);

        UnCheckAll = new QPushButton(groupBox_2);
        UnCheckAll->setObjectName(QStringLiteral("UnCheckAll"));

        gridLayout_5->addWidget(UnCheckAll, 0, 1, 1, 1);

        checkAll = new QPushButton(groupBox_2);
        checkAll->setObjectName(QStringLiteral("checkAll"));
        checkAll->setCheckable(false);
        checkAll->setChecked(false);

        gridLayout_5->addWidget(checkAll, 1, 1, 1, 1);


        horizontalLayout->addWidget(groupBox_2);

        groupBox_5 = new QGroupBox(frame);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        gridLayoutWidget = new QWidget(groupBox_5);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(10, 110, 81, 22));
        gridLayout_6 = new QGridLayout(gridLayoutWidget);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        gridLayout_6->setContentsMargins(1, 1, 1, 1);
        label = new QLabel(gridLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_6->addWidget(label, 0, 0, 1, 1);

        horizontalSlider_grayScale = new QSlider(gridLayoutWidget);
        horizontalSlider_grayScale->setObjectName(QStringLiteral("horizontalSlider_grayScale"));
        horizontalSlider_grayScale->setMaximum(50);
        horizontalSlider_grayScale->setOrientation(Qt::Horizontal);

        gridLayout_6->addWidget(horizontalSlider_grayScale, 0, 1, 1, 1);

        GrayLevel = new QLabel(gridLayoutWidget);
        GrayLevel->setObjectName(QStringLiteral("GrayLevel"));

        gridLayout_6->addWidget(GrayLevel, 0, 2, 1, 1);

        QuantizationCheckBox = new QCheckBox(groupBox_5);
        QuantizationCheckBox->setObjectName(QStringLiteral("QuantizationCheckBox"));
        QuantizationCheckBox->setGeometry(QRect(10, 30, 71, 26));
        QuantizationCheckBox->setChecked(true);

        horizontalLayout->addWidget(groupBox_5);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_10 = new QGridLayout(groupBox);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        gridLayout_9 = new QGridLayout();
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_3->addWidget(label_11, 0, 0, 1, 1);

        YMinHorizontalSlider = new QSlider(groupBox);
        YMinHorizontalSlider->setObjectName(QStringLiteral("YMinHorizontalSlider"));
        YMinHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(YMinHorizontalSlider, 0, 1, 1, 1);

        YMinLabel = new QLabel(groupBox);
        YMinLabel->setObjectName(QStringLiteral("YMinLabel"));

        gridLayout_3->addWidget(YMinLabel, 0, 2, 1, 1);

        label_12 = new QLabel(groupBox);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_3->addWidget(label_12, 1, 0, 1, 1);

        UMinHorizontalSlider = new QSlider(groupBox);
        UMinHorizontalSlider->setObjectName(QStringLiteral("UMinHorizontalSlider"));
        UMinHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(UMinHorizontalSlider, 1, 1, 1, 1);

        UMinLabel = new QLabel(groupBox);
        UMinLabel->setObjectName(QStringLiteral("UMinLabel"));

        gridLayout_3->addWidget(UMinLabel, 1, 2, 1, 1);

        label_13 = new QLabel(groupBox);
        label_13->setObjectName(QStringLiteral("label_13"));

        gridLayout_3->addWidget(label_13, 2, 0, 1, 1);

        VMinHorizontalSlider = new QSlider(groupBox);
        VMinHorizontalSlider->setObjectName(QStringLiteral("VMinHorizontalSlider"));
        VMinHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_3->addWidget(VMinHorizontalSlider, 2, 1, 1, 1);

        VMinLabel = new QLabel(groupBox);
        VMinLabel->setObjectName(QStringLiteral("VMinLabel"));

        gridLayout_3->addWidget(VMinLabel, 2, 2, 1, 1);


        gridLayout_9->addLayout(gridLayout_3, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        UMaxHorizontalSlider = new QSlider(groupBox);
        UMaxHorizontalSlider->setObjectName(QStringLiteral("UMaxHorizontalSlider"));
        UMaxHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(UMaxHorizontalSlider, 1, 1, 1, 1);

        UMaxLabel = new QLabel(groupBox);
        UMaxLabel->setObjectName(QStringLiteral("UMaxLabel"));

        gridLayout_4->addWidget(UMaxLabel, 1, 2, 1, 1);

        YMaxHorizontalSlider = new QSlider(groupBox);
        YMaxHorizontalSlider->setObjectName(QStringLiteral("YMaxHorizontalSlider"));
        YMaxHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(YMaxHorizontalSlider, 0, 1, 1, 1);

        YMaxLabel = new QLabel(groupBox);
        YMaxLabel->setObjectName(QStringLiteral("YMaxLabel"));

        gridLayout_4->addWidget(YMaxLabel, 0, 2, 1, 1);

        label_15 = new QLabel(groupBox);
        label_15->setObjectName(QStringLiteral("label_15"));

        gridLayout_4->addWidget(label_15, 0, 0, 1, 1);

        VMaxHorizontalSlider = new QSlider(groupBox);
        VMaxHorizontalSlider->setObjectName(QStringLiteral("VMaxHorizontalSlider"));
        VMaxHorizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout_4->addWidget(VMaxHorizontalSlider, 2, 1, 1, 1);

        VMaxLabel = new QLabel(groupBox);
        VMaxLabel->setObjectName(QStringLiteral("VMaxLabel"));

        gridLayout_4->addWidget(VMaxLabel, 2, 2, 1, 1);

        label_14 = new QLabel(groupBox);
        label_14->setObjectName(QStringLiteral("label_14"));

        gridLayout_4->addWidget(label_14, 1, 0, 1, 1);

        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QStringLiteral("label_16"));

        gridLayout_4->addWidget(label_16, 2, 0, 1, 1);

        YUVMaxColorSampleLabel = new QLabel(groupBox);
        YUVMaxColorSampleLabel->setObjectName(QStringLiteral("YUVMaxColorSampleLabel"));
        YUVMaxColorSampleLabel->setAutoFillBackground(false);
        YUVMaxColorSampleLabel->setStyleSheet(QStringLiteral("background-color: rgb(239, 41, 41);"));

        gridLayout_4->addWidget(YUVMaxColorSampleLabel, 0, 3, 3, 1);


        gridLayout_9->addLayout(gridLayout_4, 0, 2, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton_CloseColor = new QPushButton(groupBox);
        pushButton_CloseColor->setObjectName(QStringLiteral("pushButton_CloseColor"));

        horizontalLayout_2->addWidget(pushButton_CloseColor);

        pushButton_OpenColor = new QPushButton(groupBox);
        pushButton_OpenColor->setObjectName(QStringLiteral("pushButton_OpenColor"));

        horizontalLayout_2->addWidget(pushButton_OpenColor);


        gridLayout_9->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        YUVMinColorSampleLabel = new QLabel(groupBox);
        YUVMinColorSampleLabel->setObjectName(QStringLiteral("YUVMinColorSampleLabel"));
        YUVMinColorSampleLabel->setAutoFillBackground(false);
        YUVMinColorSampleLabel->setStyleSheet(QStringLiteral("background-color: rgb(32, 74, 135);"));

        gridLayout_9->addWidget(YUVMinColorSampleLabel, 0, 1, 1, 1);

        selectColorComboBox = new QComboBox(groupBox);
        selectColorComboBox->setObjectName(QStringLiteral("selectColorComboBox"));

        gridLayout_9->addWidget(selectColorComboBox, 1, 2, 1, 1);


        gridLayout_10->addLayout(gridLayout_9, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox);

        groupBox_4 = new QGroupBox(frame);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(120, 0));
        groupBox_4->setMaximumSize(QSize(120, 16777215));
        gridLayout_8 = new QGridLayout(groupBox_4);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        zoomlabel = new QLabel(groupBox_4);
        zoomlabel->setObjectName(QStringLiteral("zoomlabel"));
        zoomlabel->setAutoFillBackground(false);
        zoomlabel->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));

        gridLayout_8->addWidget(zoomlabel, 0, 0, 1, 1);


        horizontalLayout->addWidget(groupBox_4);

        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMaximumSize(QSize(250, 16777215));
        gridLayout_7 = new QGridLayout(groupBox_3);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        ParametersListWidget = new QListWidget(groupBox_3);
        ParametersListWidget->setObjectName(QStringLiteral("ParametersListWidget"));

        gridLayout_7->addWidget(ParametersListWidget, 0, 0, 1, 2);

        saveSegmentationPushButton = new QPushButton(groupBox_3);
        saveSegmentationPushButton->setObjectName(QStringLiteral("saveSegmentationPushButton"));

        gridLayout_7->addWidget(saveSegmentationPushButton, 1, 0, 1, 1);

        buttonBox = new QDialogButtonBox(groupBox_3);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout_7->addWidget(buttonBox, 1, 1, 1, 1);


        horizontalLayout->addWidget(groupBox_3);

        groupBox->raise();
        groupBox_4->raise();
        groupBox_2->raise();
        groupBox_3->raise();
        groupBox_5->raise();

        gridLayout->addWidget(frame, 1, 0, 1, 2, Qt::AlignHCenter);

        leftFrame = new QFrame(SegmentationConfigDialog);
        leftFrame->setObjectName(QStringLiteral("leftFrame"));
        leftFrame->setAutoFillBackground(false);
        leftFrame->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        leftFrame->setFrameShape(QFrame::StyledPanel);
        leftFrame->setFrameShadow(QFrame::Raised);
        originalLabel = new QLabel(leftFrame);
        originalLabel->setObjectName(QStringLiteral("originalLabel"));
        originalLabel->setGeometry(QRect(-10, 40, 590, 137));
        originalLabel->setMouseTracking(false);
        originalLabel->setAutoFillBackground(false);
        originalLabel->setStyleSheet(QStringLiteral("background-color: rgb(233, 185, 110);"));

        gridLayout->addWidget(leftFrame, 0, 0, 1, 1);

        rightFrame = new QFrame(SegmentationConfigDialog);
        rightFrame->setObjectName(QStringLiteral("rightFrame"));
        rightFrame->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        rightFrame->setFrameShape(QFrame::StyledPanel);
        rightFrame->setFrameShadow(QFrame::Raised);
        visualizationLabel = new QLabel(rightFrame);
        visualizationLabel->setObjectName(QStringLiteral("visualizationLabel"));
        visualizationLabel->setGeometry(QRect(200, 0, 589, 423));
        visualizationLabel->setMouseTracking(false);
        visualizationLabel->setAutoFillBackground(false);
        visualizationLabel->setStyleSheet(QStringLiteral("background-color: rgb(237, 212, 0);"));

        gridLayout->addWidget(rightFrame, 0, 1, 1, 1);


        retranslateUi(SegmentationConfigDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SegmentationConfigDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SegmentationConfigDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SegmentationConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *SegmentationConfigDialog)
    {
        SegmentationConfigDialog->setWindowTitle(QApplication::translate("SegmentationConfigDialog", "Segmentation Config", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("SegmentationConfigDialog", "Visibility", Q_NULLPTR));
        NoCOLCheckBox->setText(QString());
        GreenCheckBox->setText(QString());
        OrangeCheckBox->setText(QString());
        PinkCheckBox->setText(QString());
        BlueCheckBox->setText(QString());
        LightBlueCheckBox->setText(QString());
        YellowCheckBox->setText(QString());
        PurpleCheckBox->setText(QString());
        RedCheckBox->setText(QString());
        ColorStrangeCheckBox->setText(QString());
        UnCheckAll->setText(QApplication::translate("SegmentationConfigDialog", "UnCheck All", Q_NULLPTR));
        checkAll->setText(QApplication::translate("SegmentationConfigDialog", "Check All", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("SegmentationConfigDialog", "Filter     ", Q_NULLPTR));
        label->setText(QApplication::translate("SegmentationConfigDialog", "G", Q_NULLPTR));
        GrayLevel->setText(QApplication::translate("SegmentationConfigDialog", "0", Q_NULLPTR));
        QuantizationCheckBox->setText(QApplication::translate("SegmentationConfigDialog", "Quant", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("SegmentationConfigDialog", "Color Settings", Q_NULLPTR));
        label_11->setText(QApplication::translate("SegmentationConfigDialog", "Y", Q_NULLPTR));
        YMinLabel->setText(QApplication::translate("SegmentationConfigDialog", "255", Q_NULLPTR));
        label_12->setText(QApplication::translate("SegmentationConfigDialog", "U", Q_NULLPTR));
        UMinLabel->setText(QApplication::translate("SegmentationConfigDialog", "255", Q_NULLPTR));
        label_13->setText(QApplication::translate("SegmentationConfigDialog", "V", Q_NULLPTR));
        VMinLabel->setText(QApplication::translate("SegmentationConfigDialog", "255", Q_NULLPTR));
        UMaxLabel->setText(QApplication::translate("SegmentationConfigDialog", "255", Q_NULLPTR));
        YMaxLabel->setText(QApplication::translate("SegmentationConfigDialog", "255", Q_NULLPTR));
        label_15->setText(QApplication::translate("SegmentationConfigDialog", "Y", Q_NULLPTR));
        VMaxLabel->setText(QApplication::translate("SegmentationConfigDialog", "255", Q_NULLPTR));
        label_14->setText(QApplication::translate("SegmentationConfigDialog", "U", Q_NULLPTR));
        label_16->setText(QApplication::translate("SegmentationConfigDialog", "V", Q_NULLPTR));
        YUVMaxColorSampleLabel->setText(QString());
        pushButton_CloseColor->setText(QApplication::translate("SegmentationConfigDialog", "Close Color", Q_NULLPTR));
        pushButton_OpenColor->setText(QApplication::translate("SegmentationConfigDialog", "Open Color", Q_NULLPTR));
        YUVMinColorSampleLabel->setText(QString());
        groupBox_4->setTitle(QApplication::translate("SegmentationConfigDialog", "Zoom", Q_NULLPTR));
        zoomlabel->setText(QString());
        groupBox_3->setTitle(QApplication::translate("SegmentationConfigDialog", "Saving Options", Q_NULLPTR));
        saveSegmentationPushButton->setText(QApplication::translate("SegmentationConfigDialog", "Save New", Q_NULLPTR));
        originalLabel->setText(QString());
        visualizationLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SegmentationConfigDialog: public Ui_SegmentationConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEGMENTATIONCONFIGDIALOG_H
