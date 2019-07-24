#ifndef ROBOTWIDGET_H
#define ROBOTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>
#include "ParametersWindow.h"

namespace Ui {
  class RobotWidget;
}

class RobotWidget : public QWidget {
  Q_OBJECT

 public:
  explicit RobotWidget(const size_t &t_index, QWidget *parent = nullptr);

  RobotWidget(const size_t &t_index, String behaviour, String navigation,
              String planning, QWidget *parent = nullptr);

  ~RobotWidget();

  QPixmap getRobotId();
  void setPrimaryColor(QPixmap &t_robotId);
  void setSecodaryColor(QPixmap &t_robotId);
  void update();

 private slots:
  void on_toolsButtonRobot_clicked();

 private:
  Ui::RobotWidget *m_ui;
  size_t m_index;
  QPixmap m_borderImage;
  QPixmap m_numbersImage;
  ParametersWindow m_parametersWindow;
};

#endif  // ROBOTWIDGET_H
