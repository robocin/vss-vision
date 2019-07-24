#include "ParameterOption.h"
#include "ui_ParameterOption.h"

ParameterOption::ParameterOption(QWidget *parent) :
  QWidget(parent),
  m_ui(new Ui::ParameterOption) {
  m_ui->setupUi(this);
}

Void ParameterOption::setParameterName(const String &t_name) {
  m_ui->parameterName->setText(QString(t_name.c_str()));
}

Void ParameterOption::setParameterValue(const Float &t_value) {
  std::stringstream ss;
  ss << std::fixed << std::setprecision(2) << t_value;
  String value;
  ss >> value;
  m_lastText = QString(value.c_str());
  m_ui->parameterText->setText(m_lastText);
}

Float ParameterOption::getParameterValue() {
  return m_ui->parameterText->toPlainText().toFloat();
}

ParameterOption::~ParameterOption() {
  delete m_ui;
}

void ParameterOption::on_parameterText_textChanged()
{
}
