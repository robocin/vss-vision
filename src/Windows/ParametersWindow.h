#ifndef PARAMETERSWINDOW_H
#define PARAMETERSWINDOW_H

#include <QDialog>
#include <QAbstractButton>
#include "Utils/Types.h"
#include "ParameterOption.h"
#include "../GameInfo/GameInfo.h"

namespace Ui {
class ParametersWindow;
}

class ParametersWindow : public QDialog
{
    Q_OBJECT

    Void setWindow();

public:
    explicit ParametersWindow(const size_t &t_index, QWidget *parent = nullptr);
    ~ParametersWindow();
    Void setIndex(const size_t &t_index);

private slots:

     void on_confirmButton_clicked();

     Vector<Pair<String, Reference<Float>>> allParameters();

     void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::ParametersWindow *m_ui;
    size_t m_index;
    Array<ParameterOption*, MAX_PARAMETERS> m_parameterWidgets;
};

#endif // PARAMETERSWINDOW_H
