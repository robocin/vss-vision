/********************************************************************************
** Form generated from reading UI file 'MainVSSWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVSSWINDOW_H
#define UI_MAINVSSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
    QLabel *fpsLabel;
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
            MainVSSWindow->setObjectName(QStringLiteral("MainVSSWindow"));
        MainVSSWindow->resize(947, 642);
        actionClose = new QAction(MainVSSWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionMenu = new QAction(MainVSSWindow);
        actionMenu->setObjectName(QStringLiteral("actionMenu"));
        CentralWidget = new QWidget(MainVSSWindow);
        CentralWidget->setObjectName(QStringLiteral("CentralWidget"));
        CentralWidget->setEnabled(true);
        verticalLayout_6 = new QVBoxLayout(CentralWidget);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        tabWidget = new QTabWidget(CentralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        cameraTab = new QWidget();
        cameraTab->setObjectName(QStringLiteral("cameraTab"));
        verticalLayout_2 = new QVBoxLayout(cameraTab);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        cameraFrame = new QFrame(cameraTab);
        cameraFrame->setObjectName(QStringLiteral("cameraFrame"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(cameraFrame->sizePolicy().hasHeightForWidth());
        cameraFrame->setSizePolicy(sizePolicy);
        cameraFrame->setMinimumSize(QSize(0, 0));
        cameraFrame->setMaximumSize(QSize(16777215, 16777215));
        cameraFrame->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        cameraFrame->setFrameShape(QFrame::StyledPanel);
        cameraFrame->setFrameShadow(QFrame::Raised);
        cameraLabel = new QLabel(cameraFrame);
        cameraLabel->setObjectName(QStringLiteral("cameraLabel"));
        cameraLabel->setGeometry(QRect(70, 50, 321, 221));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(4);
        sizePolicy1.setVerticalStretch(3);
        sizePolicy1.setHeightForWidth(cameraLabel->sizePolicy().hasHeightForWidth());
        cameraLabel->setSizePolicy(sizePolicy1);
        cameraLabel->setMinimumSize(QSize(0, 0));
        cameraLabel->setMouseTracking(true);
        cameraLabel->setAutoFillBackground(false);
        cameraLabel->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        cameraLabel->setScaledContents(true);
        cameraLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(cameraFrame);

        cameraWidget = new QWidget(cameraTab);
        cameraWidget->setObjectName(QStringLiteral("cameraWidget"));
        cameraWidget->setMinimumSize(QSize(0, 100));
        horizontalLayout_4 = new QHBoxLayout(cameraWidget);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        viewOptionsGroupBox = new QGroupBox(cameraWidget);
        viewOptionsGroupBox->setObjectName(QStringLiteral("viewOptionsGroupBox"));
        viewOptionsGroupBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        horizontalLayout_5 = new QHBoxLayout(viewOptionsGroupBox);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(222, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        viewOptionsWidget = new QWidget(viewOptionsGroupBox);
        viewOptionsWidget->setObjectName(QStringLiteral("viewOptionsWidget"));
        verticalLayout_5 = new QVBoxLayout(viewOptionsWidget);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        visualizationComboBox = new QComboBox(viewOptionsWidget);
        visualizationComboBox->setObjectName(QStringLiteral("visualizationComboBox"));
        visualizationComboBox->setMinimumSize(QSize(90, 22));
        visualizationComboBox->setLayoutDirection(Qt::RightToLeft);
        visualizationComboBox->setSizeAdjustPolicy(QComboBox::AdjustToMinimumContentsLength);
        visualizationComboBox->setFrame(false);

        verticalLayout_5->addWidget(visualizationComboBox);


        horizontalLayout_5->addWidget(viewOptionsWidget);


        horizontalLayout_4->addWidget(viewOptionsGroupBox);


        verticalLayout_2->addWidget(cameraWidget);

        tabWidget->addTab(cameraTab, QString());
        simulationTab = new QWidget();
        simulationTab->setObjectName(QStringLiteral("simulationTab"));
        gridLayout_3 = new QGridLayout(simulationTab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        simulationFrame = new QFrame(simulationTab);
        simulationFrame->setObjectName(QStringLiteral("simulationFrame"));
        sizePolicy.setHeightForWidth(simulationFrame->sizePolicy().hasHeightForWidth());
        simulationFrame->setSizePolicy(sizePolicy);
        simulationFrame->setMinimumSize(QSize(0, 0));
        simulationFrame->setMaximumSize(QSize(16777215, 16777215));
        simulationFrame->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        simulationFrame->setFrameShape(QFrame::StyledPanel);
        simulationFrame->setFrameShadow(QFrame::Raised);
        simulationLabel = new QLabel(simulationFrame);
        simulationLabel->setObjectName(QStringLiteral("simulationLabel"));
        simulationLabel->setGeometry(QRect(70, 50, 321, 221));
        sizePolicy1.setHeightForWidth(simulationLabel->sizePolicy().hasHeightForWidth());
        simulationLabel->setSizePolicy(sizePolicy1);
        simulationLabel->setMinimumSize(QSize(0, 0));
        simulationLabel->setMouseTracking(true);
        simulationLabel->setAutoFillBackground(false);
        simulationLabel->setStyleSheet(QStringLiteral("background-color: rgb(0, 0, 0);"));
        simulationLabel->setScaledContents(true);
        simulationLabel->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(simulationFrame, 0, 0, 1, 1);

        tabWidget->addTab(simulationTab, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        tabWidget->addTab(tab, QString());

        verticalLayout_6->addWidget(tabWidget);

        MainVSSWindow->setCentralWidget(CentralWidget);
        menubar = new QMenuBar(MainVSSWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 947, 22));
        menuFIle = new QMenu(menubar);
        menuFIle->setObjectName(QStringLiteral("menuFIle"));
        menuConfigure = new QMenu(menubar);
        menuConfigure->setObjectName(QStringLiteral("menuConfigure"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainVSSWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainVSSWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainVSSWindow->setStatusBar(statusbar);
        informationsDockWidget = new QDockWidget(MainVSSWindow);
        informationsDockWidget->setObjectName(QStringLiteral("informationsDockWidget"));
        informationsDockWidget->setAllowedAreas(Qt::BottomDockWidgetArea);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        verticalLayout_4 = new QVBoxLayout(dockWidgetContents);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox = new QGroupBox(dockWidgetContents);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        groupBox->setMinimumSize(QSize(0, 150));
        sourceTab = new QTabWidget(groupBox);
        sourceTab->setObjectName(QStringLiteral("sourceTab"));
        sourceTab->setGeometry(QRect(10, 32, 150, 107));
        sizePolicy.setHeightForWidth(sourceTab->sizePolicy().hasHeightForWidth());
        sourceTab->setSizePolicy(sizePolicy);
        sourceTab->setTabsClosable(false);
        camTab = new QWidget();
        camTab->setObjectName(QStringLiteral("camTab"));
        verticalLayout_8 = new QVBoxLayout(camTab);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        cameraIndexWidget = new QWidget(camTab);
        cameraIndexWidget->setObjectName(QStringLiteral("cameraIndexWidget"));
        horizontalLayout_6 = new QHBoxLayout(cameraIndexWidget);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        cameraIndexLabel = new QLabel(cameraIndexWidget);
        cameraIndexLabel->setObjectName(QStringLiteral("cameraIndexLabel"));
        cameraIndexLabel->setEnabled(true);
        cameraIndexLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_6->addWidget(cameraIndexLabel);

        cameraIndexComboBox = new QComboBox(cameraIndexWidget);
        cameraIndexComboBox->setObjectName(QStringLiteral("cameraIndexComboBox"));
        cameraIndexComboBox->setEnabled(true);
        cameraIndexComboBox->setEditable(false);

        horizontalLayout_6->addWidget(cameraIndexComboBox);


        verticalLayout_8->addWidget(cameraIndexWidget);

        cameraConfigPushButton = new QPushButton(camTab);
        cameraConfigPushButton->setObjectName(QStringLiteral("cameraConfigPushButton"));
        cameraConfigPushButton->setEnabled(true);
        cameraConfigPushButton->setAutoDefault(false);
        cameraConfigPushButton->setFlat(false);

        verticalLayout_8->addWidget(cameraConfigPushButton);

        sourceTab->addTab(camTab, QString());
        videoTab = new QWidget();
        videoTab->setObjectName(QStringLiteral("videoTab"));
        verticalLayout_7 = new QVBoxLayout(videoTab);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        videoFileNameLabel = new QLabel(videoTab);
        videoFileNameLabel->setObjectName(QStringLiteral("videoFileNameLabel"));
        videoFileNameLabel->setEnabled(true);
        videoFileNameLabel->setLayoutDirection(Qt::LeftToRight);
        videoFileNameLabel->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(videoFileNameLabel);

        videoPathBrowsePushButton = new QPushButton(videoTab);
        videoPathBrowsePushButton->setObjectName(QStringLiteral("videoPathBrowsePushButton"));
        videoPathBrowsePushButton->setEnabled(true);

        verticalLayout_7->addWidget(videoPathBrowsePushButton);

        sourceTab->addTab(videoTab, QString());
        mousePositionLabel = new QLabel(groupBox);
        mousePositionLabel->setObjectName(QStringLiteral("mousePositionLabel"));
        mousePositionLabel->setGeometry(QRect(12, 32, 16, 17));
        cameraDistortionWidget = new QWidget(groupBox);
        cameraDistortionWidget->setObjectName(QStringLiteral("cameraDistortionWidget"));
        cameraDistortionWidget->setGeometry(QRect(190, 60, 146, 66));
        verticalLayout_9 = new QVBoxLayout(cameraDistortionWidget);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        CameraDistortion = new QLabel(cameraDistortionWidget);
        CameraDistortion->setObjectName(QStringLiteral("CameraDistortion"));

        verticalLayout_9->addWidget(CameraDistortion);

        DistortionComboBox = new QComboBox(cameraDistortionWidget);
        DistortionComboBox->setObjectName(QStringLiteral("DistortionComboBox"));

        verticalLayout_9->addWidget(DistortionComboBox);

        fieldSizeWidget = new QWidget(groupBox);
        fieldSizeWidget->setObjectName(QStringLiteral("fieldSizeWidget"));
        fieldSizeWidget->setGeometry(QRect(350, 60, 86, 66));
        verticalLayout_10 = new QVBoxLayout(fieldSizeWidget);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        fieldSizeLabel = new QLabel(fieldSizeWidget);
        fieldSizeLabel->setObjectName(QStringLiteral("fieldSizeLabel"));

        verticalLayout_10->addWidget(fieldSizeLabel);

        fieldSizeComboBox = new QComboBox(fieldSizeWidget);
        fieldSizeComboBox->setObjectName(QStringLiteral("fieldSizeComboBox"));

        verticalLayout_10->addWidget(fieldSizeComboBox);

        fpsLabel = new QLabel(groupBox);
        fpsLabel->setObjectName(QStringLiteral("fpsLabel"));
        fpsLabel->setGeometry(QRect(720, 90, 200, 17));

        verticalLayout_4->addWidget(groupBox);

        informationsDockWidget->setWidget(dockWidgetContents);
        MainVSSWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), informationsDockWidget);
        settingsDockWidget = new QDockWidget(MainVSSWindow);
        settingsDockWidget->setObjectName(QStringLiteral("settingsDockWidget"));
        settingsDockWidget->setAllowedAreas(Qt::RightDockWidgetArea);
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QStringLiteral("dockWidgetContents_2"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget_3 = new QWidget(dockWidgetContents_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy2);
        horizontalLayout_3 = new QHBoxLayout(widget_3);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        widget = new QWidget(widget_3);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        widget->setMaximumSize(QSize(350, 16777215));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        numberOfPlayersWidget = new QWidget(widget);
        numberOfPlayersWidget->setObjectName(QStringLiteral("numberOfPlayersWidget"));
        sizePolicy2.setHeightForWidth(numberOfPlayersWidget->sizePolicy().hasHeightForWidth());
        numberOfPlayersWidget->setSizePolicy(sizePolicy2);
        horizontalLayout_2 = new QHBoxLayout(numberOfPlayersWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        numberOfPlayersLabel = new QLabel(numberOfPlayersWidget);
        numberOfPlayersLabel->setObjectName(QStringLiteral("numberOfPlayersLabel"));

        horizontalLayout_2->addWidget(numberOfPlayersLabel);

        numberOfPlayersSpinBox = new QSpinBox(numberOfPlayersWidget);
        numberOfPlayersSpinBox->setObjectName(QStringLiteral("numberOfPlayersSpinBox"));
        numberOfPlayersSpinBox->setMaximumSize(QSize(70, 16777215));
        numberOfPlayersSpinBox->setMinimum(3);
        numberOfPlayersSpinBox->setMaximum(11);
        numberOfPlayersSpinBox->setValue(3);

        horizontalLayout_2->addWidget(numberOfPlayersSpinBox);

        numbetOfPlayersConfirm = new QPushButton(numberOfPlayersWidget);
        numbetOfPlayersConfirm->setObjectName(QStringLiteral("numbetOfPlayersConfirm"));
        numbetOfPlayersConfirm->setEnabled(false);
        numbetOfPlayersConfirm->setMaximumSize(QSize(100, 16777215));
        numbetOfPlayersConfirm->setCheckable(false);

        horizontalLayout_2->addWidget(numbetOfPlayersConfirm);


        verticalLayout->addWidget(numberOfPlayersWidget);

        robotsScrollArea = new QScrollArea(widget);
        robotsScrollArea->setObjectName(QStringLiteral("robotsScrollArea"));
        robotsScrollArea->setMinimumSize(QSize(270, 0));
        robotsScrollArea->setMaximumSize(QSize(16777215, 16777215));
        robotsScrollArea->setAutoFillBackground(true);
        robotsScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 268, 285));
        scrollAreaWidgetContents->setAutoFillBackground(true);
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        robotsScrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(robotsScrollArea);


        horizontalLayout_3->addWidget(widget);

        groupBox_2 = new QGroupBox(widget_3);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        groupBox_2->setMinimumSize(QSize(200, 0));
        groupBox_2->setMaximumSize(QSize(350, 16777215));
        halfPushButton = new QPushButton(groupBox_2);
        halfPushButton->setObjectName(QStringLiteral("halfPushButton"));
        halfPushButton->setGeometry(QRect(71, 257, 50, 40));
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/icon/008-two.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral(":/image/icon/007-one.png"), QSize(), QIcon::Normal, QIcon::On);
        halfPushButton->setIcon(icon);
        halfPushButton->setIconSize(QSize(32, 32));
        halfPushButton->setCheckable(true);
        halfPushButton->setChecked(true);
        communicationPushButton = new QPushButton(groupBox_2);
        communicationPushButton->setObjectName(QStringLiteral("communicationPushButton"));
        communicationPushButton->setEnabled(true);
        communicationPushButton->setGeometry(QRect(11, 208, 50, 40));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/image/icon/020-difussion.png"), QSize(), QIcon::Normal, QIcon::Off);
        communicationPushButton->setIcon(icon1);
        communicationPushButton->setIconSize(QSize(30, 30));
        communicationPushButton->setCheckable(true);
        capturePushButton = new QPushButton(groupBox_2);
        capturePushButton->setObjectName(QStringLiteral("capturePushButton"));
        capturePushButton->setGeometry(QRect(9, 22, 50, 40));
        capturePushButton->setAutoFillBackground(false);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/image/icon/006-video-camera.png"), QSize(), QIcon::Normal, QIcon::Off);
        capturePushButton->setIcon(icon2);
        capturePushButton->setIconSize(QSize(30, 30));
        capturePushButton->setCheckable(true);
        capturePushButton->setChecked(false);
        recordPushButton = new QPushButton(groupBox_2);
        recordPushButton->setObjectName(QStringLiteral("recordPushButton"));
        recordPushButton->setEnabled(true);
        recordPushButton->setGeometry(QRect(133, 22, 50, 40));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/image/icon/001-rec-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        recordPushButton->setIcon(icon3);
        recordPushButton->setIconSize(QSize(30, 30));
        recordPushButton->setCheckable(true);
        strategyInitPushButton = new QPushButton(groupBox_2);
        strategyInitPushButton->setObjectName(QStringLiteral("strategyInitPushButton"));
        strategyInitPushButton->setEnabled(false);
        strategyInitPushButton->setGeometry(QRect(10, 164, 50, 40));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/image/icon/017-strategy.png"), QSize(), QIcon::Normal, QIcon::Off);
        strategyInitPushButton->setIcon(icon4);
        strategyInitPushButton->setIconSize(QSize(30, 30));
        strategyInitPushButton->setCheckable(true);
        visionInitPushButton = new QPushButton(groupBox_2);
        visionInitPushButton->setObjectName(QStringLiteral("visionInitPushButton"));
        visionInitPushButton->setEnabled(false);
        visionInitPushButton->setGeometry(QRect(10, 120, 50, 40));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/image/icon/016-eye.png"), QSize(), QIcon::Normal, QIcon::Off);
        visionInitPushButton->setIcon(icon5);
        visionInitPushButton->setIconSize(QSize(30, 30));
        visionInitPushButton->setCheckable(true);
        visionInitPushButton->setFlat(false);
        maggicSegmentationButton = new QPushButton(groupBox_2);
        maggicSegmentationButton->setObjectName(QStringLiteral("maggicSegmentationButton"));
        maggicSegmentationButton->setEnabled(true);
        maggicSegmentationButton->setGeometry(QRect(130, 120, 50, 40));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/image/icon/030-wand.png"), QSize(), QIcon::Normal, QIcon::Off);
        maggicSegmentationButton->setIcon(icon6);
        maggicSegmentationButton->setIconSize(QSize(30, 30));
        maggicSegmentationButton->setCheckable(true);
        maggicSegmentationButton->setChecked(true);
        maggicSegmentationButton->setFlat(false);
        primaryColor = new QPushButton(groupBox_2);
        primaryColor->setObjectName(QStringLiteral("primaryColor"));
        primaryColor->setGeometry(QRect(11, 257, 50, 40));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/image/icon/013-blueFlag.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon7.addFile(QStringLiteral(":/image/icon/014-yellowFlag.png"), QSize(), QIcon::Normal, QIcon::On);
        icon7.addFile(QStringLiteral(":/image/icon/014-yellowFlag.png"), QSize(), QIcon::Active, QIcon::On);
        icon7.addFile(QStringLiteral(":/image/icon/014-yellowFlag.png"), QSize(), QIcon::Selected, QIcon::On);
        primaryColor->setIcon(icon7);
        primaryColor->setIconSize(QSize(32, 32));
        primaryColor->setCheckable(true);
        primaryColor->setChecked(false);
        primaryColor->setAutoRepeatDelay(0);
        primaryColor->setAutoRepeatInterval(0);
        primaryColor->setFlat(false);
        communicationModeComboBox = new QComboBox(groupBox_2);
        communicationModeComboBox->setObjectName(QStringLiteral("communicationModeComboBox"));
        communicationModeComboBox->setGeometry(QRect(130, 210, 61, 27));
        QFont font;
        font.setPointSize(10);
        communicationModeComboBox->setFont(font);
        calibrateFieldPointspushButton = new QPushButton(groupBox_2);
        calibrateFieldPointspushButton->setObjectName(QStringLiteral("calibrateFieldPointspushButton"));
        calibrateFieldPointspushButton->setEnabled(false);
        calibrateFieldPointspushButton->setGeometry(QRect(71, 70, 50, 40));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/image/icon/003-football-field-in-perspective.png"), QSize(), QIcon::Normal, QIcon::Off);
        calibrateFieldPointspushButton->setIcon(icon8);
        calibrateFieldPointspushButton->setIconSize(QSize(32, 32));
        startAllPushButton = new QPushButton(groupBox_2);
        startAllPushButton->setObjectName(QStringLiteral("startAllPushButton"));
        startAllPushButton->setGeometry(QRect(71, 22, 50, 40));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/image/icon/005-power-button.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon9.addFile(QStringLiteral(":/image/icon/004-pause.png"), QSize(), QIcon::Normal, QIcon::On);
        startAllPushButton->setIcon(icon9);
        startAllPushButton->setIconSize(QSize(30, 30));
        startAllPushButton->setCheckable(true);
        startAllPushButton->setChecked(false);
        visionConfigurePushButton = new QPushButton(groupBox_2);
        visionConfigurePushButton->setObjectName(QStringLiteral("visionConfigurePushButton"));
        visionConfigurePushButton->setEnabled(false);
        visionConfigurePushButton->setGeometry(QRect(71, 120, 50, 40));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/image/icon/012-settings-work-tool.png"), QSize(), QIcon::Normal, QIcon::Off);
        visionConfigurePushButton->setIcon(icon10);
        visionConfigurePushButton->setIconSize(QSize(30, 30));
        visionConfigurePushButton->setFlat(false);
        cutFieldPushButton = new QPushButton(groupBox_2);
        cutFieldPushButton->setObjectName(QStringLiteral("cutFieldPushButton"));
        cutFieldPushButton->setGeometry(QRect(9, 70, 50, 40));
        cutFieldPushButton->setAutoFillBackground(false);
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/image/icon/002-crop-symbol.png"), QSize(), QIcon::Normal, QIcon::Off);
        cutFieldPushButton->setIcon(icon11);
        cutFieldPushButton->setIconSize(QSize(32, 32));
        cutFieldPushButton->setCheckable(true);
        cutFieldPushButton->setChecked(false);
        communicationResetPushButton = new QPushButton(groupBox_2);
        communicationResetPushButton->setObjectName(QStringLiteral("communicationResetPushButton"));
        communicationResetPushButton->setEnabled(true);
        communicationResetPushButton->setGeometry(QRect(71, 208, 50, 40));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/image/icon/009-reset.png"), QSize(), QIcon::Normal, QIcon::Off);
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
        MainVSSWindow->setWindowTitle(QApplication::translate("MainVSSWindow", "MainWindow", Q_NULLPTR));
        actionClose->setText(QApplication::translate("MainVSSWindow", "Close", Q_NULLPTR));
        actionMenu->setText(QApplication::translate("MainVSSWindow", "Menu", Q_NULLPTR));
        cameraLabel->setText(QString());
        viewOptionsGroupBox->setTitle(QApplication::translate("MainVSSWindow", "View Options", Q_NULLPTR));
        visualizationComboBox->clear();
        visualizationComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainVSSWindow", "Original", Q_NULLPTR)
        );
        tabWidget->setTabText(tabWidget->indexOf(cameraTab), QApplication::translate("MainVSSWindow", "Camera", Q_NULLPTR));
        simulationLabel->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(simulationTab), QApplication::translate("MainVSSWindow", "Simulation", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainVSSWindow", "Tab 1", Q_NULLPTR));
        menuFIle->setTitle(QApplication::translate("MainVSSWindow", "FIle", Q_NULLPTR));
        menuConfigure->setTitle(QApplication::translate("MainVSSWindow", "Configure", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainVSSWindow", "View", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainVSSWindow", "Informations:", Q_NULLPTR));
        cameraIndexLabel->setText(QApplication::translate("MainVSSWindow", "Index:", Q_NULLPTR));
        cameraConfigPushButton->setText(QApplication::translate("MainVSSWindow", "Cam Config", Q_NULLPTR));
        sourceTab->setTabText(sourceTab->indexOf(camTab), QApplication::translate("MainVSSWindow", "Camera", Q_NULLPTR));
        videoFileNameLabel->setText(QApplication::translate("MainVSSWindow", "Video file name:", Q_NULLPTR));
        videoPathBrowsePushButton->setText(QApplication::translate("MainVSSWindow", "Browse...", Q_NULLPTR));
        sourceTab->setTabText(sourceTab->indexOf(videoTab), QApplication::translate("MainVSSWindow", "Video", Q_NULLPTR));
        mousePositionLabel->setText(QString());
        CameraDistortion->setText(QApplication::translate("MainVSSWindow", "Camera Distortion:", Q_NULLPTR));
        DistortionComboBox->clear();
        DistortionComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainVSSWindow", "NULL", Q_NULLPTR)
         << QApplication::translate("MainVSSWindow", "ELP-USB", Q_NULLPTR)
        );
        fieldSizeLabel->setText(QApplication::translate("MainVSSWindow", "Field Size:", Q_NULLPTR));
        fieldSizeComboBox->clear();
        fieldSizeComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainVSSWindow", "3x3", Q_NULLPTR)
         << QApplication::translate("MainVSSWindow", "5x5", Q_NULLPTR)
        );
        fpsLabel->setText(QApplication::translate("MainVSSWindow", "60fps", Q_NULLPTR));
        numberOfPlayersLabel->setText(QApplication::translate("MainVSSWindow", "Players:", Q_NULLPTR));
        numbetOfPlayersConfirm->setText(QApplication::translate("MainVSSWindow", "Confirm", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainVSSWindow", "Settings:", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        halfPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>FIrst or second half button</p><p>This button toggles between first and second half of the game.</p><p><br/></p><p>The shortcut for this button is the letter '=' in the keyboard.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        halfPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        halfPushButton->setShortcut(QApplication::translate("MainVSSWindow", "=", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        communicationPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Start Communication Button</p><p>This button starts communication with the robot.</p><p><br/></p><p>The shortcut of this button is the number 5.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        communicationPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        communicationPushButton->setShortcut(QApplication::translate("MainVSSWindow", "5", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        capturePushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Start Capture Button</p><p>When this button is pressed, the application starts to get frames from the video or camera.</p><p>The shortcut of this button is the number 1.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        capturePushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        capturePushButton->setShortcut(QApplication::translate("MainVSSWindow", "1", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        recordPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Set Record Button</p><p>This button starts the record of the video. The popup asking the path and name of the video will appears once you start to record and set the start all button or the start capture button.</p><p>The shortcut of this button is the number 0.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        recordPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        recordPushButton->setShortcut(QApplication::translate("MainVSSWindow", "0", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        strategyInitPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Start Strategy Button</p><p>This button starts the strategy, decision and behavior system.</p><p><br/></p><p>The shortcut of this button is the number 4.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        strategyInitPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        strategyInitPushButton->setShortcut(QApplication::translate("MainVSSWindow", "4", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        visionInitPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Start VIsion Button</p><p>This button starts the computational vision system.</p><p><br/></p><p>The shortcut of this button is the number 3.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        visionInitPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        visionInitPushButton->setShortcut(QApplication::translate("MainVSSWindow", "3", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        maggicSegmentationButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Configure Vision Button</p><p>This button opens the configuration of the automatic segmentation system in a new window.</p><p><br/></p><p>The shortcut of this button is the letter m in the keyboard.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        maggicSegmentationButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        maggicSegmentationButton->setShortcut(QApplication::translate("MainVSSWindow", "M", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        primaryColor->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Primary color button</p><p>This button toggles between the blue color and the yellow color as primary color to your team.</p><p><br/></p><p>The shortcut for this button is key '-' in the keyboard.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        primaryColor->setText(QString());
#ifndef QT_NO_SHORTCUT
        primaryColor->setShortcut(QApplication::translate("MainVSSWindow", "-", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        communicationModeComboBox->clear();
        communicationModeComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainVSSWindow", "NRF 0", Q_NULLPTR)
         << QApplication::translate("MainVSSWindow", "NRF 1", Q_NULLPTR)
         << QApplication::translate("MainVSSWindow", "XBee 0", Q_NULLPTR)
         << QApplication::translate("MainVSSWindow", "XBee 1", Q_NULLPTR)
        );
#ifndef QT_NO_TOOLTIP
        communicationModeComboBox->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Mode</p><p>   This button is used to select the communication mode. For more information read the documentation.</p><p><br/></p><p>The shortcut of this button is the letter r in the keyboard.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        calibrateFieldPointspushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Field Points Calibration Button</p><p>This button opens a new window where you can calibrate the field points to the field crop function beside this button.</p><p><br/></p><p>The shortcut of this button is the letter c in the keyboard.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        calibrateFieldPointspushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        calibrateFieldPointspushButton->setShortcut(QApplication::translate("MainVSSWindow", "F", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        startAllPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Start All Button</p><p>This button Start the capture, start the computational vision system, the strategy system as well as the communication system. Also, this button enables the camera crop in the visualization panel.</p><p>The shortcut of this button is the key ' in the keyboard.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        startAllPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        startAllPushButton->setShortcut(QApplication::translate("MainVSSWindow", "'", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        visionConfigurePushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Configure Vision Button</p><p>   This button opens the configuration of the computational vision system in a new window.</p><p><br/></p><p>The shortcut of this button is the letter v in the keyboard.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        visionConfigurePushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        visionConfigurePushButton->setShortcut(QApplication::translate("MainVSSWindow", "V", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        cutFieldPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Cut Field Button</p><p>This button enables the field crop funtion. You can disable it at any time. The strategy and vision system may not work properly without this option marked. To configure the field crop area see the button beside this one.</p><p><br/></p><p>The shortcut of this button is the number 2.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        cutFieldPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        cutFieldPushButton->setShortcut(QApplication::translate("MainVSSWindow", "2", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
#ifndef QT_NO_TOOLTIP
        communicationResetPushButton->setToolTip(QApplication::translate("MainVSSWindow", "<html><head/><body><p>Reset Communication Button</p><p>This button resets the communication system.<br/></p><p>The shortcut of this button is the letter r in the keyboard.</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        communicationResetPushButton->setText(QString());
#ifndef QT_NO_SHORTCUT
        communicationResetPushButton->setShortcut(QApplication::translate("MainVSSWindow", "R", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
    } // retranslateUi

};

namespace Ui {
    class MainVSSWindow: public Ui_MainVSSWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVSSWINDOW_H
