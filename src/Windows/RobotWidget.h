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

  QPixmap getRobotId();
  void setPrimaryColor(QPixmap &t_robotId);
  void setSecondaryColor(QPixmap &t_robotId);
  void setSecondSecondary(QPixmap &t_robotId);
  void update();

 private slots:
  void on_toolsButtonRobot_clicked();

 private:
  Ui::RobotWidget *m_ui;
  size_t m_index;
  QPixmap m_borderImage;
  QPixmap m_numbersImage;
  uint m_robotId;
  std::vector<int> ids = {204, 240, 276, 174, 246, 282, 180, 288, 216, 186, 222, 258};
};

#endif  // ROBOTWIDGET_H
