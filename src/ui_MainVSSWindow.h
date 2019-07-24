/********************************************************************************
** Form generated from reading UI file 'MainVSSWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVSSWINDOW_H
#define UI_MAINVSSWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainVSSWindow
{
public:
    QAction *actionClose;
    QAction *actionMenu;
    QWidget *CentralWidget;
    QVBoxLayout *verticalLayout_6;
    QTabWidget *tabWidget;
    QWidget *cameraTab;
    QVBoxLayout *verticalLayout_2;
    QFrame *cameraFrame;
    QLabel *cameraLabel;
    QWidget *cameraWidget;
    QHBoxLayout *horizontalLayout_4;
    QGroupBox *viewOptionsGroupBox;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QWidget *viewOptionsWidget;
    QVBoxLayout *verticalLayout_5;
    QComboBox *visualizationComboBox;
    QCheckBox *planning;
    QWidget *simulationTab;
    QGridLayout *gridLayout_3;
    QFrame *simulationFrame;
    QLabel *simulationLabel;
    QWidget *tab;
    QMenuBar *menubar;
    QMenu *menuFIle;
    QMenu *menuConfigure;
    QMenu *menuView;
    QStatusBar *statusbar;
    QDockWidget *informationsDockWidget;
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox;
    QTabWidget *sourceTab;
    QWidget *camTab;
    QVBoxLayout *verticalLayout_8;
    QWidget *cameraIndexWidget;
    QHBoxLayout *horizontalLayout_6;
    QLabel *cameraIndexLabel;
    QComboBox *cameraIndexComboBox;
    QPushButton *cameraConfigPushButton;
    QWidget *videoTab;
    QVBoxLayout *verticalLayout_7;
    QLabel *videoFileNameLabel;
    QPushButton *videoPathBrowsePushButton;
    QLabel *mousePositionLabel;
    QWidget *cameraDistortionWidget;
    QVBoxLayout *verticalLayout_9;
    QLabel *CameraDistortion;
    QComboBox *DistortionComboBox;
    QWidget *fieldSizeWidget;
    QVBoxLayout *verticalLayout_10;
    QLabel *fieldSizeLabel;
    QComboBox *fieldSizeComboBox;
    QDockWidget *settingsDockWidget;
    QWidget *dockWidgetContents_2;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QWidget *numberOfPlayersWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *numberOfPlayersLabel;
    QSpinBox *numberOfPlayersSpinBox;
    QPushButton *numbetOfPlayersConfirm;
    QScrollArea *robotsScrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_2;
    QPushButton *halfPushButton;
    QPushButton *communicationPushButton;
    QPushButton *capturePushButton;
    QPushButton *recordPushButton;
    QPushButton *strategyInitPushButton;
    QPushButton *visionInitPushButton;
    QPushButton *maggicSegmentationButton;
    QPushButton *primaryColor;
    QComboBox *communicationModeComboBox;
    QPushButton *calibrateFieldPointspushButton;
    QPushButton *startAllPushButton;
    QPushButton *visionConfigurePushButton;
    QPushButton *cutFieldPushButton;
    QPushButton *communicationResetPushButton;

    void setupUi(QMainWindow *MainVSSWindow)
    {
        if (MainVSSWindow->objectName().isEmpty())
            MainVSSWindow->setObjectName(QString::fromUtf8("MainVSSWindow"));
        MainVSSWindow->resize(947, 642);
        actionClose = new QAction(MainVSSWindow);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionMenu = new QAction(MainVSSWindow);
        actionMenu->setObjectName(QString::fromUtf8("actionMenu"));
        CentralWidget = new QWidget(MainVSSWindow);
        CentralWidget->setObjectName(QString::fromUtf8("CentralWidget"));
        CentralWidget->setEnabled(true);
        verticalLayout_6 = new QVBoxLayout(CentralWidget);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        tabWidget = new QTabWidget(CentralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        cameraTab = new QWidget();
        cameraTab->setObjectName(QString::fromUtf8("cameraTab"));
        verticalLayout_2 = new QVBoxLayout(cameraTab);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        cameraFrame = new QFrame(cameraTab);
        cameraFrame->setObjectName(QString::fromUtf8("cameraFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraFrame->sizePolicy().hasHeightForWidth());
        cameraFrame->setSizePolicy(sizePolicy);
        cameraFrame->setMinimumSize(QSize(0, 0));
        cameraFrame->setMaximumSize(QSize(16777215, 16777215));
        cameraFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        cameraFrame->setFrameShape(QFrame::StyledPanel);
        cameraFrame->setFrameShadow(QFrame::Raised);
        cameraLabel = new QLabel(cameraFrame);
        cameraLabel->setObjectName(QString::fromUtf8("cameraLabel"));
        cameraLabel->setGeometry(QRect(70, 50, 321, 221));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(4);
        sizePolicy1.setVerticalStretch(3);
        sizePolicy1.setHeightForWidth(cameraLabel->sizePolicy().hasHeightForWidth());
        cameraLabel->setSizePolicy(sizePolicy1);
        cameraLabel->setMinimumSize(QSize(0, 0));
        cameraLabel->setMouseTracking(true);
        cameraLabel->setAutoFillBackground(false);
        cameraLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        cameraLabel->setScaledContents(true);
        cameraLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(cameraFrame);

        cameraWidget = new QWidget(cameraTab);
        cameraWidget->setObjectName(QString::fromUtf8("cameraWidget"));
        cameraWidget->setMinimumSize(QSize(0, 100));
        horizontalLayout_4 = new QHBoxLayout(cameraWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        viewOptionsGroupBox = new QGroupBox(cameraWidget);
        viewOptionsGroupBox->setObjectName(QString::fromUtf8("viewOptionsGroupBox"));
        viewOptionsGroupBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        horizontalLayout_5 = new QHBoxLayout(viewOptionsGroupBox);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(222, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        viewOptionsWidget = new QWidget(viewOptionsGroupBox);
        viewOptionsWidget->setObjectName(QString::fromUtf8("viewOptionsWidget"));
        verticalLayout_5 = new QVBoxLayout(viewOptionsWidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        visualizationComboBox = new QComboBox(viewOptionsWidget);
        visualizationComboBox->addItem(QString());
        visualizationComboBox->setObjectName(QString::fromUtf8("visualizationComboBox"));
        visualizationComboBox->setLayoutDirection(Qt::RightToLeft);
        visualizationComboBox->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
        visualizationComboBox->setFrame(false);

        verticalLayout_5->addWidget(visualizationComboBox);

        planning = new QCheckBox(viewOptionsWidget);
        planning->setObjectName(QString::fromUtf8("planning"));
        planning->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_5->addWidget(planning);


        horizontalLayout_5->addWidget(viewOptionsWidget);


        horizontalLayout_4->addWidget(viewOptionsGroupBox);


        verticalLayout_2->addWidget(cameraWidget);

        tabWidget->addTab(cameraTab, QString());
        simulationTab = new QWidget();
        simulationTab->setObjectName(QString::fromUtf8("simulationTab"));
        gridLayout_3 = new QGridLayout(simulationTab);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        simulationFrame = new QFrame(simulationTab);
        simulationFrame->setObjectName(QString::fromUtf8("simulationFrame"));
        sizePolicy.setHeightForWidth(simulationFrame->sizePolicy().hasHeightForWidth());
        simulationFrame->setSizePolicy(sizePolicy);
        simulationFrame->setMinimumSize(QSize(0, 0));
        simulationFrame->setMaximumSize(QSize(16777215, 16777215));
        simulationFrame->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        simulationFrame->setFrameShape(QFrame::StyledPanel);
        simulationFrame->setFrameShadow(QFrame::Raised);
        simulationLabel = new QLabel(simulationFrame);
        simulationLabel->setObjectName(QString::fromUtf8("simulationLabel"));
        simulationLabel->setGeometry(QRect(70, 50, 321, 221));
        sizePolicy1.setHeightForWidth(simulationLabel->sizePolicy().hasHeightForWidth());
        simulationLabel->setSizePolicy(sizePolicy1);
        simulationLabel->setMinimumSize(QSize(0, 0));
        simulationLabel->setMouseTracking(true);
        simulationLabel->setAutoFillBackground(false);
        simulationLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        simulationLabel->setScaledContents(true);
        simulationLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(simulationFrame, 0, 0, 1, 1);

        tabWidget->addTab(simulationTab, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());

        verticalLayout_6->addWidget(tabWidget);

        MainVSSWindow->setCentralWidget(CentralWidget);
        menubar = new QMenuBar(MainVSSWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 947, 22));
        menuFIle = new QMenu(menubar);
        menuFIle->setObjectName(QString::fromUtf8("menuFIle"));
        menuConfigure = new QMenu(menubar);
        menuConfigure->setObjectName(QString::fromUtf8("menuConfigure"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        MainVSSWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainVSSWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainVSSWindow->setStatusBar(statusbar);
        informationsDockWidget = new QDockWidget(MainVSSWindow);
        informationsDockWidget->setObjectName(QString::fromUtf8("informationsDockWidget"));
        informationsDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(0, 150));
        sourceTab = new QTabWidget(groupBox);
        sourceTab->setObjectName(QString::fromUtf8("sourceTab"));
        sourceTab->setGeometry(QRect(10, 32, 150, 107));
        sizePolicy.setHeightForWidth(sourceTab->sizePolicy().hasHeightForWidth());
        sourceTab->setSizePolicy(sizePolicy);
        sourceTab->setTabsClosable(false);
        camTab = new QWidget();
        camTab->setObjectName(QString::fromUtf8("camTab"));
        verticalLayout_8 = new QVBoxLayout(camTab);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        cameraIndexWidget = new QWidget(camTab);
        cameraIndexWidget->setObjectName(QString::fromUtf8("cameraIndexWidget"));
        horizontalLayout_6 = new QHBoxLayout(cameraIndexWidget);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        cameraIndexLabel = new QLabel(cameraIndexWidget);
        cameraIndexLabel->setObjectName(QString::fromUtf8("cameraIndexLabel"));
        cameraIndexLabel->setEnabled(true);
        cameraIndexLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(cameraIndexLabel);

        cameraIndexComboBox = new QComboBox(cameraIndexWidget);
        cameraIndexComboBox->setObjectName(QString::fromUtf8("cameraIndexComboBox"));
        cameraIndexComboBox->setEnabled(true);
        cameraIndexComboBox->setEditable(false);

        horizontalLayout_6->addWidget(cameraIndexComboBox);


        verticalLayout_8->addWidget(cameraIndexWidget);

        cameraConfigPushButton = new QPushButton(camTab);
        cameraConfigPushButton->setObjectName(QString::fromUtf8("cameraConfigPushButton"));
        cameraConfigPushButton->setEnabled(true);
        cameraConfigPushButton->setAutoDefault(false);
        cameraConfigPushButton->setFlat(false);

        verticalLayout_8->addWidget(cameraConfigPushButton);

        sourceTab->addTab(camTab, QString());
        videoTab = new QWidget();
        videoTab->setObjectName(QString::fromUtf8("videoTab"));
        verticalLayout_7 = new QVBoxLayout(videoTab);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        videoFileNameLabel = new QLabel(videoTab);
        videoFileNameLabel->setObjectName(QString::fromUtf8("videoFileNameLabel"));
        videoFileNameLabel->setEnabled(true);
        videoFileNameLabel->setLayoutDirection(Qt::LeftToRight);
        videoFileNameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(videoFileNameLabel);

        videoPathBrowsePushButton = new QPushButton(videoTab);
        videoPathBrowsePushButton->setObjectName(QString::fromUtf8("videoPathBrowsePushButton"));
        videoPathBrowsePushButton->setEnabled(true);

        verticalLayout_7->addWidget(videoPathBrowsePushButton);

        sourceTab->addTab(videoTab, QString());
        mousePositionLabel = new QLabel(groupBox);
        mousePositionLabel->setObjectName(QString::fromUtf8("mousePositionLabel"));
        mousePositionLabel->setGeometry(QRect(12, 32, 16, 17));
        cameraDistortionWidget = new QWidget(groupBox);
        cameraDistortionWidget->setObjectName(QString::fromUtf8("cameraDistortionWidget"));
        cameraDistortionWidget->setGeometry(QRect(190, 60, 146, 66));
        verticalLayout_9 = new QVBoxLayout(cameraDistortionWidget);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        CameraDistortion = new QLabel(cameraDistortionWidget);
        CameraDistortion->setObjectName(QString::fromUtf8("CameraDistortion"));

        verticalLayout_9->addWidget(CameraDistortion);

        DistortionComboBox = new QComboBox(cameraDistortionWidget);
        DistortionComboBox->addItem(QString());
        DistortionComboBox->addItem(QString());
        DistortionComboBox->setObjectName(QString::fromUtf8("DistortionComboBox"));

        verticalLayout_9->addWidget(DistortionComboBox);

        fieldSizeWidget = new QWidget(groupBox);
        fieldSizeWidget->setObjectName(QString::fromUtf8("fieldSizeWidget"));
        fieldSizeWidget->setGeometry(QRect(350, 60, 86, 66));
        verticalLayout_10 = new QVBoxLayout(fieldSizeWidget);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        fieldSizeLabel = new QLabel(fieldSizeWidget);
        fieldSizeLabel->setObjectName(QString::fromUtf8("fieldSizeLabel"));

        verticalLayout_10->addWidget(fieldSizeLabel);

        fieldSizeComboBox = new QComboBox(fieldSizeWidget);
        fieldSizeComboBox->addItem(QString());
        fieldSizeComboBox->addItem(QString());
        fieldSizeComboBox->setObjectName(QString::fromUtf8("fieldSizeComboBox"));

        verticalLayout_10->addWidget(fieldSizeComboBox);


        verticalLayout_4->addWidget(groupBox);

        informationsDockWidget->setWidget(dockWidgetContents);
        MainVSSWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), informationsDockWidget);
        settingsDockWidget = new QDockWidget(MainVSSWindow);
        settingsDockWidget->setObjectName(QString::fromUtf8("settingsDockWidget"));
        settingsDockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget_3 = new QWidget(dockWidgetContents_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy2);
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        widget = new QWidget(widget_3);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        widget->setMaximumSize(QSize(350, 16777215));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        numberOfPlayersWidget = new QWidget(widget);
        numberOfPlayersWidget->setObjectName(QString::fromUtf8("numberOfPlayersWidget"));
        sizePolicy2.setHeightForWidth(numberOfPlayersWidget->sizePolicy().hasHeightForWidth());
        numberOfPlayersWidget->setSizePolicy(sizePolicy2);
        horizontalLayout_2 = new QHBoxLayout(numberOfPlayersWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        numberOfPlayersLabel = new QLabel(numberOfPlayersWidget);
        numberOfPlayersLabel->setObjectName(QString::fromUtf8("numberOfPlayersLabel"));

        horizontalLayout_2->addWidget(numberOfPlayersLabel);

        numberOfPlayersSpinBox = new QSpinBox(numberOfPlayersWidget);
        numberOfPlayersSpinBox->setObjectName(QString::fromUtf8("numberOfPlayersSpinBox"));
        numberOfPlayersSpinBox->setMaximumSize(QSize(70, 16777215));
        numberOfPlayersSpinBox->setMinimum(3);
        numberOfPlayersSpinBox->setMaximum(11);
        numberOfPlayersSpinBox->setValue(3);

        horizontalLayout_2->addWidget(numberOfPlayersSpinBox);

        numbetOfPlayersConfirm = new QPushButton(numberOfPlayersWidget);
        numbetOfPlayersConfirm->setObjectName(QString::fromUtf8("numbetOfPlayersConfirm"));
        numbetOfPlayersConfirm->setEnabled(false);
        numbetOfPlayersConfirm->setMaximumSize(QSize(100, 16777215));
        numbetOfPlayersConfirm->setCheckable(false);

        horizontalLayout_2->addWidget(numbetOfPlayersConfirm);


        verticalLayout->addWidget(numberOfPlayersWidget);

        robotsScrollArea = new QScrollArea(widget);
        robotsScrollArea->setObjectName(QString::fromUtf8("robotsScrollArea"));
        robotsScrollArea->setMinimumSize(QSize(270, 0));
        robotsScrollArea->setMaximumSize(QSize(16777215, 16777215));
        robotsScrollArea->setAutoFillBackground(true);
        robotsScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 268, 284));
        scrollAreaWidgetContents->setAutoFillBackground(true);
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        robotsScrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(robotsScrollArea);


        horizontalLayout_3->addWidget(widget);

        groupBox_2 = new QGroupBox(widget_3);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        groupBox_2->setMinimumSize(QSize(200, 0));
        groupBox_2->setMaximumSize(QSize(350, 16777215));
        halfPushButton = new QPushButton(groupBox_2);
        halfPushButton->setObjectName(QString::fromUtf8("halfPushButton"));
        halfPushButton->setGeometry(QRect(71, 257, 50, 40));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/image/icon/008-two.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QString::fromUtf8(":/image/icon/007-one.png"), QSize(), QIcon::Normal, QIcon::On);
        halfPushButton->setIcon(icon);
        halfPushButton->setIconSize(QSize(32, 32));
        halfPushButton->setCheckable(true);
        halfPushButton->setChecked(true);
        communicationPushButton = new QPushButton(groupBox_2);
        communicationPushButton->setObjectName(QString::fromUtf8("communicationPushButton"));
        communicationPushButton->setEnabled(true);
        communicationPushButton->setGeometry(QRect(11, 208, 50, 40));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/image/icon/020-difussion.png"), QSize(), QIcon::Normal, QIcon::Off);
        communicationPushButton->setIcon(icon1);
        communicationPushButton->setIconSize(QSize(30, 30));
        communicationPushButton->setCheckable(true);
        capturePushButton = new QPushButton(groupBox_2);
        capturePushButton->setObjectName(QString::fromUtf8("capturePushButton"));
        capturePushButton->setGeometry(QRect(9, 22, 50, 40));
        capturePushButton->setAutoFillBackground(false);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/image/icon/006-video-camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        capturePushButton->setIcon(icon2);
        capturePushButton->setIconSize(QSize(30, 30));
        capturePushButton->setCheckable(true);
        capturePushButton->setChecked(false);
        recordPushButton = new QPushButton(groupBox_2);
        recordPushButton->setObjectName(QString::fromUtf8("recordPushButton"));
        recordPushButton->setEnabled(true);
        recordPushButton->setGeometry(QRect(133, 22, 50, 40));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/image/icon/001-rec-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        recordPushButton->setIcon(icon3);
        recordPushButton->setIconSize(QSize(30, 30));
        recordPushButton->setCheckable(true);
        strategyInitPushButton = new QPushButton(groupBox_2);
        strategyInitPushButton->setObjectName(QString::fromUtf8("strategyInitPushButton"));
        strategyInitPushButton->setEnabled(false);
        strategyInitPushButton->setGeometry(QRect(10, 164, 50, 40));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/image/icon/017-strategy.png"), QSize(), QIcon::Normal, QIcon::Off);
        strategyInitPushButton->setIcon(icon4);
        strategyInitPushButton->setIconSize(QSize(30, 30));
        strategyInitPushButton->setCheckable(true);
        visionInitPushButton = new QPushButton(groupBox_2);
        visionInitPushButton->setObjectName(QString::fromUtf8("visionInitPushButton"));
        visionInitPushButton->setEnabled(false);
        visionInitPushButton->setGeometry(QRect(10, 120, 50, 40));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/image/icon/016-eye.png"), QSize(), QIcon::Normal, QIcon::Off);
        visionInitPushButton->setIcon(icon5);
        visionInitPushButton->setIconSize(QSize(30, 30));
        visionInitPushButton->setCheckable(true);
        visionInitPushButton->setFlat(false);
        maggicSegmentationButton = new QPushButton(groupBox_2);
        maggicSegmentationButton->setObjectName(QString::fromUtf8("maggicSegmentationButton"));
        maggicSegmentationButton->setEnabled(true);
        maggicSegmentationButton->setGeometry(QRect(130, 120, 50, 40));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/image/icon/030-wand.png"), QSize(), QIcon::Normal, QIcon::Off);
        maggicSegmentationButton->setIcon(icon6);
        maggicSegmentationButton->setIconSize(QSize(30, 30));
        maggicSegmentationButton->setCheckable(true);
        maggicSegmentationButton->setChecked(true);
        maggicSegmentationButton->setFlat(false);
        primaryColor = new QPushButton(groupBox_2);
        primaryColor->setObjectName(QString::fromUtf8("primaryColor"));
        primaryColor->setGeometry(QRect(11, 257, 50, 40));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/image/icon/013-blueFlag.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QString::fromUtf8(":/image/icon/014-yellowFlag.png"), QSize(), QIcon::Normal, QIcon::On);
        icon7.addFile(QString::fromUtf8(":/image/icon/014-yellowFlag.png"), QSize(), QIcon::Active, QIcon::On);
        icon7.addFile(QString::fromUtf8(":/image/icon/014-yellowFlag.png"), QSize(), QIcon::Selected, QIcon::On);
        primaryColor->setIcon(icon7);
        primaryColor->setIconSize(QSize(32, 32));
        primaryColor->setCheckable(true);
        primaryColor->setChecked(false);
        primaryColor->setAutoRepeatDelay(0);
        primaryColor->setAutoRepeatInterval(0);
        primaryColor->setFlat(false);
        communicationModeComboBox = new QComboBox(groupBox_2);
        communicationModeComboBox->addItem(QString());
        communicationModeComboBox->addItem(QString());
        communicationModeComboBox->addItem(QString());
        communicationModeComboBox->addItem(QString());
        communicationModeComboBox->setObjectName(QString::fromUtf8("communicationModeComboBox"));
        communicationModeComboBox->setGeometry(QRect(130, 210, 61, 27));
        QFont font;
        font.setPointSize(10);
        communicationModeComboBox->setFont(font);
        calibrateFieldPointspushButton = new QPushButton(groupBox_2);
        calibrateFieldPointspushButton->setObjectName(QString::fromUtf8("calibrateFieldPointspushButton"));
        calibrateFieldPointspushButton->setEnabled(false);
        calibrateFieldPointspushButton->setGeometry(QRect(71, 70, 50, 40));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/image/icon/003-football-field-in-perspective.png"), QSize(), QIcon::Normal, QIcon::Off);
        calibrateFieldPointspushButton->setIcon(icon8);
        calibrateFieldPointspushButton->setIconSize(QSize(32, 32));
        startAllPushButton = new QPushButton(groupBox_2);
        startAllPushButton->setObjectName(QString::fromUtf8("startAllPushButton"));
        startAllPushButton->setGeometry(QRect(71, 22, 50, 40));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/image/icon/005-power-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon9.addFile(QString::fromUtf8(":/image/icon/004-pause.png"), QSize(), QIcon::Normal, QIcon::On);
        startAllPushButton->setIcon(icon9);
        startAllPushButton->setIconSize(QSize(30, 30));
        startAllPushButton->setCheckable(true);
        startAllPushButton->setChecked(false);
        visionConfigurePushButton = new QPushButton(groupBox_2);
        visionConfigurePushButton->setObjectName(QString::fromUtf8("visionConfigurePushButton"));
        visionConfigurePushButton->setEnabled(false);
        visionConfigurePushButton->setGeometry(QRect(71, 120, 50, 40));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/image/icon/012-settings-work-tool.png"), QSize(), QIcon::Normal, QIcon::Off);
        visionConfigurePushButton->setIcon(icon10);
        visionConfigurePushButton->setIconSize(QSize(30, 30));
        visionConfigurePushButton->setFlat(false);
        cutFieldPushButton = new QPushButton(groupBox_2);
        cutFieldPushButton->setObjectName(QString::fromUtf8("cutFieldPushButton"));
        cutFieldPushButton->setGeometry(QRect(9, 70, 50, 40));
        cutFieldPushButton->setAutoFillBackground(false);
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/image/icon/002-crop-symbol.png"), QSize(), QIcon::Normal, QIcon::Off);
        cutFieldPushButton->setIcon(icon11);
        cutFieldPushButton->setIconSize(QSize(32, 32));
        cutFieldPushButton->setCheckable(true);
        cutFieldPushButton->setChecked(false);
        communicationResetPushButton = new QPushButton(groupBox_2);
        communicationResetPushButton->setObjectName(QString::fromUtf8("communicationResetPushButton"));
        communicationResetPushButton->setEnabled(true);
        communicationResetPushButton->setGeometry(QRect(71, 208, 50, 40));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8(":/image/icon/009-reset.png"), QSize(), QIcon::Normal, QIcon::Off);
        communicationResetPushButton->setIcon(icon12);
        communicationResetPushButton->setIconSize(QSize(30, 30));

        horizontalLayout_3->addWidget(groupBox_2);


        horizontalLayout->addWidget(widget_3);

        settingsDockWidget->setWidget(dockWidgetContents_2);
        MainVSSWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), settingsDockWidget);

        menubar->addAction(menuFIle->menuAction());
        menubar->addAction(menuConfigure->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFIle->addSeparator();
        menuFIle->addAction(actionClose);
        menuView->addAction(actionMenu);

        retranslateUi(MainVSSWindow);

        tabWidget->setCurrentIndex(0);
        sourceTab->setCurrentIndex(0);
        cameraConfigPushButton->setDefault(false);
        primaryColor->setDefault(false);


        QMetaObject::connectSlotsByName(MainVSSWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainVSSWindow)
    {
        MainVSSWindow->setWindowTitle(QApplication::translate("MainVSSWindow", "MainWindow", nullptr));
        actionClose->setText(QApplication::translate("MainVSSWindow", "Close", nullptr));
        actionMenu->setText(QApplication::translate("MainVSSWindow", "Menu", nullptr));
        cameraLabel->setText(QString());
        viewOptionsGroupBox->setTitle(QApplication::translate("MainVSSWindow", "View Options", nullptr));
        visualizationComboBox->setItemText(0, QApplication::translate("MainVSSWindow", "Original", nullptr));

        planning->setText(QApplication::translate("MainVSSWindow", "Planning", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(cameraTab), QApplication::translate("MainVSSWindow", "Camera", nullptr));
        simulationLabel->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(simulationTab), QApplication::translate("MainVSSWindow", "Simulation", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainVSSWindow", "Tab 1", nullptr));
        menuFIle->setTitle(QApplication::translate("MainVSSWindow", "FIle", nullptr));
        menuConfigure->setTitle(QApplication::translate("MainVSSWindow", "Configure", nullptr));
        menuView->setTitle(QApplication::translate("MainVSSWindow", "View", nullptr));
        groupBox->setTitle(QApplication::translate("MainVSSWindow", "Informations:", nullptr));
        cameraIndexLabel->setText(QApplication::translate("MainVSSWindow", "Index:", nullptr));
        cameraConfigPushButton->setText(QApplication::translate("MainVSSWindow", "Cam Config", nullptr));
        sourceTab->setTabText(sourceTab->indexOf(camTab), QApplication::translate("MainVSSWindow", "Camera", nullptr));
        videoFileNameLabel->setText(QApplication::translate("MainVSSWindow", "Video file name:", nullptr));
        videoPathBrowsePushButton->setText(QApplication::translate("MainVSSWindow", "Browse...", nullptr));
        sourceTab->setTabText(sourceTab->indexOf(videoTab), QApplication::translate("MainVSSWindow", "Video", nullptr));
        mousePositionLabel->setText(QString());
        CameraDistortion->setText(QApplication::translate("MainVSSWindow", "Camera Distortion:", nullptr));
        DistortionComboBox->setItemText(0, QApplication::translate("MainVSSWindow", "NULL", nullptr));
        DistortionComboBox->setItemText(1, QApplication::translate("MainVSSWindow", "ELP-USB", nullptr));

        fieldSizeLabel->setText(QApplication::translate("MainVSSWindow", "Field Size:", nullptr));
        fieldSizeComboBox->setItemText(0, QApplication::translate("MainVSSWindow", "3x3", nullptr));
        fieldSizeComboBox->setItemText(1, QApplication::translate("MainVSSWindow", "5x5", nullptr));

        numberOfPlayersLabel->setText(QApplication::translate("MainVSSWindow", "Players:", nullptr));
        numbetOfPlayersConfirm->setText(QApplication::translate("MainVSSWindow", "Confirm", nullptr));
        groupBox_2->setTitle(QApplication::translate("MainVSSWindow", "Settings:", nullptr));
#ifndef QT_NO_TOOLTIP
        halfPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>FIrst or second half button</p><p>This button toggles between first and second half of the game.</p><p><br/></p><p>The shortcut for this button is the letter '=' in the keyboard.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        halfPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        halfPushButton->setShortcut(QApplication::translate("MainVSSWindow", "=", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        communicationPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Start Communication Button</p><p>This button starts communication with the robot.</p><p><br/></p><p>The shortcut of this button is the number 5.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        communicationPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        communicationPushButton->setShortcut(QApplication::translate("MainVSSWindow", "5", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        capturePushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Start Capture Button</p><p>When this button is pressed, the application starts to get frames from the video or camera.</p><p>The shortcut of this button is the number 1.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        capturePushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        capturePushButton->setShortcut(QApplication::translate("MainVSSWindow", "1", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        recordPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Set Record Button</p><p>This button starts the record of the video. The popup asking the path and name of the video will appears once you start to record and set the start all button or the start capture button.</p><p>The shortcut of this button is the number 0.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        recordPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        recordPushButton->setShortcut(QApplication::translate("MainVSSWindow", "0", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        strategyInitPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Start Strategy Button</p><p>This button starts the strategy, decision and behavior system.</p><p><br/></p><p>The shortcut of this button is the number 4.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        strategyInitPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        strategyInitPushButton->setShortcut(QApplication::translate("MainVSSWindow", "4", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        visionInitPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Start VIsion Button</p><p>This button starts the computational vision system.</p><p><br/></p><p>The shortcut of this button is the number 3.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        visionInitPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        visionInitPushButton->setShortcut(QApplication::translate("MainVSSWindow", "3", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        maggicSegmentationButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Configure Vision Button</p><p>This button opens the configuration of the automatic segmentation system in a new window.</p><p><br/></p><p>The shortcut of this button is the letter m in the keyboard.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        maggicSegmentationButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        maggicSegmentationButton->setShortcut(QApplication::translate("MainVSSWindow", "M", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        primaryColor->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Primary color button</p><p>This button toggles between the blue color and the yellow color as primary color to your team.</p><p><br/></p><p>The shortcut for this button is key '-' in the keyboard.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        primaryColor->setText(QString());
#ifndef QT_NO_SHORTCUT
        primaryColor->setShortcut(QApplication::translate("MainVSSWindow", "-", nullptr));
#endif // QT_NO_SHORTCUT
        communicationModeComboBox->setItemText(0, QApplication::translate("MainVSSWindow", "NRF 0", nullptr));
        communicationModeComboBox->setItemText(1, QApplication::translate("MainVSSWindow", "NRF 1", nullptr));
        communicationModeComboBox->setItemText(2, QApplication::translate("MainVSSWindow", "XBee 0", nullptr));
        communicationModeComboBox->setItemText(3, QApplication::translate("MainVSSWindow", "XBee 1", nullptr));

#ifndef QT_NO_TOOLTIP
        communicationModeComboBox->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Mode</p><p>   This button is used to select the communication mode. For more information read the documentation.</p><p><br/></p><p>The shortcut of this button is the letter r in the keyboard.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        calibrateFieldPointspushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Field Points Calibration Button</p><p>This button opens a new window where you can calibrate the field points to the field crop function beside this button.</p><p><br/></p><p>The shortcut of this button is the letter c in the keyboard.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        calibrateFieldPointspushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        calibrateFieldPointspushButton->setShortcut(QApplication::translate("MainVSSWindow", "F", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        startAllPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Start All Button</p><p>This button Start the capture, start the computational vision system, the strategy system as well as the communication system. Also, this button enables the camera crop in the visualization panel.</p><p>The shortcut of this button is the key ' in the keyboard.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        startAllPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        startAllPushButton->setShortcut(QApplication::translate("MainVSSWindow", "'", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        visionConfigurePushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Configure Vision Button</p><p>   This button opens the configuration of the computational vision system in a new window.</p><p><br/></p><p>The shortcut of this button is the letter v in the keyboard.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        visionConfigurePushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        visionConfigurePushButton->setShortcut(QApplication::translate("MainVSSWindow", "V", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        cutFieldPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Cut Field Button</p><p>This button enables the field crop funtion. You can disable it at any time. The strategy and vision system may not work properly without this option marked. To configure the field crop area see the button beside this one.</p><p><br/></p><p>The shortcut of this button is the number 2.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        cutFieldPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        cutFieldPushButton->setShortcut(QApplication::translate("MainVSSWindow", "2", nullptr));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        communicationResetPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Reset Communication Button</p><p>This button resets the communication system.<br/></p><p>The shortcut of this button is the letter r in the keyboard.</p></body></html>", nullptr));
#endif // QT_NO_TOOLTIP
        communicationResetPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        communicationResetPushButton->setShortcut(QApplication::translate("MainVSSWindow", "R", nullptr));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class MainVSSWindow: public Ui_MainVSSWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVSSWINDOW_H
