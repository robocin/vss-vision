/********************************************************************************
** Form generated from reading UI file 'RobotWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOTWIDGET_H
#define UI_ROBOTWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RobotWidget
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *upWidgetRobot;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *spacer1Robot;
    QLabel *numberRobot;
    QSpacerItem *spacer2Robot;
    QLabel *settingsLabelRobot;
    QToolButton *toolsButtonRobot;
    QSpacerItem *spacer3Robot;
    QGroupBox *aboutRobot;
    QHBoxLayout *horizontalLayout_13;
    QWidget *aboutGroupRobot;
    QHBoxLayout *horizontalLayout_14;
    QWidget *aboutNamesRobot;
    QVBoxLayout *verticalLayout_13;
    QLabel *positionLabelRobot;
    QLabel *speedLabelRobot;
    QLabel *angleLabelRobot;
    QWidget *aboutValuesRobot;
    QVBoxLayout *verticalLayout_14;
    QLabel *positionValueRobot;
    QLabel *speedValueRobot;
    QLabel *angleValueRobot;
    QLabel *idRobot;

    void setupUi(QWidget *RobotWidget)
    {
        if (RobotWidget->objectName().isEmpty())
            RobotWidget->setObjectName(QString::fromUtf8("RobotWidget"));
        RobotWidget->resize(270, 200);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RobotWidget->sizePolicy().hasHeightForWidth());
        RobotWidget->setSizePolicy(sizePolicy);
        RobotWidget->setMinimumSize(QSize(270, 200));
        RobotWidget->setMaximumSize(QSize(320, 16777215));
        verticalLayout = new QVBoxLayout(RobotWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        upWidgetRobot = new QWidget(RobotWidget);
        upWidgetRobot->setObjectName(QString::fromUtf8("upWidgetRobot"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(upWidgetRobot->sizePolicy().hasHeightForWidth());
        upWidgetRobot->setSizePolicy(sizePolicy1);
        upWidgetRobot->setMaximumSize(QSize(16777215, 70));
        horizontalLayout_4 = new QHBoxLayout(upWidgetRobot);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        spacer1Robot = new QSpacerItem(1, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(spacer1Robot);

        numberRobot = new QLabel(upWidgetRobot);
        numberRobot->setObjectName(QString::fromUtf8("numberRobot"));
        sizePolicy1.setHeightForWidth(numberRobot->sizePolicy().hasHeightForWidth());
        numberRobot->setSizePolicy(sizePolicy1);
        numberRobot->setMinimumSize(QSize(20, 20));
        numberRobot->setMaximumSize(QSize(50, 50));
        numberRobot->setPixmap(QPixmap(QString::fromUtf8(":/image/icon/021-keyboard-key-1.png")));
        numberRobot->setScaledContents(true);

        horizontalLayout_4->addWidget(numberRobot);

        spacer2Robot = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(spacer2Robot);

        settingsLabelRobot = new QLabel(upWidgetRobot);
        settingsLabelRobot->setObjectName(QString::fromUtf8("settingsLabelRobot"));

        horizontalLayout_4->addWidget(settingsLabelRobot);

        toolsButtonRobot = new QToolButton(upWidgetRobot);
        toolsButtonRobot->setObjectName(QString::fromUtf8("toolsButtonRobot"));
        sizePolicy1.setHeightForWidth(toolsButtonRobot->sizePolicy().hasHeightForWidth());
        toolsButtonRobot->setSizePolicy(sizePolicy1);
        toolsButtonRobot->setMaximumSize(QSize(40, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/icon/012-settings-work-tool.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolsButtonRobot->setIcon(icon);
        toolsButtonRobot->setCheckable(false);

        horizontalLayout_4->addWidget(toolsButtonRobot);

        spacer3Robot = new QSpacerItem(13, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(spacer3Robot);


        verticalLayout->addWidget(upWidgetRobot);

        aboutRobot = new QGroupBox(RobotWidget);
        aboutRobot->setObjectName(QString::fromUtf8("aboutRobot"));
        aboutRobot->setMaximumSize(QSize(16777215, 120));
        horizontalLayout_13 = new QHBoxLayout(aboutRobot);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(1, 1, 1, 1);
        aboutGroupRobot = new QWidget(aboutRobot);
        aboutGroupRobot->setObjectName(QString::fromUtf8("aboutGroupRobot"));
        sizePolicy.setHeightForWidth(aboutGroupRobot->sizePolicy().hasHeightForWidth());
        aboutGroupRobot->setSizePolicy(sizePolicy);
        aboutGroupRobot->setMinimumSize(QSize(95, 65));
        horizontalLayout_14 = new QHBoxLayout(aboutGroupRobot);
        horizontalLayout_14->setSpacing(0);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        aboutNamesRobot = new QWidget(aboutGroupRobot);
        aboutNamesRobot->setObjectName(QString::fromUtf8("aboutNamesRobot"));
        verticalLayout_13 = new QVBoxLayout(aboutNamesRobot);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        positionLabelRobot = new QLabel(aboutNamesRobot);
        positionLabelRobot->setObjectName(QString::fromUtf8("positionLabelRobot"));
        positionLabelRobot->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(positionLabelRobot);

        speedLabelRobot = new QLabel(aboutNamesRobot);
        speedLabelRobot->setObjectName(QString::fromUtf8("speedLabelRobot"));
        speedLabelRobot->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(speedLabelRobot);

        angleLabelRobot = new QLabel(aboutNamesRobot);
        angleLabelRobot->setObjectName(QString::fromUtf8("angleLabelRobot"));
        angleLabelRobot->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(angleLabelRobot);


        horizontalLayout_14->addWidget(aboutNamesRobot);

        aboutValuesRobot = new QWidget(aboutGroupRobot);
        aboutValuesRobot->setObjectName(QString::fromUtf8("aboutValuesRobot"));
        aboutValuesRobot->setMaximumSize(QSize(16777215, 100));
        verticalLayout_14 = new QVBoxLayout(aboutValuesRobot);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        positionValueRobot = new QLabel(aboutValuesRobot);
        positionValueRobot->setObjectName(QString::fromUtf8("positionValueRobot"));
        positionValueRobot->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(positionValueRobot);

        speedValueRobot = new QLabel(aboutValuesRobot);
        speedValueRobot->setObjectName(QString::fromUtf8("speedValueRobot"));
        speedValueRobot->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(speedValueRobot);

        angleValueRobot = new QLabel(aboutValuesRobot);
        angleValueRobot->setObjectName(QString::fromUtf8("angleValueRobot"));
        angleValueRobot->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(angleValueRobot);


        horizontalLayout_14->addWidget(aboutValuesRobot);


        horizontalLayout_13->addWidget(aboutGroupRobot);

        idRobot = new QLabel(aboutRobot);
        idRobot->setObjectName(QString::fromUtf8("idRobot"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(idRobot->sizePolicy().hasHeightForWidth());
        idRobot->setSizePolicy(sizePolicy2);
        idRobot->setMinimumSize(QSize(30, 30));
        idRobot->setMaximumSize(QSize(70, 70));
        idRobot->setPixmap(QPixmap(QString::fromUtf8(":/image/icon/border.png")));
        idRobot->setScaledContents(true);
        idRobot->setAlignment(Qt::AlignCenter);

        horizontalLayout_13->addWidget(idRobot);


        verticalLayout->addWidget(aboutRobot);


        retranslateUi(RobotWidget);

        QMetaObject::connectSlotsByName(RobotWidget);
    } // setupUi

    void retranslateUi(QWidget *RobotWidget)
    {
        RobotWidget->setWindowTitle(QApplication::translate("RobotWidget", "Form", nullptr));
        numberRobot->setText(QString());
        settingsLabelRobot->setText(QApplication::translate("RobotWidget", "Settings:", nullptr));
        toolsButtonRobot->setText(QApplication::translate("RobotWidget", "...", nullptr));
        aboutRobot->setTitle(QApplication::translate("RobotWidget", "About:", nullptr));
        positionLabelRobot->setText(QApplication::translate("RobotWidget", "Pos.:", nullptr));
        speedLabelRobot->setText(QApplication::translate("RobotWidget", "Spd.:", nullptr));
        angleLabelRobot->setText(QApplication::translate("RobotWidget", "Ang.:", nullptr));
        positionValueRobot->setText(QApplication::translate("RobotWidget", "-", nullptr));
        speedValueRobot->setText(QApplication::translate("RobotWidget", "-", nullptr));
        angleValueRobot->setText(QApplication::translate("RobotWidget", "-", nullptr));
        idRobot->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RobotWidget: public Ui_RobotWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOTWIDGET_H
