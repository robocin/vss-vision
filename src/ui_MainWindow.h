/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
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
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionClose;
    QAction *actionMenu;
    QWidget *CentralWidget;
    QGridLayout *gridLayout_4;
    QTabWidget *Tabs;
    QWidget *CameraTab;
    QHBoxLayout *horizontalLayout_2;
    QFrame *CameraVisualization;
    QWidget *SimulationTab;
    QHBoxLayout *horizontalLayout_7;
    QFrame *SimulationVisualization;
    QWidget *RobotsTab;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_5;
    QComboBox *comboBox;
    QTabWidget *tabWidget;
    QWidget *Robot1;
    QCheckBox *StaticPlayer1;
    QCheckBox *ShowDebugs1;
    QToolButton *toolButton;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QWidget *Robot2;
    QMenuBar *menubar;
    QMenu *menuFIle;
    QMenu *menuConfigure;
    QMenu *menuView;
    QDockWidget *Settings;
    QWidget *dockWidgetContents;
    QStatusBar *statusbar;
    QDockWidget *Informations;
    QWidget *dockWidgetContents_6;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1098, 688);
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        actionMenu = new QAction(MainWindow);
        actionMenu->setObjectName(QStringLiteral("actionMenu"));
        CentralWidget = new QWidget(MainWindow);
        CentralWidget->setObjectName(QStringLiteral("CentralWidget"));
        CentralWidget->setEnabled(true);
        gridLayout_4 = new QGridLayout(CentralWidget);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        Tabs = new QTabWidget(CentralWidget);
        Tabs->setObjectName(QStringLiteral("Tabs"));
        CameraTab = new QWidget();
        CameraTab->setObjectName(QStringLiteral("CameraTab"));
        horizontalLayout_2 = new QHBoxLayout(CameraTab);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        CameraVisualization = new QFrame(CameraTab);
        CameraVisualization->setObjectName(QStringLiteral("CameraVisualization"));
        CameraVisualization->setEnabled(true);
        CameraVisualization->setMinimumSize(QSize(0, 0));
        CameraVisualization->setMaximumSize(QSize(16777215, 16777215));
        CameraVisualization->setFrameShape(QFrame::StyledPanel);
        CameraVisualization->setFrameShadow(QFrame::Raised);

        horizontalLayout_2->addWidget(CameraVisualization);

        Tabs->addTab(CameraTab, QString());
        SimulationTab = new QWidget();
        SimulationTab->setObjectName(QStringLiteral("SimulationTab"));
        horizontalLayout_7 = new QHBoxLayout(SimulationTab);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        SimulationVisualization = new QFrame(SimulationTab);
        SimulationVisualization->setObjectName(QStringLiteral("SimulationVisualization"));
        SimulationVisualization->setEnabled(true);
        SimulationVisualization->setMinimumSize(QSize(0, 0));
        SimulationVisualization->setMaximumSize(QSize(16777215, 16777215));
        SimulationVisualization->setFrameShape(QFrame::StyledPanel);
        SimulationVisualization->setFrameShadow(QFrame::Raised);

        horizontalLayout_7->addWidget(SimulationVisualization);

        Tabs->addTab(SimulationTab, QString());
        RobotsTab = new QWidget();
        RobotsTab->setObjectName(QStringLiteral("RobotsTab"));
        gridLayout_3 = new QGridLayout(RobotsTab);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        groupBox = new QGroupBox(RobotsTab);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_5 = new QGridLayout(groupBox);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout_5->addWidget(comboBox, 0, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 0, 1, 1, 1);

        tabWidget = new QTabWidget(RobotsTab);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        Robot1 = new QWidget();
        Robot1->setObjectName(QStringLiteral("Robot1"));
        StaticPlayer1 = new QCheckBox(Robot1);
        StaticPlayer1->setObjectName(QStringLiteral("StaticPlayer1"));
        StaticPlayer1->setGeometry(QRect(380, 449, 110, 23));
        ShowDebugs1 = new QCheckBox(Robot1);
        ShowDebugs1->setObjectName(QStringLiteral("ShowDebugs1"));
        ShowDebugs1->setGeometry(QRect(380, 478, 118, 23));
        toolButton = new QToolButton(Robot1);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(380, 9, 26, 24));
        toolButton->setIconSize(QSize(30, 30));
        label = new QLabel(Robot1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(330, 100, 67, 17));
        label_2 = new QLabel(Robot1);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(540, 250, 67, 17));
        label_3 = new QLabel(Robot1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(370, 250, 67, 17));
        label_4 = new QLabel(Robot1);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(520, 170, 67, 17));
        label_5 = new QLabel(Robot1);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(290, 190, 67, 17));
        label_6 = new QLabel(Robot1);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(180, 200, 67, 17));
        tabWidget->addTab(Robot1, QString());
        Robot2 = new QWidget();
        Robot2->setObjectName(QStringLiteral("Robot2"));
        tabWidget->addTab(Robot2, QString());

        gridLayout_3->addWidget(tabWidget, 0, 0, 1, 1);

        Tabs->addTab(RobotsTab, QString());

        gridLayout_4->addWidget(Tabs, 0, 0, 1, 1);

        MainWindow->setCentralWidget(CentralWidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1098, 22));
        menuFIle = new QMenu(menubar);
        menuFIle->setObjectName(QStringLiteral("menuFIle"));
        menuConfigure = new QMenu(menubar);
        menuConfigure->setObjectName(QStringLiteral("menuConfigure"));
        menuView = new QMenu(menubar);
        menuView->setObjectName(QStringLiteral("menuView"));
        MainWindow->setMenuBar(menubar);
        Settings = new QDockWidget(MainWindow);
        Settings->setObjectName(QStringLiteral("Settings"));
        Settings->setFloating(false);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QStringLiteral("dockWidgetContents"));
        Settings->setWidget(dockWidgetContents);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), Settings);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        Informations = new QDockWidget(MainWindow);
        Informations->setObjectName(QStringLiteral("Informations"));
        dockWidgetContents_6 = new QWidget();
        dockWidgetContents_6->setObjectName(QStringLiteral("dockWidgetContents_6"));
        Informations->setWidget(dockWidgetContents_6);
        MainWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(8), Informations);

        menubar->addAction(menuFIle->menuAction());
        menubar->addAction(menuConfigure->menuAction());
        menubar->addAction(menuView->menuAction());
        menuFIle->addSeparator();
        menuFIle->addAction(actionClose);
        menuView->addAction(actionMenu);

        retranslateUi(MainWindow);

        Tabs->setCurrentIndex(2);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionClose->setText(QApplication::translate("MainWindow", "Close", Q_NULLPTR));
        actionMenu->setText(QApplication::translate("MainWindow", "Menu", Q_NULLPTR));
        Tabs->setTabText(Tabs->indexOf(CameraTab), QApplication::translate("MainWindow", "Camera", Q_NULLPTR));
        Tabs->setTabText(Tabs->indexOf(SimulationTab), QApplication::translate("MainWindow", "Simulation", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Decision", Q_NULLPTR));
        StaticPlayer1->setText(QApplication::translate("MainWindow", "Static Player", Q_NULLPTR));
        ShowDebugs1->setText(QApplication::translate("MainWindow", "Show Debugs", Q_NULLPTR));
        toolButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Robot1), QApplication::translate("MainWindow", "Robot 1", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(Robot2), QApplication::translate("MainWindow", "Robot 2", Q_NULLPTR));
        Tabs->setTabText(Tabs->indexOf(RobotsTab), QApplication::translate("MainWindow", "Robots", Q_NULLPTR));
        menuFIle->setTitle(QApplication::translate("MainWindow", "FIle", Q_NULLPTR));
        menuConfigure->setTitle(QApplication::translate("MainWindow", "Configure", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainWindow", "View", Q_NULLPTR));
        Settings->setWindowTitle(QApplication::translate("MainWindow", "Settings", Q_NULLPTR));
        Informations->setWindowTitle(QApplication::translate("MainWindow", "Informations", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
