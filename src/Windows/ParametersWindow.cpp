#include "ParametersWindow.h"
#include "ui_ParametersWindow.h"

ParametersWindow::ParametersWindow(const size_t &t_index, QWidget *parent)
    : QDialog(parent), m_ui(new Ui::ParametersWindow), m_index(t_index) {
  m_ui->setupUi(this);
  for (auto &widget : m_parameterWidgets) {
    widget = new ParameterOption(m_ui->scrollAreaWidgetContents);
    m_ui->verticalLayout->addWidget(widget);
  }
  for (std::string type : Behaviors::_names()) {
    m_ui->behaviorComboBox->addItem(QString(type.c_str()));
  }
  for (std::string type : Navigations::_names()) {
    m_ui->navigationComboBox->addItem(QString(type.c_str()));
  }
  for (std::string type : Plannings::_names()) {
    m_ui->planningComboBox->addItem(QString(type.c_str()));
  }
  setWindow();
}

Void ParametersWindow::setIndex(const size_t &t_index) { m_index = t_index; }

ParametersWindow::~ParametersWindow() {
  for (auto &widget : m_parameterWidgets) {
    delete widget;
  }
  delete m_ui;
}

Vector<Pair<String, Reference<Float>>> ParametersWindow::allParameters() {
  Vector<Pair<String, Reference<Float>>> parameters;
  Vector<Pair<String, Reference<Float>>> interfaceParameters;
  auto behavior = Behaviors::_from_string_nocase_nothrow(m_ui->behaviorComboBox->currentText().toStdString().c_str());
  if (behavior) {
    switch (*behavior) {
      case Behaviors::ATTACKERIRONCUP2019:
        interfaceParameters =
            AttackerIronCup2019::getInterfaceParameters(vss, m_index);
        std::copy(interfaceParameters.begin(), interfaceParameters.end(),
                  std::back_inserter(parameters));
        break;
      case Behaviors::DEFENDERIRONCUP2019:
        interfaceParameters =
            DefenderIronCup2019::getInterfaceParameters(vss, m_index);
        std::copy(interfaceParameters.begin(), interfaceParameters.end(),
                  std::back_inserter(parameters));
        break;
      case Behaviors::GKINSIDEIRONCUP2019:
        interfaceParameters =
            GkInsideIronCup2019::getInterfaceParameters(vss, m_index);
        std::copy(interfaceParameters.begin(), interfaceParameters.end(),
                  std::back_inserter(parameters));
        break;
      case Behaviors::GKOUTSIDEIRONCUP2019:
        interfaceParameters =
            GkOutsideIronCup2019::getInterfaceParameters(vss, m_index);
        std::copy(interfaceParameters.begin(), interfaceParameters.end(),
                  std::back_inserter(parameters));
        break;
      default:
        //std::cerr << "Meu patrão não tem esse Behavior" << std::endl;
        break;
    }
  }
  auto navigation = Navigations::_from_string_nocase_nothrow(m_ui->navigationComboBox->currentText().toStdString().c_str());
  if (navigation) {
    switch (*navigation) {
      case Navigations::DEFENDER:
        interfaceParameters =
            NavigationDefender::getInterfaceParameters(vss, m_index);
        std::copy(interfaceParameters.begin(), interfaceParameters.end(),
                  std::back_inserter(parameters));
        break;
      case Navigations::GOALIE:
        interfaceParameters =
            NavigationGoalie::getInterfaceParameters(vss, m_index);
        std::copy(interfaceParameters.begin(), interfaceParameters.end(),
                  std::back_inserter(parameters));

        break;
      case Navigations::ATTACKER:
        interfaceParameters =
            NavigationAttacker::getInterfaceParameters(vss, m_index);
        std::copy(interfaceParameters.begin(), interfaceParameters.end(),
                  std::back_inserter(parameters));
        break;
      default:
        //std::cerr << "Não existe esse navigation" << std::endl;
        break;
    }
  }
  auto planning = Plannings::_from_string_nocase_nothrow(m_ui->planningComboBox->currentText().toStdString().c_str());
  if (planning) {
    switch (*planning) {
      case Plannings::BEZIER:
        interfaceParameters = PBezier::getInterfaceParameters(vss, m_index);
        std::copy(interfaceParameters.begin(), interfaceParameters.end(),
                  std::back_inserter(parameters));

        break;
      case Plannings::UNIVECTOR_POSTURE:
        interfaceParameters =
            PUnivectorPosture::getInterfaceParameters(vss, m_index);
        std::copy(interfaceParameters.begin(), interfaceParameters.end(),
                  std::back_inserter(parameters));

        break;
      case Plannings::UNIVECTOR:
        interfaceParameters = PUnivector::getInterfaceParameters(vss, m_index);
        std::copy(interfaceParameters.begin(), interfaceParameters.end(),
                  std::back_inserter(parameters));
        break;
      default:
        //std::cerr << "não tem esse planning" << std::endl;
        break;
    }
  }
  std::sort(parameters.begin(), parameters.end());
  return parameters;
}

