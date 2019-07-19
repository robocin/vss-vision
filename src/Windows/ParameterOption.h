#ifndef PARAMETEROPTION_H
#define PARAMETEROPTION_H

#include "../Utils/Utils.h"
#include <QWidget>

namespace Ui {
  class ParameterOption;
}

class ParameterOption : public QWidget
{
  Q_OBJECT

public:
  explicit ParameterOption(QWidget *parent = nullptr);
  ~ParameterOption();
  Void setParameterName(const String &t_name);
  Void setParameterValue(const Float &t_value);
  Float getParameterValue();

private slots:
  void on_parameterText_textChanged();

private:
  Ui::ParameterOption *m_ui;
  QString m_lastText;
};

#endif // PARAMETEROPTION_H
