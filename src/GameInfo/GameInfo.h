#ifndef GAMEINFO_H
#define GAMEINFO_H

#include "Utils/EnumsAndConstants.h"
#include "opencv2/opencv.hpp"
#include <vector>
#include <array>
#include "Entity/Entity.h"

class GameInfo {
  cv::Mat m_frame;
  Entity m_ball;
  Players m_players;
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

  Entity ball();

  void setBall(Entity& t_ball);

  Players players(uint t_team = 0);

  void setPlayers(Players& t_players);

  void setEntities(Entity &t_ball, Players &t_players);

};

// Singleton
static GameInfo &vss = GameInfo::singleton();

#endif // GAMEINFO_H
