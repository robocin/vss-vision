/********************************************************************************
** Form generated from reading UI file 'trackconfigdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TRACKCONFIGDIALOG_H
#define UI_TRACKCONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_TrackConfigDialog
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *videoLabel;
    QTreeWidget *treeWidget;
    QFrame *frame;
    QLabel *label_2;
    QSlider *verticalSlider__MinSize;
    QLabel *label;
    QSlider *verticalSlider__MaxSize;
    QLabel *label_3;
    QSlider *verticalSlider__MinSizeBall;
    QSlider *verticalSlider__MaxSizeBall;
    QLabel *label_4;
    QLabel *label_MinSize;
    QLabel *label_MaxSize;
    QLabel *label_MinBall;
    QLabel *label_MaxBall;
    QComboBox *comboBox_EnemySearch;
    QPushButton *pushButton_Reset;
    QFrame *frame_KMeans;
    QSlider *verticalSlider_orange;
    QLabel *label_5;
    QFrame *frame_orange;
    QLabel *label_orange;
    QFrame *frame_blue;
    QLabel *label_blue;
    QSlider *verticalSlider_blue;
    QFrame *frame_yellow;
    QLabel *label_yellow;
    QSlider *verticalSlider_yellow;
    QFrame *frame_red;
    QLabel *label_red;
    QSlider *verticalSlider_red;
    QFrame *frame_green;
    QLabel *label_green;
    QSlider *verticalSlider_green;
    QFrame *frame_pink;
    QLabel *label_pink;
    QSlider *verticalSlider_pink;
    QFrame *frame_light_blue;
    QLabel *label_light_blue;
    QSlider *verticalSlider_light_blue;
    QFrame *frame_purple;
    QLabel *label_purple;
    QSlider *verticalSlider_purple;
    QFrame *frame_unknown;
    QLabel *label_unknown;
    QSlider *verticalSlider_unknown;
    QFrame *frame_default;

    void setupUi(QDialog *TrackConfigDialog)
    {
        if (TrackConfigDialog->objectName().isEmpty())
            TrackConfigDialog->setObjectName(QString::fromUtf8("TrackConfigDialog"));
        TrackConfigDialog->resize(1201, 711);
        buttonBox = new QDialogButtonBox(TrackConfigDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(850, 671, 341, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        videoLabel = new QLabel(TrackConfigDialog);
        videoLabel->setObjectName(QString::fromUtf8("videoLabel"));
        videoLabel->setGeometry(QRect(420, 20, 640, 480));
        treeWidget = new QTreeWidget(TrackConfigDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        QTreeWidgetItem *__qtreewidgetitem1 = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem1);
        new QTreeWidgetItem(__qtreewidgetitem1);
        treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
        treeWidget->setGeometry(QRect(0, 0, 261, 251));
        frame = new QFrame(TrackConfigDialog);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(10, 260, 261, 411));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 10, 67, 20));
        verticalSlider__MinSize = new QSlider(frame);
        verticalSlider__MinSize->setObjectName(QString::fromUtf8("verticalSlider__MinSize"));
        verticalSlider__MinSize->setGeometry(QRect(30, 70, 16, 311));
        verticalSlider__MinSize->setMinimum(1);
        verticalSlider__MinSize->setMaximum(1000);
        verticalSlider__MinSize->setOrientation(Qt::Vertical);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 10, 71, 20));
        verticalSlider__MaxSize = new QSlider(frame);
        verticalSlider__MaxSize->setObjectName(QString::fromUtf8("verticalSlider__MaxSize"));
        verticalSlider__MaxSize->setGeometry(QRect(90, 70, 16, 311));
        verticalSlider__MaxSize->setMinimum(1);
        verticalSlider__MaxSize->setMaximum(1000);
        verticalSlider__MaxSize->setOrientation(Qt::Vertical);
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(130, 10, 61, 20));
        verticalSlider__MinSizeBall = new QSlider(frame);
        verticalSlider__MinSizeBall->setObjectName(QString::fromUtf8("verticalSlider__MinSizeBall"));
        verticalSlider__MinSizeBall->setGeometry(QRect(150, 70, 16, 311));
        verticalSlider__MinSizeBall->setMinimum(1);
        verticalSlider__MinSizeBall->setMaximum(1000);
        verticalSlider__MinSizeBall->setOrientation(Qt::Vertical);
        verticalSlider__MaxSizeBall = new QSlider(frame);
        verticalSlider__MaxSizeBall->setObjectName(QString::fromUtf8("verticalSlider__MaxSizeBall"));
        verticalSlider__MaxSizeBall->setGeometry(QRect(210, 70, 16, 311));
        verticalSlider__MaxSizeBall->setMinimum(1);
        verticalSlider__MaxSizeBall->setMaximum(1000);
        verticalSlider__MaxSizeBall->setOrientation(Qt::Vertical);
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(190, 10, 61, 20));
        label_MinSize = new QLabel(frame);
        label_MinSize->setObjectName(QString::fromUtf8("label_MinSize"));
        label_MinSize->setGeometry(QRect(20, 40, 31, 20));
        label_MaxSize = new QLabel(frame);
        label_MaxSize->setObjectName(QString::fromUtf8("label_MaxSize"));
        label_MaxSize->setGeometry(QRect(80, 40, 31, 20));
        label_MinBall = new QLabel(frame);
        label_MinBall->setObjectName(QString::fromUtf8("label_MinBall"));
        label_MinBall->setGeometry(QRect(140, 40, 31, 20));
        label_MaxBall = new QLabel(frame);
        label_MaxBall->setObjectName(QString::fromUtf8("label_MaxBall"));
        label_MaxBall->setGeometry(QRect(200, 40, 31, 20));
        comboBox_EnemySearch = new QComboBox(frame);
        comboBox_EnemySearch->addItem(QString());
        comboBox_EnemySearch->addItem(QString());
        comboBox_EnemySearch->addItem(QString());
        comboBox_EnemySearch->addItem(QString());
        comboBox_EnemySearch->setObjectName(QString::fromUtf8("comboBox_EnemySearch"));
        comboBox_EnemySearch->setGeometry(QRect(80, 385, 86, 20));
        pushButton_Reset = new QPushButton(TrackConfigDialog);
        pushButton_Reset->setObjectName(QString::fromUtf8("pushButton_Reset"));
        pushButton_Reset->setGeometry(QRect(0, 680, 261, 25));
        frame_KMeans = new QFrame(TrackConfigDialog);
        frame_KMeans->setObjectName(QString::fromUtf8("frame_KMeans"));
        frame_KMeans->setGeometry(QRect(270, 520, 921, 151));
        frame_KMeans->setFrameShape(QFrame::StyledPanel);
        frame_KMeans->setFrameShadow(QFrame::Raised);
        frame_KMeans->setLineWidth(0);
        verticalSlider_orange = new QSlider(frame_KMeans);
        verticalSlider_orange->setObjectName(QString::fromUtf8("verticalSlider_orange"));
        verticalSlider_orange->setGeometry(QRect(70, 40, 20, 101));
        verticalSlider_orange->setMaximum(5);
        verticalSlider_orange->setOrientation(Qt::Vertical);
        label_5 = new QLabel(frame_KMeans);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(430, 10, 67, 17));
        label_5->setAlignment(Qt::AlignCenter);
        frame_orange = new QFrame(frame_KMeans);
        frame_orange->setObjectName(QString::fromUtf8("frame_orange"));
        frame_orange->setGeometry(QRect(30, 50, 31, 31));
        frame_orange->setFrameShape(QFrame::StyledPanel);
        frame_orange->setFrameShadow(QFrame::Raised);
        label_orange = new QLabel(frame_KMeans);
        label_orange->setObjectName(QString::fromUtf8("label_orange"));
        label_orange->setGeometry(QRect(30, 100, 31, 21));
        label_orange->setAlignment(Qt::AlignCenter);
        frame_blue = new QFrame(frame_KMeans);
        frame_blue->setObjectName(QString::fromUtf8("frame_blue"));
        frame_blue->setGeometry(QRect(130, 50, 31, 31));
        frame_blue->setFrameShape(QFrame::StyledPanel);
        frame_blue->setFrameShadow(QFrame::Raised);
        label_blue = new QLabel(frame_KMeans);
        label_blue->setObjectName(QString::fromUtf8("label_blue"));
        label_blue->setGeometry(QRect(130, 100, 31, 21));
        label_blue->setAlignment(Qt::AlignCenter);
        verticalSlider_blue = new QSlider(frame_KMeans);
        verticalSlider_blue->setObjectName(QString::fromUtf8("verticalSlider_blue"));
        verticalSlider_blue->setGeometry(QRect(170, 40, 20, 101));
        verticalSlider_blue->setMaximum(5);
        verticalSlider_blue->setOrientation(Qt::Vertical);
        frame_yellow = new QFrame(frame_KMeans);
        frame_yellow->setObjectName(QString::fromUtf8("frame_yellow"));
        frame_yellow->setGeometry(QRect(230, 50, 31, 31));
        frame_yellow->setFrameShape(QFrame::StyledPanel);
        frame_yellow->setFrameShadow(QFrame::Raised);
        label_yellow = new QLabel(frame_KMeans);
        label_yellow->setObjectName(QString::fromUtf8("label_yellow"));
        label_yellow->setGeometry(QRect(230, 100, 31, 21));
        label_yellow->setAlignment(Qt::AlignCenter);
        verticalSlider_yellow = new QSlider(frame_KMeans);
        verticalSlider_yellow->setObjectName(QString::fromUtf8("verticalSlider_yellow"));
        verticalSlider_yellow->setGeometry(QRect(270, 40, 20, 101));
        verticalSlider_yellow->setMaximum(5);
        verticalSlider_yellow->setOrientation(Qt::Vertical);
        frame_red = new QFrame(frame_KMeans);
        frame_red->setObjectName(QString::fromUtf8("frame_red"));
        frame_red->setGeometry(QRect(330, 50, 31, 31));
        frame_red->setFrameShape(QFrame::StyledPanel);
        frame_red->setFrameShadow(QFrame::Raised);
        label_red = new QLabel(frame_KMeans);
        label_red->setObjectName(QString::fromUtf8("label_red"));
        label_red->setGeometry(QRect(330, 100, 31, 21));
        label_red->setAlignment(Qt::AlignCenter);
        verticalSlider_red = new QSlider(frame_KMeans);
        verticalSlider_red->setObjectName(QString::fromUtf8("verticalSlider_red"));
        verticalSlider_red->setGeometry(QRect(370, 40, 20, 101));
        verticalSlider_red->setMaximum(5);
        verticalSlider_red->setOrientation(Qt::Vertical);
        frame_green = new QFrame(frame_KMeans);
        frame_green->setObjectName(QString::fromUtf8("frame_green"));
        frame_green->setGeometry(QRect(430, 50, 31, 31));
        frame_green->setFrameShape(QFrame::StyledPanel);
        frame_green->setFrameShadow(QFrame::Raised);
        label_green = new QLabel(frame_KMeans);
        label_green->setObjectName(QString::fromUtf8("label_green"));
        label_green->setGeometry(QRect(430, 100, 31, 21));
        label_green->setAlignment(Qt::AlignCenter);
        verticalSlider_green = new QSlider(frame_KMeans);
        verticalSlider_green->setObjectName(QString::fromUtf8("verticalSlider_green"));
        verticalSlider_green->setGeometry(QRect(470, 40, 20, 101));
        verticalSlider_green->setMaximum(5);
        verticalSlider_green->setOrientation(Qt::Vertical);
        frame_pink = new QFrame(frame_KMeans);
        frame_pink->setObjectName(QString::fromUtf8("frame_pink"));
        frame_pink->setGeometry(QRect(530, 50, 31, 31));
        frame_pink->setFrameShape(QFrame::StyledPanel);
        frame_pink->setFrameShadow(QFrame::Raised);
        label_pink = new QLabel(frame_KMeans);
        label_pink->setObjectName(QString::fromUtf8("label_pink"));
        label_pink->setGeometry(QRect(530, 100, 31, 21));
        label_pink->setAlignment(Qt::AlignCenter);
        verticalSlider_pink = new QSlider(frame_KMeans);
        verticalSlider_pink->setObjectName(QString::fromUtf8("verticalSlider_pink"));
        verticalSlider_pink->setGeometry(QRect(570, 40, 20, 101));
        verticalSlider_pink->setMaximum(5);
        verticalSlider_pink->setOrientation(Qt::Vertical);
        frame_light_blue = new QFrame(frame_KMeans);
        frame_light_blue->setObjectName(QString::fromUtf8("frame_light_blue"));
        frame_light_blue->setGeometry(QRect(630, 50, 31, 31));
        frame_light_blue->setFrameShape(QFrame::StyledPanel);
        frame_light_blue->setFrameShadow(QFrame::Raised);
        label_light_blue = new QLabel(frame_KMeans);
        label_light_blue->setObjectName(QString::fromUtf8("label_light_blue"));
        label_light_blue->setGeometry(QRect(630, 100, 31, 21));
        label_light_blue->setAlignment(Qt::AlignCenter);
        verticalSlider_light_blue = new QSlider(frame_KMeans);
        verticalSlider_light_blue->setObjectName(QString::fromUtf8("verticalSlider_light_blue"));
        verticalSlider_light_blue->setGeometry(QRect(670, 40, 20, 101));
        verticalSlider_light_blue->setMaximum(5);
        verticalSlider_light_blue->setOrientation(Qt::Vertical);
        frame_purple = new QFrame(frame_KMeans);
        frame_purple->setObjectName(QString::fromUtf8("frame_purple"));
        frame_purple->setGeometry(QRect(730, 50, 31, 31));
        frame_purple->setFrameShape(QFrame::StyledPanel);
        frame_purple->setFrameShadow(QFrame::Raised);
        label_purple = new QLabel(frame_KMeans);
        label_purple->setObjectName(QString::fromUtf8("label_purple"));
        label_purple->setGeometry(QRect(730, 100, 31, 21));
        label_purple->setAlignment(Qt::AlignCenter);
        verticalSlider_purple = new QSlider(frame_KMeans);
        verticalSlider_purple->setObjectName(QString::fromUtf8("verticalSlider_purple"));
        verticalSlider_purple->setGeometry(QRect(770, 40, 20, 101));
        verticalSlider_purple->setMaximum(5);
        verticalSlider_purple->setOrientation(Qt::Vertical);
        frame_unknown = new QFrame(frame_KMeans);
        frame_unknown->setObjectName(QString::fromUtf8("frame_unknown"));
        frame_unknown->setGeometry(QRect(830, 50, 31, 31));
        frame_unknown->setFrameShape(QFrame::StyledPanel);
        frame_unknown->setFrameShadow(QFrame::Raised);
        label_unknown = new QLabel(frame_KMeans);
        label_unknown->setObjectName(QString::fromUtf8("label_unknown"));
        label_unknown->setGeometry(QRect(830, 100, 31, 21));
        label_unknown->setAlignment(Qt::AlignCenter);
        verticalSlider_unknown = new QSlider(frame_KMeans);
        verticalSlider_unknown->setObjectName(QString::fromUtf8("verticalSlider_unknown"));
        verticalSlider_unknown->setGeometry(QRect(870, 40, 20, 101));
        verticalSlider_unknown->setMaximum(5);
        verticalSlider_unknown->setOrientation(Qt::Vertical);
        frame_default = new QFrame(TrackConfigDialog);
        frame_default->setObjectName(QString::fromUtf8("frame_default"));
        frame_default->setGeometry(QRect(270, 520, 921, 151));
        frame_default->setFrameShape(QFrame::StyledPanel);
        frame_default->setFrameShadow(QFrame::Raised);
        frame_default->raise();
        buttonBox->raise();
        videoLabel->raise();
        treeWidget->raise();
        frame->raise();
        pushButton_Reset->raise();
        frame_KMeans->raise();

        retranslateUi(TrackConfigDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TrackConfigDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TrackConfigDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TrackConfigDialog);
    } // setupUi

    void retranslateUi(QDialog *TrackConfigDialog)
    {
        TrackConfigDialog->setWindowTitle(QApplication::translate("TrackConfigDialog", "Dialog", nullptr));
        videoLabel->setText(QString());
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("TrackConfigDialog", "Track N Detection", nullptr));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("TrackConfigDialog", "Detection", nullptr));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("TrackConfigDialog", "WhereAreThose", nullptr));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("TrackConfigDialog", "None", nullptr));
        QTreeWidgetItem *___qtreewidgetitem4 = treeWidget->topLevelItem(1);
        ___qtreewidgetitem4->setText(0, QApplication::translate("TrackConfigDialog", "Tracking", nullptr));
        QTreeWidgetItem *___qtreewidgetitem5 = ___qtreewidgetitem4->child(0);
        ___qtreewidgetitem5->setText(0, QApplication::translate("TrackConfigDialog", "SimpleTracking", nullptr));
        QTreeWidgetItem *___qtreewidgetitem6 = ___qtreewidgetitem4->child(1);
        ___qtreewidgetitem6->setText(0, QApplication::translate("TrackConfigDialog", "None", nullptr));
        treeWidget->setSortingEnabled(__sortingEnabled);

        label_2->setText(QApplication::translate("TrackConfigDialog", "MinSize", nullptr));
        label->setText(QApplication::translate("TrackConfigDialog", "MaxSize", nullptr));
        label_3->setText(QApplication::translate("TrackConfigDialog", "MinBall", nullptr));
        label_4->setText(QApplication::translate("TrackConfigDialog", "MaxBall", nullptr));
        label_MinSize->setText(QApplication::translate("TrackConfigDialog", "000", nullptr));
        label_MaxSize->setText(QApplication::translate("TrackConfigDialog", "000", nullptr));
        label_MinBall->setText(QApplication::translate("TrackConfigDialog", "000", nullptr));
        label_MaxBall->setText(QApplication::translate("TrackConfigDialog", "000", nullptr));
        comboBox_EnemySearch->setItemText(0, QApplication::translate("TrackConfigDialog", "Nothing", nullptr));
        comboBox_EnemySearch->setItemText(1, QApplication::translate("TrackConfigDialog", "Primary", nullptr));
        comboBox_EnemySearch->setItemText(2, QApplication::translate("TrackConfigDialog", "Secondary", nullptr));
        comboBox_EnemySearch->setItemText(3, QApplication::translate("TrackConfigDialog", "Both", nullptr));

        pushButton_Reset->setText(QApplication::translate("TrackConfigDialog", "Reset", nullptr));
        label_5->setText(QApplication::translate("TrackConfigDialog", "KMeans", nullptr));
        label_orange->setText(QApplication::translate("TrackConfigDialog", "0", nullptr));
        label_blue->setText(QApplication::translate("TrackConfigDialog", "0", nullptr));
        label_yellow->setText(QApplication::translate("TrackConfigDialog", "0", nullptr));
        label_red->setText(QApplication::translate("TrackConfigDialog", "0", nullptr));
        label_green->setText(QApplication::translate("TrackConfigDialog", "0", nullptr));
        label_pink->setText(QApplication::translate("TrackConfigDialog", "0", nullptr));
        label_light_blue->setText(QApplication::translate("TrackConfigDialog", "0", nullptr));
        label_purple->setText(QApplication::translate("TrackConfigDialog", "0", nullptr));
        label_unknown->setText(QApplication::translate("TrackConfigDialog", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TrackConfigDialog: public Ui_TrackConfigDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TRACKCONFIGDIALOG_H
