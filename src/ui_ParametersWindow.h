/********************************************************************************
** Form generated from reading UI file 'ParametersWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETERSWINDOW_H
#define UI_PARAMETERSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParametersWindow
{
public:
    QHBoxLayout *horizontalLayout_5;
    QWidget *widgetLeft;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *behaviorBox;
    QVBoxLayout *verticalLayout_3;
    QComboBox *behaviorComboBox;
    QGroupBox *planningBox;
    QVBoxLayout *verticalLayout_6;
    QComboBox *planningComboBox;
    QGroupBox *navigationBox;
    QVBoxLayout *verticalLayout_5;
    QComboBox *navigationComboBox;
    QPushButton *confirmButton;
    QGroupBox *editParametersWidget;
    QVBoxLayout *verticalLayout_7;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ParametersWindow)
    {
        if (ParametersWindow->objectName().isEmpty())
            ParametersWindow->setObjectName(QString::fromUtf8("ParametersWindow"));
        ParametersWindow->resize(673, 382);
        horizontalLayout_5 = new QHBoxLayout(ParametersWindow);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        widgetLeft = new QWidget(ParametersWindow);
        widgetLeft->setObjectName(QString::fromUtf8("widgetLeft"));
        verticalLayout_2 = new QVBoxLayout(widgetLeft);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        behaviorBox = new QGroupBox(widgetLeft);
        behaviorBox->setObjectName(QString::fromUtf8("behaviorBox"));
        verticalLayout_3 = new QVBoxLayout(behaviorBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        behaviorComboBox = new QComboBox(behaviorBox);
        behaviorComboBox->setObjectName(QString::fromUtf8("behaviorComboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(behaviorComboBox->sizePolicy().hasHeightForWidth());
        behaviorComboBox->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(behaviorComboBox);


        verticalLayout_2->addWidget(behaviorBox);

        planningBox = new QGroupBox(widgetLeft);
        planningBox->setObjectName(QString::fromUtf8("planningBox"));
        verticalLayout_6 = new QVBoxLayout(planningBox);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        planningComboBox = new QComboBox(planningBox);
        planningComboBox->setObjectName(QString::fromUtf8("planningComboBox"));
        sizePolicy.setHeightForWidth(planningComboBox->sizePolicy().hasHeightForWidth());
        planningComboBox->setSizePolicy(sizePolicy);

        verticalLayout_6->addWidget(planningComboBox);


        verticalLayout_2->addWidget(planningBox);

        navigationBox = new QGroupBox(widgetLeft);
        navigationBox->setObjectName(QString::fromUtf8("navigationBox"));
        verticalLayout_5 = new QVBoxLayout(navigationBox);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        navigationComboBox = new QComboBox(navigationBox);
        navigationComboBox->setObjectName(QString::fromUtf8("navigationComboBox"));
        sizePolicy.setHeightForWidth(navigationComboBox->sizePolicy().hasHeightForWidth());
        navigationComboBox->setSizePolicy(sizePolicy);

        verticalLayout_5->addWidget(navigationComboBox);


        verticalLayout_2->addWidget(navigationBox);

        confirmButton = new QPushButton(widgetLeft);
        confirmButton->setObjectName(QString::fromUtf8("confirmButton"));
        confirmButton->setEnabled(false);

        verticalLayout_2->addWidget(confirmButton);


        horizontalLayout_5->addWidget(widgetLeft);

        editParametersWidget = new QGroupBox(ParametersWindow);
        editParametersWidget->setObjectName(QString::fromUtf8("editParametersWidget"));
        verticalLayout_7 = new QVBoxLayout(editParametersWidget);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        scrollArea = new QScrollArea(editParametersWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 298, 287));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_7->addWidget(scrollArea);

        buttonBox = new QDialogButtonBox(editParametersWidget);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Ok|QDialogButtonBox::Open|QDialogButtonBox::Save);

        verticalLayout_7->addWidget(buttonBox);


        horizontalLayout_5->addWidget(editParametersWidget);


        retranslateUi(ParametersWindow);

        QMetaObject::connectSlotsByName(ParametersWindow);
    } // setupUi

    void retranslateUi(QDialog *ParametersWindow)
    {
        ParametersWindow->setWindowTitle(QApplication::translate("ParametersWindow", "Dialog", nullptr));
        behaviorBox->setTitle(QApplication::translate("ParametersWindow", "Behavior:", nullptr));
        planningBox->setTitle(QApplication::translate("ParametersWindow", "Planning:", nullptr));
        navigationBox->setTitle(QApplication::translate("ParametersWindow", "Navigation:", nullptr));
        confirmButton->setText(QApplication::translate("ParametersWindow", "Confirm", nullptr));
        editParametersWidget->setTitle(QApplication::translate("ParametersWindow", "Edit Parameters:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParametersWindow: public Ui_ParametersWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETERSWINDOW_H
