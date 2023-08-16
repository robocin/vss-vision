#include "RobotWidget.h"
#include <iostream>
#include "ui_RobotWidget.h"
#include "Vision/Vision.h"

RobotWidget::RobotWidget(const size_t &t_index, QWidget *parent)
  : QWidget(parent),
    m_ui(new Ui::RobotWidget),
    m_index(t_index),
    m_borderImage(":/image/icon/border.png"),
    m_numbersImage(":/image/icon/numbers.png") {
  m_ui->setupUi(this);
  QRect region(static_cast<int>(t_index) * 50, 0, 50, 50);
  m_ui->numberRobot->setPixmap(m_numbersImage.copy(region));
  m_ui->idRobot->setPixmap(m_borderImage);
  // Iniciar com o arquivo salvo nessa posicao
  // setar cores inicias
  // dizer qual o numero certo do robo
  // atualizar posicao, velocidade e aceleracao
}

RobotWidget::~RobotWidget() {
  delete m_ui;
}

QPixmap RobotWidget::getRobotId() {
  QPixmap colorArea(200, 200);
  setPrimaryColor(colorArea);
  setSecondaryColor(colorArea);
  setSecondSecondary(colorArea);
  QPainter paint(&colorArea);
  paint.drawPixmap(0, 0, m_borderImage);
  paint.end();
  return colorArea;
}

void RobotWidget::setPrimaryColor(QPixmap &t_robotId) {
  QPainter paint(&t_robotId);
  int teamColor = Vision::singleton().getTeamColor();
  if (teamColor == Color::BLUE) {
    paint.setBrush(QBrush(Qt::blue));
  } else if (teamColor == Color::YELLOW) {
    paint.setBrush(QBrush(Qt::yellow));
  } else paint.setBrush(QBrush(Qt::black));
  paint.drawRect(0, 0, 200, 100);
}

void RobotWidget::setSecondaryColor(QPixmap &t_robotId) {
  QPainter paint(&t_robotId);

  // AJUSTAR
  QColor color(Qt::black);
  QVector<QString> names;
  int t_id = this->m_robotId%100 + 1;
  // printf("ID 1: %d\n", t_id);

  for (const char *str : Color::_names()) {
    if (t_id == Color::_from_string(str)) {
      QString correctColor(str);
      if (QColor::isValidColor(correctColor)) {
        color = QColor(correctColor);
      }
    }
  }

  paint.setBrush(QBrush(color));
  paint.drawRect(0, 100, 200, 100);
}

void RobotWidget::setSecondSecondary(QPixmap &t_robotId) {
  QPainter paint(&t_robotId);

  // AJUSTAR
  QColor color(Qt::black);
  QVector<QString> names;
  int t_id = this->m_robotId%100 + (Color::PINK - Color::RED);
  // printf("ID 2: %d\n", t_id);

  for (const char *str : Color::_names()) {
    if (t_id == Color::_from_string(str)) {
      QString correctColor(str);
      if (QColor::isValidColor(correctColor)) {
        color = QColor(correctColor);
      }
    }
  }

  paint.setBrush(QBrush(color));
  paint.drawRect(100, 100, 100, 100);
}

void RobotWidget::update() {
  int offset_x = static_cast<int>(m_index) * 50;
  int offset_y = 0;
  int teamColor = Vision::singleton().getTeamColor();
  
  Players players = vss.players(
              static_cast<uint>(teamColor)
              );
  if (m_index < players.size()) {
    Ally &ally = players[m_index];
    this->m_robotId = ally.id();
    m_ui->idRobot->setPixmap(getRobotId());
    std::stringstream ss;
    std::string str;
    QString value;
    ss << std::fixed << std::setprecision(2) << ally.position();
    getline(ss, str);
    ss.clear();
    value = str.c_str();
    m_ui->positionValueRobot->setText(value);
    //ss << std::fixed << std::setprecision(2) << ally.speed();
    getline(ss, str);
    ss.clear();
    value = str.c_str();
    m_ui->speedValueRobot->setText(value);
    ss << std::fixed << std::setprecision(2) << Geometry::radiansToDegrees(ally.angle());
    getline(ss, str);
    value = str.c_str();
    m_ui->angleValueRobot->setText(value + " degrees.");
    //y += 50;
  } else {
    m_ui->idRobot->setPixmap(m_borderImage);
  }
  QRect region(offset_x, offset_y, 50, 50);
  m_ui->numberRobot->setPixmap(m_numbersImage.copy(region));
}

void RobotWidget::on_toolsButtonRobot_clicked() { }