Void ParametersWindow::setWindow() {
  for (auto &widget : m_parameterWidgets) {
    widget->hide();
  }
  Vector<Pair<String, Reference<Float>>> parameters(allParameters());
  size_t n = parameters.size();
  for (size_t i = 0; i < n; i++) {
    auto &widget = m_parameterWidgets[i];
    widget->setParameterName(parameters[i].first);
    widget->setParameterValue(parameters[i].second);
    widget->show();
  }
}

void ParametersWindow::on_behaviorComboBox_currentIndexChanged(
    const QString &arg1) {
  m_ui->confirmButton->setEnabled(true);
  setWindow();
}

void ParametersWindow::on_planningComboBox_currentTextChanged(
    const QString &arg1) {
  m_ui->confirmButton->setEnabled(true);
  setWindow();
}

void ParametersWindow::on_navigationComboBox_currentTextChanged(
    const QString &arg1) {
  m_ui->confirmButton->setEnabled(true);
  setWindow();
}

void ParametersWindow::setBehaviourComboBoxIndex(String arg1) {
  m_ui->behaviorComboBox->setCurrentIndex(Behaviors::_from_string(arg1.c_str()));
}

void ParametersWindow::setNavigationComboBoxIndex(String arg1) {
  m_ui->navigationComboBox->setCurrentIndex(Navigations::_from_string(arg1.c_str()));
}

void ParametersWindow::setPlanningComboBoxIndex(String arg1) {
  m_ui->planningComboBox->setCurrentIndex(Plannings::_from_string(arg1.c_str()));
}

void ParametersWindow::on_confirmButton_clicked() {
  auto behavior = Behaviors::_from_string_nocase_nothrow(m_ui->behaviorComboBox->currentText().toStdString().c_str());
  if (behavior) {
    vss.behaviorsTable()[m_index] = *behavior;
  } else {
    vss.behaviorsTable()[m_index] = Behaviors::INVALID;
  }
  auto navigation = Plannings::_from_string_nocase_nothrow(m_ui->planningComboBox->currentText().toStdString().c_str());
  if (navigation) {
    vss.planningsTable()[m_index] = *navigation;
  } else {
    vss.planningsTable()[m_index] = Plannings::INVALID;
  }
  auto planning = Navigations::_from_string_nocase_nothrow(m_ui->navigationComboBox->currentText().toStdString().c_str());
  if (planning) {
    vss.navigationsTable()[m_index] = *planning;
  }
  vss.navigationsTable()[m_index] = Navigations::INVALID;
  m_ui->confirmButton->setEnabled(false);
}

void ParametersWindow::on_buttonBox_clicked(QAbstractButton *button) {
  Vector<Pair<String, Reference<Float>>> parameters(allParameters());
  size_t n = parameters.size();
  if (button == m_ui->buttonBox->button(QDialogButtonBox::Ok)) {
    for (size_t i = 0; i < n; i++) {
      auto &widget = m_parameterWidgets[i];
      Float &parameterValue = parameters[i].second;
      parameterValue = widget->getParameterValue();
    }
    hide();
  } else if (button == m_ui->buttonBox->button(QDialogButtonBox::Save)) {
  } else if (button == m_ui->buttonBox->button(QDialogButtonBox::Open)) {
  }
}
