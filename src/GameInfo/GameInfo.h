#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "Utils/EnumsAndConstants.h"
#include "opencv2/opencv.hpp"
#include "Timer/Timer.h"
#include <vector>
#include <array>
#include "Entity/Entity.h"
#include <QMutex>

class GameInfo {
  Timer m_time;
  QMutex m_frameLocker;
  cv::Mat m_frame;
  Entity m_ball;
  int m_half;

  Void setLockedFrame(const Bool &t_active = true);

public:
  GameInfo();

  static GameInfo &singleton();

  Void setFrame(const cv::Mat &t_frame);

  Void clearFrame();

  Void mergeFrame(const cv::Mat &t_frame);

  // Pega uma copia do frame
  cv::Mat frameCopy();

  void setHalf(int half);

  int getHalf();

  Entity &ball();

  Timer &time();
};

// Singleton
static GameInfo &vss = GameInfo::singleton();

#endif // GAMEINFO_H
