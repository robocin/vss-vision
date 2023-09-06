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
  std::vector<int> ids = {5, 5, 7, 7, 5, 6};
  std::vector<int> idsAlt = {7, 6, 6, 4, 4, 4};
};

#endif  // ROBOTWIDGET_H
