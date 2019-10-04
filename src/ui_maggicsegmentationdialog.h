/********************************************************************************
** Form generated from reading UI file 'maggicsegmentationdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAGGICSEGMENTATIONDIALOG_H
#define UI_MAGGICSEGMENTATIONDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
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
            MaggicSegmentationDialog->setObjectName(QStringLiteral("MaggicSegmentationDialog"));
        MaggicSegmentationDialog->resize(750, 562);
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/icon/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MaggicSegmentationDialog->setWindowIcon(icon);
        MaggicSegmentationDialog->setWindowOpacity(1);
        buttonBox = new QDialogButtonBox(MaggicSegmentationDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(460, 520, 171, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        verticalLayoutWidget = new QWidget(MaggicSegmentationDialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(650, 10, 91, 241));
        entitiesLayout = new QVBoxLayout(verticalLayoutWidget);
        entitiesLayout->setSpacing(6);
        entitiesLayout->setObjectName(QStringLiteral("entitiesLayout"));
        entitiesLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignHCenter|Qt::AlignTop);

        entitiesLayout->addWidget(label);

        entitiesButton_1 = new QPushButton(verticalLayoutWidget);
        entitiesButton_1->setObjectName(QStringLiteral("entitiesButton_1"));
        entitiesButton_1->setEnabled(true);
        entitiesButton_1->setCheckable(true);
        entitiesButton_1->setFlat(false);

        entitiesLayout->addWidget(entitiesButton_1);

        entitiesButton_2 = new QPushButton(verticalLayoutWidget);
        entitiesButton_2->setObjectName(QStringLiteral("entitiesButton_2"));
        entitiesButton_2->setCheckable(true);

        entitiesLayout->addWidget(entitiesButton_2);

        entitiesButton_3 = new QPushButton(verticalLayoutWidget);
        entitiesButton_3->setObjectName(QStringLiteral("entitiesButton_3"));
        entitiesButton_3->setAutoFillBackground(false);
        entitiesButton_3->setCheckable(true);
        entitiesButton_3->setChecked(false);

        entitiesLayout->addWidget(entitiesButton_3);

        entitiesButton_4 = new QPushButton(verticalLayoutWidget);
        entitiesButton_4->setObjectName(QStringLiteral("entitiesButton_4"));
        entitiesButton_4->setCheckable(true);

        entitiesLayout->addWidget(entitiesButton_4);

        entitiesButton_5 = new QPushButton(verticalLayoutWidget);
        entitiesButton_5->setObjectName(QStringLiteral("entitiesButton_5"));
        entitiesButton_5->setCheckable(true);

        entitiesLayout->addWidget(entitiesButton_5);

        entitiesButton_6 = new QPushButton(verticalLayoutWidget);
        entitiesButton_6->setObjectName(QStringLiteral("entitiesButton_6"));
        entitiesButton_6->setCheckable(true);

        entitiesLayout->addWidget(entitiesButton_6);

        entitiesButton_7 = new QPushButton(verticalLayoutWidget);
        entitiesButton_7->setObjectName(QStringLiteral("entitiesButton_7"));
        entitiesButton_7->setCheckable(true);

        entitiesLayout->addWidget(entitiesButton_7);

        tabWidget = new QTabWidget(MaggicSegmentationDialog);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 642, 511));
        tabWidget->setTabShape(QTabWidget::Triangular);
        tab_1 = new QWidget();
        tab_1->setObjectName(QStringLiteral("tab_1"));
        tabWidget->addTab(tab_1, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        tabWidget->addTab(tab_5, QString());
        visualizationLabel = new QLabel(MaggicSegmentationDialog);
        visualizationLabel->setObjectName(QStringLiteral("visualizationLabel"));
        visualizationLabel->setGeometry(QRect(1, 28, 640, 480));
        visualizationLabel->setMouseTracking(true);
        visualizationLabel->setAutoFillBackground(true);
        learningProgressBar = new QProgressBar(MaggicSegmentationDialog);
        learningProgressBar->setObjectName(QStringLiteral("learningProgressBar"));
        learningProgressBar->setEnabled(false);
        learningProgressBar->setGeometry(QRect(650, 300, 91, 23));
        learningProgressBar->setMaximum(100);
        learningProgressBar->setValue(40);
        loadButton = new QPushButton(MaggicSegmentationDialog);
        loadButton->setObjectName(QStringLiteral("loadButton"));
        loadButton->setEnabled(true);
        loadButton->setGeometry(QRect(650, 300, 91, 25));
        line = new QFrame(MaggicSegmentationDialog);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(650, 250, 91, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        learnSpinBox = new QSpinBox(MaggicSegmentationDialog);
        learnSpinBox->setObjectName(QStringLiteral("learnSpinBox"));
        learnSpinBox->setEnabled(false);
        learnSpinBox->setGeometry(QRect(650, 270, 91, 26));
        learnSpinBox->setMinimum(1);
        learnSpinBox->setMaximum(1000);
        learnSpinBox->setSingleStep(10);
        learnSpinBox->setValue(60);
        minimumVerticalSlider = new QSlider(MaggicSegmentationDialog);
        minimumVerticalSlider->setObjectName(QStringLiteral("minimumVerticalSlider"));
        minimumVerticalSlider->setGeometry(QRect(661, 369, 20, 111));
        minimumVerticalSlider->setMinimum(1);
        minimumVerticalSlider->setMaximum(255);
        minimumVerticalSlider->setValue(1);
        minimumVerticalSlider->setOrientation(Qt::Vertical);
        minimumLcdNumber = new QLCDNumber(MaggicSegmentationDialog);
        minimumLcdNumber->setObjectName(QStringLiteral("minimumLcdNumber"));
        minimumLcdNumber->setGeometry(QRect(650, 480, 41, 31));
        minimumLcdNumber->setLineWidth(0);
        minimumLcdNumber->setMidLineWidth(1);
        minimumLcdNumber->setDigitCount(3);
        minimumLcdNumber->setMode(QLCDNumber::Dec);
        minimumLcdNumber->setSegmentStyle(QLCDNumber::Flat);
        minimumLcdNumber->setProperty("intValue", QVariant(255));
        maximumVerticalSlider = new QSlider(MaggicSegmentationDialog);
        maximumVerticalSlider->setObjectName(QStringLiteral("maximumVerticalSlider"));
        maximumVerticalSlider->setGeometry(QRect(711, 369, 20, 111));
        maximumVerticalSlider->setMinimum(3);
        maximumVerticalSlider->setMaximum(255);
        maximumVerticalSlider->setValue(3);
        maximumVerticalSlider->setOrientation(Qt::Vertical);
        maximumLcdNumber = new QLCDNumber(MaggicSegmentationDialog);
        maximumLcdNumber->setObjectName(QStringLiteral("maximumLcdNumber"));
        maximumLcdNumber->setGeometry(QRect(700, 480, 41, 31));
        maximumLcdNumber->setLineWidth(0);
        maximumLcdNumber->setMidLineWidth(1);
        maximumLcdNumber->setDigitCount(3);
        maximumLcdNumber->setMode(QLCDNumber::Dec);
        maximumLcdNumber->setSegmentStyle(QLCDNumber::Flat);
        maximumLcdNumber->setProperty("intValue", QVariant(255));
        resetButton = new QPushButton(MaggicSegmentationDialog);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setGeometry(QRect(650, 520, 89, 31));
        fixCameraButton = new QPushButton(MaggicSegmentationDialog);
        fixCameraButton->setObjectName(QStringLiteral("fixCameraButton"));
        fixCameraButton->setGeometry(QRect(20, 530, 121, 25));
        threshGrayHorizontalSlider = new QSlider(MaggicSegmentationDialog);
        threshGrayHorizontalSlider->setObjectName(QStringLiteral("threshGrayHorizontalSlider"));
        threshGrayHorizontalSlider->setGeometry(QRect(260, 510, 160, 21));
        threshGrayHorizontalSlider->setMinimum(1);
        threshGrayHorizontalSlider->setMaximum(255);
        threshGrayHorizontalSlider->setOrientation(Qt::Horizontal);
        threshGrayLcdNumber = new QLCDNumber(MaggicSegmentationDialog);
        threshGrayLcdNumber->setObjectName(QStringLiteral("threshGrayLcdNumber"));
        threshGrayLcdNumber->setGeometry(QRect(320, 530, 41, 31));
        threshGrayLcdNumber->setLineWidth(0);
        threshGrayLcdNumber->setMidLineWidth(1);
        threshGrayLcdNumber->setDigitCount(3);
        threshGrayLcdNumber->setMode(QLCDNumber::Dec);
        threshGrayLcdNumber->setSegmentStyle(QLCDNumber::Flat);
        threshGrayLcdNumber->setProperty("intValue", QVariant(255));
        playpauseButton = new QPushButton(MaggicSegmentationDialog);
        playpauseButton->setObjectName(QStringLiteral("playpauseButton"));
        playpauseButton->setGeometry(QRect(158, 530, 91, 21));
        playpauseButton->setCheckable(true);
        applyLUTButton = new QPushButton(MaggicSegmentationDialog);
        applyLUTButton->setObjectName(QStringLiteral("applyLUTButton"));
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
        MaggicSegmentationDialog->setWindowTitle(QApplication::translate("MaggicSegmentationDialog", "MaggicVision", Q_NULLPTR));
        label->setText(QApplication::translate("MaggicSegmentationDialog", "Entities", Q_NULLPTR));
        entitiesButton_1->setText(QApplication::translate("MaggicSegmentationDialog", "1", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        entitiesButton_1->setShortcut(QApplication::translate("MaggicSegmentationDialog", "1", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        entitiesButton_2->setText(QApplication::translate("MaggicSegmentationDialog", "2", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        entitiesButton_2->setShortcut(QApplication::translate("MaggicSegmentationDialog", "2", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        entitiesButton_3->setText(QApplication::translate("MaggicSegmentationDialog", "3", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        entitiesButton_3->setShortcut(QApplication::translate("MaggicSegmentationDialog", "3", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        entitiesButton_4->setText(QApplication::translate("MaggicSegmentationDialog", "4", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        entitiesButton_4->setShortcut(QApplication::translate("MaggicSegmentationDialog", "4", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        entitiesButton_5->setText(QApplication::translate("MaggicSegmentationDialog", "5", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        entitiesButton_5->setShortcut(QApplication::translate("MaggicSegmentationDialog", "5", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        entitiesButton_6->setText(QApplication::translate("MaggicSegmentationDialog", "6", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        entitiesButton_6->setShortcut(QApplication::translate("MaggicSegmentationDialog", "6", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        entitiesButton_7->setText(QApplication::translate("MaggicSegmentationDialog", "7", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        entitiesButton_7->setShortcut(QApplication::translate("MaggicSegmentationDialog", "7", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        tabWidget->setTabText(tabWidget->indexOf(tab_1), QApplication::translate("MaggicSegmentationDialog", "Extreme Saturation", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MaggicSegmentationDialog", "Multiplied Results", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MaggicSegmentationDialog", "Thresholded", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MaggicSegmentationDialog", "Segmented", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MaggicSegmentationDialog", "Details", Q_NULLPTR));
        visualizationLabel->setText(QString());
        loadButton->setText(QApplication::translate("MaggicSegmentationDialog", "Load Config", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        loadButton->setShortcut(QApplication::translate("MaggicSegmentationDialog", "T", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        resetButton->setText(QApplication::translate("MaggicSegmentationDialog", "Reset", Q_NULLPTR));
        fixCameraButton->setText(QApplication::translate("MaggicSegmentationDialog", "Fix Camera", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        fixCameraButton->setShortcut(QApplication::translate("MaggicSegmentationDialog", "F", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        playpauseButton->setText(QApplication::translate("MaggicSegmentationDialog", "Play/Pause", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        playpauseButton->setShortcut(QApplication::translate("MaggicSegmentationDialog", "P", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        applyLUTButton->setText(QApplication::translate("MaggicSegmentationDialog", "Aplicar!", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        applyLUTButton->setShortcut(QApplication::translate("MaggicSegmentationDialog", "T", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class MaggicSegmentationDialog: public Ui_MaggicSegmentationDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAGGICSEGMENTATIONDIALOG_H
