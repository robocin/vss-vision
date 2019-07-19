/********************************************************************************
** Form generated from reading UI file 'maggicsegmentationdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAGGICSEGMENTATIONDIALOG_H
#define UI_MAGGICSEGMENTATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MaggicSegmentationDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *entitiesLayout;
    QLabel *label;
    QPushButton *entitiesButton_1;
    QPushButton *entitiesButton_2;
    QPushButton *entitiesButton_3;
    QPushButton *entitiesButton_4;
    QPushButton *entitiesButton_5;
    QPushButton *entitiesButton_6;
    QPushButton *entitiesButton_7;
    QTabWidget *tabWidget;
    QWidget *tab_1;
    QWidget *tab_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QWidget *tab_5;
    QLabel *visualizationLabel;
    QProgressBar *learningProgressBar;
    QPushButton *loadButton;
    QFrame *line;
    QSpinBox *learnSpinBox;
    QSlider *minimumVerticalSlider;
    QLCDNumber *minimumLcdNumber;
    QSlider *maximumVerticalSlider;
    QLCDNumber *maximumLcdNumber;
    QPushButton *resetButton;
    QPushButton *fixCameraButton;
    QSlider *threshGrayHorizontalSlider;
    QLCDNumber *threshGrayLcdNumber;
    QPushButton *playpauseButton;
    QPushButton *applyLUTButton;

    void setupUi(QDialog *MaggicSegmentationDialog)
    {
        if (MaggicSegmentationDialog->objectName().isEmpty())
            MaggicSegmentationDialog->setObjectName(QString::fromUtf8("MaggicSegmentationDialog"));
        MaggicSegmentationDialog->resize(750, 562);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/icon/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MaggicSegmentationDialog->setWindowIcon(icon);
        MaggicSegmentationDialog->setWindowOpacity(1.000000000000000);
        buttonBox = new QDialogButtonBox(MaggicSegmentationDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(460, 520, 171, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(MaggicSegmentationDialog);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(650, 10, 91, 241));
        entitiesLayout = new QVBoxLayout(verticalLayoutWidget);
        entitiesLayout->setSpacing(6);
        entitiesLayout->setObjectName(QString::fromUtf8("entitiesLayout"));
        entitiesLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        entitiesLayout->addWidget(label);

        entitiesButton_1 = new QPushButton(verticalLayoutWidget);
        entitiesButton_1->setObjectName(QString::fromUtf8("entitiesButton_1"));
        entitiesButton_1->setEnabled(true);
        entitiesButton_1->setCheckable(true);
        entitiesButton_1->setFlat(false);

        entitiesLayout->addWidget(entitiesButton_1);

        entitiesButton_2 = new QPushButton(verticalLayoutWidget);
        entitiesButton_2->setObjectName(QString::fromUtf8("entitiesButton_2"));
        entitiesButton_2->setCheckable(true);

        entitiesLayout->addWidget(entitiesButton_2);

        entitiesButton_3 = new QPushButton(verticalLayoutWidget);
        entitiesButton_3->setObjectName(QString::fromUtf8("entitiesButton_3"));
        entitiesButton_3->setAutoFillBackground(false);
        entitiesButton_3->setCheckable(true);
        entitiesButton_3->setChecked(false);

        entitiesLayout->addWidget(entitiesButton_3);

        entitiesButton_4 = new QPushButton(verticalLayoutWidget);
        entitiesButton_4->setObjectName(QString::fromUtf8("entitiesButton_4"));
        entitiesButton_4->setCheckable(true);

        entitiesLayout->addWidget(entitiesButton_4);

        entitiesButton_5 = new QPushButton(verticalLayoutWidget);
        entitiesButton_5->setObjectName(QString::fromUtf8("entitiesButton_5"));
        entitiesButton_5->setCheckable(true);

        entitiesLayout->addWidget(entitiesButton_5);

        entitiesButton_6 = new QPushButton(verticalLayoutWidget);
        entitiesButton_6->setObjectName(QString::fromUtf8("entitiesButton_6"));
        entitiesButton_6->setCheckable(true);

        entitiesLayout->addWidget(entitiesButton_6);

        entitiesButton_7 = new QPushButton(verticalLayoutWidget);
        entitiesButton_7->setObjectName(QString::fromUtf8("entitiesButton_7"));
        entitiesButton_7->setCheckable(true);

        entitiesLayout->addWidget(entitiesButton_7);

        tabWidget = new QTabWidget(MaggicSegmentationDialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 642, 511));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab_1 = new QWidget();
        tab_1->setObjectName(QString::fromUtf8("tab_1"));
        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        tabWidget->addTab(tab_5, QString());
        visualizationLabel = new QLabel(MaggicSegmentationDialog);
        visualizationLabel->setObjectName(QString::fromUtf8("visualizationLabel"));
        visualizationLabel->setGeometry(QRect(1, 28, 640, 480));
        visualizationLabel->setMouseTracking(true);
        visualizationLabel->setAutoFillBackground(true);
        learningProgressBar = new QProgressBar(MaggicSegmentationDialog);
        learningProgressBar->setObjectName(QString::fromUtf8("learningProgressBar"));
        learningProgressBar->setEnabled(false);
        learningProgressBar->setGeometry(QRect(650, 300, 91, 23));
        learningProgressBar->setMaximum(100);
        learningProgressBar->setValue(40);
        loadButton = new QPushButton(MaggicSegmentationDialog);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));
        loadButton->setEnabled(true);
        loadButton->setGeometry(QRect(650, 300, 91, 25));
        line = new QFrame(MaggicSegmentationDialog);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(650, 250, 91, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        learnSpinBox = new QSpinBox(MaggicSegmentationDialog);
        learnSpinBox->setObjectName(QString::fromUtf8("learnSpinBox"));
        learnSpinBox->setEnabled(false);
        learnSpinBox->setGeometry(QRect(650, 270, 91, 26));
        learnSpinBox->setMinimum(1);
        learnSpinBox->setMaximum(1000);
        learnSpinBox->setSingleStep(10);
        learnSpinBox->setValue(60);
        minimumVerticalSlider = new QSlider(MaggicSegmentationDialog);
        minimumVerticalSlider->setObjectName(QString::fromUtf8("minimumVerticalSlider"));
        minimumVerticalSlider->setGeometry(QRect(661, 369, 20, 111));
        minimumVerticalSlider->setMinimum(1);
        minimumVerticalSlider->setMaximum(255);
        minimumVerticalSlider->setValue(1);
        minimumVerticalSlider->setOrientation(Qt::Vertical);
        minimumLcdNumber = new QLCDNumber(MaggicSegmentationDialog);
        minimumLcdNumber->setObjectName(QString::fromUtf8("minimumLcdNumber"));
        minimumLcdNumber->setGeometry(QRect(650, 480, 41, 31));
        minimumLcdNumber->setLineWidth(0);
        minimumLcdNumber->setMidLineWidth(1);
        minimumLcdNumber->setDigitCount(3);
        minimumLcdNumber->setMode(QLCDNumber::Dec);
        minimumLcdNumber->setSegmentStyle(QLCDNumber::Flat);
        minimumLcdNumber->setProperty("intValue", QVariant(255));
        maximumVerticalSlider = new QSlider(MaggicSegmentationDialog);
        maximumVerticalSlider->setObjectName(QString::fromUtf8("maximumVerticalSlider"));
        maximumVerticalSlider->setGeometry(QRect(711, 369, 20, 111));
        maximumVerticalSlider->setMinimum(3);
        maximumVerticalSlider->setMaximum(255);
        maximumVerticalSlider->setValue(3);
        maximumVerticalSlider->setOrientation(Qt::Vertical);
        maximumLcdNumber = new QLCDNumber(MaggicSegmentationDialog);
        maximumLcdNumber->setObjectName(QString::fromUtf8("maximumLcdNumber"));
        maximumLcdNumber->setGeometry(QRect(700, 480, 41, 31));
        maximumLcdNumber->setLineWidth(0);
        maximumLcdNumber->setMidLineWidth(1);
        maximumLcdNumber->setDigitCount(3);
        maximumLcdNumber->setMode(QLCDNumber::Dec);
        maximumLcdNumber->setSegmentStyle(QLCDNumber::Flat);
        maximumLcdNumber->setProperty("intValue", QVariant(255));
        resetButton = new QPushButton(MaggicSegmentationDialog);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));
        resetButton->setGeometry(QRect(650, 520, 89, 31));
        fixCameraButton = new QPushButton(MaggicSegmentationDialog);
        fixCameraButton->setObjectName(QString::fromUtf8("fixCameraButton"));
        fixCameraButton->setGeometry(QRect(20, 530, 121, 25));
        threshGrayHorizontalSlider = new QSlider(MaggicSegmentationDialog);
        threshGrayHorizontalSlider->setObjectName(QString::fromUtf8("threshGrayHorizontalSlider"));
        threshGrayHorizontalSlider->setGeometry(QRect(260, 510, 160, 21));
        threshGrayHorizontalSlider->setMinimum(1);
        threshGrayHorizontalSlider->setMaximum(255);
        threshGrayHorizontalSlider->setOrientation(Qt::Horizontal);
        threshGrayLcdNumber = new QLCDNumber(MaggicSegmentationDialog);
        threshGrayLcdNumber->setObjectName(QString::fromUtf8("threshGrayLcdNumber"));
        threshGrayLcdNumber->setGeometry(QRect(320, 530, 41, 31));
        threshGrayLcdNumber->setLineWidth(0);
        threshGrayLcdNumber->setMidLineWidth(1);
        threshGrayLcdNumber->setDigitCount(3);
        threshGrayLcdNumber->setMode(QLCDNumber::Dec);
        threshGrayLcdNumber->setSegmentStyle(QLCDNumber::Flat);
        threshGrayLcdNumber->setProperty("intValue", QVariant(255));
        playpauseButton = new QPushButton(MaggicSegmentationDialog);
        playpauseButton->setObjectName(QString::fromUtf8("playpauseButton"));
        playpauseButton->setGeometry(QRect(158, 530, 91, 21));
        playpauseButton->setCheckable(true);
        applyLUTButton = new QPushButton(MaggicSegmentationDialog);
        applyLUTButton->setObjectName(QString::fromUtf8("applyLUTButton"));
        applyLUTButton->setEnabled(true);
        applyLUTButton->setGeometry(QRect(650, 330, 91, 25));

        retranslateUi(MaggicSegmentationDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), MaggicSegmentationDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), MaggicSegmentationDialog, SLOT(reject()));

        tabWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MaggicSegmentationDialog);
    } // setupUi

    void retranslateUi(QDialog *MaggicSegmentationDialog)
    {
        MaggicSegmentationDialog->setWindowTitle(QApplication::translate("MaggicSegmentationDialog", "MaggicVision", nullptr));
        label->setText(QApplication::translate("MaggicSegmentationDialog", "Entities", nullptr));
        entitiesButton_1->setText(QApplication::translate("MaggicSegmentationDialog", "1", nullptr));
#ifndef QT_NO_SHORTCUT
        entitiesButton_1->setShortcut(QApplication::translate("MaggicSegmentationDialog", "1", nullptr));
#endif // QT_NO_SHORTCUT
        entitiesButton_2->setText(QApplication::translate("MaggicSegmentationDialog", "2", nullptr));
#ifndef QT_NO_SHORTCUT
        entitiesButton_2->setShortcut(QApplication::translate("MaggicSegmentationDialog", "2", nullptr));
#endif // QT_NO_SHORTCUT
        entitiesButton_3->setText(QApplication::translate("MaggicSegmentationDialog", "3", nullptr));
#ifndef QT_NO_SHORTCUT
        entitiesButton_3->setShortcut(QApplication::translate("MaggicSegmentationDialog", "3", nullptr));
#endif // QT_NO_SHORTCUT
        entitiesButton_4->setText(QApplication::translate("MaggicSegmentationDialog", "4", nullptr));
#ifndef QT_NO_SHORTCUT
        entitiesButton_4->setShortcut(QApplication::translate("MaggicSegmentationDialog", "4", nullptr));
#endif // QT_NO_SHORTCUT
        entitiesButton_5->setText(QApplication::translate("MaggicSegmentationDialog", "5", nullptr));
#ifndef QT_NO_SHORTCUT
        entitiesButton_5->setShortcut(QApplication::translate("MaggicSegmentationDialog", "5", nullptr));
#endif // QT_NO_SHORTCUT
        entitiesButton_6->setText(QApplication::translate("MaggicSegmentationDialog", "6", nullptr));
#ifndef QT_NO_SHORTCUT
        entitiesButton_6->setShortcut(QApplication::translate("MaggicSegmentationDialog", "6", nullptr));
#endif // QT_NO_SHORTCUT
        entitiesButton_7->setText(QApplication::translate("MaggicSegmentationDialog", "7", nullptr));
#ifndef QT_NO_SHORTCUT
        entitiesButton_7->setShortcut(QApplication::translate("MaggicSegmentationDialog", "7", nullptr));
#endif // QT_NO_SHORTCUT
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MaggicSegmentationDialog", "Extreme Saturation", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MaggicSegmentationDialog", "Multiplied Results", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MaggicSegmentationDialog", "Thresholded", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MaggicSegmentationDialog", "Segmented", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MaggicSegmentationDialog", "Details", nullptr));
        visualizationLabel->setText(QString());
        loadButton->setText(QApplication::translate("MaggicSegmentationDialog", "Load Config", nullptr));
#ifndef QT_NO_SHORTCUT
        loadButton->setShortcut(QApplication::translate("MaggicSegmentationDialog", "T", nullptr));
#endif // QT_NO_SHORTCUT
        resetButton->setText(QApplication::translate("MaggicSegmentationDialog", "Reset", nullptr));
        fixCameraButton->setText(QApplication::translate("MaggicSegmentationDialog", "Fix Camera", nullptr));
#ifndef QT_NO_SHORTCUT
        fixCameraButton->setShortcut(QApplication::translate("MaggicSegmentationDialog", "F", nullptr));
#endif // QT_NO_SHORTCUT
        playpauseButton->setText(QApplication::translate("MaggicSegmentationDialog", "Play/Pause", nullptr));
#ifndef QT_NO_SHORTCUT
        playpauseButton->setShortcut(QApplication::translate("MaggicSegmentationDialog", "P", nullptr));
#endif // QT_NO_SHORTCUT
        applyLUTButton->setText(QApplication::translate("MaggicSegmentationDialog", "Aplicar!", nullptr));
#ifndef QT_NO_SHORTCUT
        applyLUTButton->setShortcut(QApplication::translate("MaggicSegmentationDialog", "T", nullptr));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class MaggicSegmentationDialog: public Ui_MaggicSegmentationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAGGICSEGMENTATIONDIALOG_H
