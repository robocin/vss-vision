#ifndef ROBOTWIDGET_H
#define ROBOTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QPainter>

namespace Ui {
  class RobotWidget;
}

class RobotWidget : public QWidget {
  Q_OBJECT

 public:
  explicit RobotWidget(const size_t &t_index, QWidget *parent = nullptr);

  ~RobotWidget();

  QPixmap getRobotId(int team_color);
  void setPrimaryColor(QPixmap &t_robotId, int team_color);
  void setSecodaryColor(QPixmap &t_robotId, int team_color);
  void update();

 private slots:
  void on_toolsButtonRobot_clicked();

 private:
  Ui::RobotWidget *m_ui;
  size_t m_index;
  QPixmap m_borderImage;
  QPixmap m_numbersImage;
  uint m_robotId;
};

#endif  // ROBOTWIDGET_H
