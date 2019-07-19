/********************************************************************************
** Form generated from reading UI file 'fieldpointscalibratedialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FIELDPOINTSCALIBRATEDIALOG_H
#define UI_FIELDPOINTSCALIBRATEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>

QT_BEGIN_NAMESPACE

class Ui_FieldPointsCalibrateDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *videoLabel;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;

    void setupUi(QDialog *FieldPointsCalibrateDialog)
    {
        if (FieldPointsCalibrateDialog->objectName().isEmpty())
            FieldPointsCalibrateDialog->setObjectName(QString::fromUtf8("FieldPointsCalibrateDialog"));
        FieldPointsCalibrateDialog->resize(738, 620);
        buttonBox = new QDialogButtonBox(FieldPointsCalibrateDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(360, 580, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        videoLabel = new QLabel(FieldPointsCalibrateDialog);
        videoLabel->setObjectName(QString::fromUtf8("videoLabel"));
        videoLabel->setGeometry(QRect(20, 20, 680, 520));
        videoLabel->setAutoFillBackground(true);
        videoLabel->setFrameShape(QFrame::Box);
        label = new QLabel(FieldPointsCalibrateDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 5, 16, 16));
        label->setPixmap(QPixmap(QString::fromUtf8(":/image/icon/021-keyboard-key-1.png")));
        label->setScaledContents(true);
        label_2 = new QLabel(FieldPointsCalibrateDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(19, 539, 16, 16));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/image/icon/023-keyboard-key-with-number-2.png")));
        label_2->setScaledContents(true);
        label_3 = new QLabel(FieldPointsCalibrateDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(685, 539, 16, 16));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/image/icon/022-number-3-key-on-keyboard.png")));
        label_3->setScaledContents(true);
        label_4 = new QLabel(FieldPointsCalibrateDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(684, 4, 16, 16));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/image/icon/029-keyboard-key-of-number-4.png")));
        label_4->setScaledContents(true);

        retranslateUi(FieldPointsCalibrateDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FieldPointsCalibrateDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FieldPointsCalibrateDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FieldPointsCalibrateDialog);
    } // setupUi

    void retranslateUi(QDialog *FieldPointsCalibrateDialog)
    {
        FieldPointsCalibrateDialog->setWindowTitle(QApplication::translate("FieldPointsCalibrateDialog", "Field Points Calibration", nullptr));
        videoLabel->setText(QString());
        label->setText(QString());
        label_2->setText(QString());
        label_3->setText(QString());
        label_4->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FieldPointsCalibrateDialog: public Ui_FieldPointsCalibrateDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FIELDPOINTSCALIBRATEDIALOG_H
