/********************************************************************************
** Form generated from reading UI file 'visionconfigdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VISIONCONFIGDIALOG_H
#define UI_VISIONCONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_VisionConfigDialog
{
public:
    QDialogButtonBox *buttonBox;
    QPushButton *calibrateSegmentationPushButton;
    QPushButton *calibrateLUTPushButton;
    QPushButton *calibrateTrackingPushButton;
    QLabel *projectionLabel;
    QLabel *segmentationLabel;

    void setupUi(QDialog *VisionConfigDialog)
    {
        if (VisionConfigDialog->objectName().isEmpty())
            VisionConfigDialog->setObjectName(QString::fromUtf8("VisionConfigDialog"));
        VisionConfigDialog->resize(1135, 620);
        buttonBox = new QDialogButtonBox(VisionConfigDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(760, 560, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        calibrateSegmentationPushButton = new QPushButton(VisionConfigDialog);
        calibrateSegmentationPushButton->setObjectName(QString::fromUtf8("calibrateSegmentationPushButton"));
        calibrateSegmentationPushButton->setGeometry(QRect(570, 480, 241, 32));
        calibrateLUTPushButton = new QPushButton(VisionConfigDialog);
        calibrateLUTPushButton->setObjectName(QString::fromUtf8("calibrateLUTPushButton"));
        calibrateLUTPushButton->setEnabled(false);
        calibrateLUTPushButton->setGeometry(QRect(570, 510, 241, 32));
        calibrateTrackingPushButton = new QPushButton(VisionConfigDialog);
        calibrateTrackingPushButton->setObjectName(QString::fromUtf8("calibrateTrackingPushButton"));
        calibrateTrackingPushButton->setGeometry(QRect(310, 480, 241, 61));
        projectionLabel = new QLabel(VisionConfigDialog);
        projectionLabel->setObjectName(QString::fromUtf8("projectionLabel"));
        projectionLabel->setGeometry(QRect(50, 30, 510, 390));
        segmentationLabel = new QLabel(VisionConfigDialog);
        segmentationLabel->setObjectName(QString::fromUtf8("segmentationLabel"));
        segmentationLabel->setGeometry(QRect(600, 30, 510, 390));

        retranslateUi(VisionConfigDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), VisionConfigDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), VisionConfigDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(VisionConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *VisionConfigDialog)
    {
        VisionConfigDialog->setWindowTitle(QApplication::translate("VisionConfigDialog", "Dialog", nullptr));
        calibrateSegmentationPushButton->setText(QApplication::translate("VisionConfigDialog", "Calibrate Segmentation by trackbar", nullptr));
        calibrateLUTPushButton->setText(QApplication::translate("VisionConfigDialog", "Calibrate Segmentation LUT 3D", nullptr));
        calibrateTrackingPushButton->setText(QApplication::translate("VisionConfigDialog", "Calibrate Tracking", nullptr));
        projectionLabel->setText(QString());
        segmentationLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class VisionConfigDialog: public Ui_VisionConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VISIONCONFIGDIALOG_H
