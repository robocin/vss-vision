/********************************************************************************
** Form generated from reading UI file 'RobotWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROBOTWIDGET_H
#define UI_ROBOTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
            RobotWidget->setObjectName(QStringLiteral("RobotWidget"));
        RobotWidget->resize(270, 200);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RobotWidget->sizePolicy().hasHeightForWidth());
        RobotWidget->setSizePolicy(sizePolicy);
        RobotWidget->setMinimumSize(QSize(270, 200));
        RobotWidget->setMaximumSize(QSize(320, 16777215));
        verticalLayout = new QVBoxLayout(RobotWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        upWidgetRobot = new QWidget(RobotWidget);
        upWidgetRobot->setObjectName(QStringLiteral("upWidgetRobot"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(upWidgetRobot->sizePolicy().hasHeightForWidth());
        upWidgetRobot->setSizePolicy(sizePolicy1);
        upWidgetRobot->setMaximumSize(QSize(16777215, 70));
        horizontalLayout_4 = new QHBoxLayout(upWidgetRobot);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        spacer1Robot = new QSpacerItem(1, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(spacer1Robot);

        numberRobot = new QLabel(upWidgetRobot);
        numberRobot->setObjectName(QStringLiteral("numberRobot"));
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
        settingsLabelRobot->setObjectName(QStringLiteral("settingsLabelRobot"));

        horizontalLayout_4->addWidget(settingsLabelRobot);

        toolsButtonRobot = new QToolButton(upWidgetRobot);
        toolsButtonRobot->setObjectName(QStringLiteral("toolsButtonRobot"));
        sizePolicy1.setHeightForWidth(toolsButtonRobot->sizePolicy().hasHeightForWidth());
        toolsButtonRobot->setSizePolicy(sizePolicy1);
        toolsButtonRobot->setMaximumSize(QSize(40, 40));
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/icon/012-settings-work-tool.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolsButtonRobot->setIcon(icon);
        toolsButtonRobot->setCheckable(false);

        horizontalLayout_4->addWidget(toolsButtonRobot);

        spacer3Robot = new QSpacerItem(13, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(spacer3Robot);


        verticalLayout->addWidget(upWidgetRobot);

        aboutRobot = new QGroupBox(RobotWidget);
        aboutRobot->setObjectName(QStringLiteral("aboutRobot"));
        aboutRobot->setMaximumSize(QSize(16777215, 120));
        horizontalLayout_13 = new QHBoxLayout(aboutRobot);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QStringLiteral("horizontalLayout_13"));
        horizontalLayout_13->setContentsMargins(1, 1, 1, 1);
        aboutGroupRobot = new QWidget(aboutRobot);
        aboutGroupRobot->setObjectName(QStringLiteral("aboutGroupRobot"));
        sizePolicy.setHeightForWidth(aboutGroupRobot->sizePolicy().hasHeightForWidth());
        aboutGroupRobot->setSizePolicy(sizePolicy);
        aboutGroupRobot->setMinimumSize(QSize(95, 65));
        horizontalLayout_14 = new QHBoxLayout(aboutGroupRobot);
        horizontalLayout_14->setSpacing(0);
        horizontalLayout_14->setObjectName(QStringLiteral("horizontalLayout_14"));
        horizontalLayout_14->setContentsMargins(0, 0, 0, 0);
        aboutNamesRobot = new QWidget(aboutGroupRobot);
        aboutNamesRobot->setObjectName(QStringLiteral("aboutNamesRobot"));
        verticalLayout_13 = new QVBoxLayout(aboutNamesRobot);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        verticalLayout_13->setContentsMargins(0, 0, 0, 0);
        positionLabelRobot = new QLabel(aboutNamesRobot);
        positionLabelRobot->setObjectName(QStringLiteral("positionLabelRobot"));
        positionLabelRobot->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(positionLabelRobot);

        speedLabelRobot = new QLabel(aboutNamesRobot);
        speedLabelRobot->setObjectName(QStringLiteral("speedLabelRobot"));
        speedLabelRobot->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(speedLabelRobot);

        angleLabelRobot = new QLabel(aboutNamesRobot);
        angleLabelRobot->setObjectName(QStringLiteral("angleLabelRobot"));
        angleLabelRobot->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(angleLabelRobot);


        horizontalLayout_14->addWidget(aboutNamesRobot);

        aboutValuesRobot = new QWidget(aboutGroupRobot);
        aboutValuesRobot->setObjectName(QStringLiteral("aboutValuesRobot"));
        aboutValuesRobot->setMaximumSize(QSize(16777215, 100));
        verticalLayout_14 = new QVBoxLayout(aboutValuesRobot);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        verticalLayout_14->setContentsMargins(0, 0, 0, 0);
        positionValueRobot = new QLabel(aboutValuesRobot);
        positionValueRobot->setObjectName(QStringLiteral("positionValueRobot"));
        positionValueRobot->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(positionValueRobot);

        speedValueRobot = new QLabel(aboutValuesRobot);
        speedValueRobot->setObjectName(QStringLiteral("speedValueRobot"));
        speedValueRobot->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(speedValueRobot);

        angleValueRobot = new QLabel(aboutValuesRobot);
        angleValueRobot->setObjectName(QStringLiteral("angleValueRobot"));
        angleValueRobot->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(angleValueRobot);


        horizontalLayout_14->addWidget(aboutValuesRobot);


        horizontalLayout_13->addWidget(aboutGroupRobot);

        idRobot = new QLabel(aboutRobot);
        idRobot->setObjectName(QStringLiteral("idRobot"));
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
        RobotWidget->setWindowTitle(QApplication::translate("RobotWidget", "Form", Q_NULLPTR));
        numberRobot->setText(QString());
        settingsLabelRobot->setText(QApplication::translate("RobotWidget", "Settings:", Q_NULLPTR));
        toolsButtonRobot->setText(QApplication::translate("RobotWidget", "...", Q_NULLPTR));
        aboutRobot->setTitle(QApplication::translate("RobotWidget", "About:", Q_NULLPTR));
        positionLabelRobot->setText(QApplication::translate("RobotWidget", "Pos.:", Q_NULLPTR));
        speedLabelRobot->setText(QApplication::translate("RobotWidget", "Spd.:", Q_NULLPTR));
        angleLabelRobot->setText(QApplication::translate("RobotWidget", "Ang.:", Q_NULLPTR));
        positionValueRobot->setText(QApplication::translate("RobotWidget", "-", Q_NULLPTR));
        speedValueRobot->setText(QApplication::translate("RobotWidget", "-", Q_NULLPTR));
        angleValueRobot->setText(QApplication::translate("RobotWidget", "-", Q_NULLPTR));
        idRobot->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class RobotWidget: public Ui_RobotWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROBOTWIDGET_H
