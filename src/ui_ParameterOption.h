/********************************************************************************
** Form generated from reading UI file 'ParameterOption.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETEROPTION_H
#define UI_PARAMETEROPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ParameterOption
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *parameterWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *parameterName;
    QTextEdit *parameterText;

    void setupUi(QWidget *ParameterOption)
    {
        if (ParameterOption->objectName().isEmpty())
            ParameterOption->setObjectName(QString::fromUtf8("ParameterOption"));
        ParameterOption->resize(300, 30);
        ParameterOption->setMinimumSize(QSize(300, 30));
        verticalLayout = new QVBoxLayout(ParameterOption);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        parameterWidget = new QWidget(ParameterOption);
        parameterWidget->setObjectName(QString::fromUtf8("parameterWidget"));
        parameterWidget->setMaximumSize(QSize(16777215, 50));
        horizontalLayout = new QHBoxLayout(parameterWidget);
        horizontalLayout->setSpacing(5);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        parameterName = new QLabel(parameterWidget);
        parameterName->setObjectName(QString::fromUtf8("parameterName"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(parameterName->sizePolicy().hasHeightForWidth());
        parameterName->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(parameterName);

        parameterText = new QTextEdit(parameterWidget);
        parameterText->setObjectName(QString::fromUtf8("parameterText"));
        parameterText->setMinimumSize(QSize(0, 0));

        horizontalLayout->addWidget(parameterText);


        verticalLayout->addWidget(parameterWidget);


        retranslateUi(ParameterOption);

        QMetaObject::connectSlotsByName(ParameterOption);
    } // setupUi

    void retranslateUi(QWidget *ParameterOption)
    {
        ParameterOption->setWindowTitle(QApplication::translate("ParameterOption", "Form", nullptr));
        parameterName->setText(QApplication::translate("ParameterOption", "Parameter Name:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ParameterOption: public Ui_ParameterOption {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETEROPTION_H
