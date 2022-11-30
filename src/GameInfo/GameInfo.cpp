#include "GameInfo.h"
#include "Utils/Utils.h"

void GameInfo::setLockedFrame(const bool& t_active) {
  if (t_active) {
    m_frameLocker.lock();
  } else {
    m_frameLocker.unlock();
  }
}

GameInfo::GameInfo() : m_frame(EMPTY_MATRIX) {
  //  std::fill(m_behaviorsTable.begin(), m_behaviorsTable.end(), false);
  //  std::fill(m_buttonsTable.begin(), m_buttonsTable.end(), INVALID_BUTTON_TYPE);
}

GameInfo& GameInfo::singleton() {
  static GameInfo instance;
  return instance;
}

void GameInfo::setFrame(const cv::Mat& t_frame) {
  setLockedFrame(true);
  m_frame = t_frame.clone();
  setLockedFrame(false);
}

void GameInfo::clearFrame() {
  setFrame(EMPTY_MATRIX);
}

void GameInfo::mergeFrame(const cv::Mat& t_frame) {
  setLockedFrame(true);
  m_frame += t_frame.clone();
  setLockedFrame(false);
}

cv::Mat GameInfo::frameCopy() {
  cv::Mat ret;
  setLockedFrame(true);
  ret = m_frame.clone();
  setLockedFrame(false);
  return ret;
}

void GameInfo::setHalf(int half) {
  setLockedFrame(true);
  m_half = half;
  setLockedFrame(false);
}

int GameInfo::getHalf() {
  setLockedFrame(true);
  int ret = m_half;
  setLockedFrame(false);
  return ret;
}

Entity GameInfo::ball() {
  setLockedFrame(true);
  Entity ret(m_ball);
  setLockedFrame(false);
  return ret;
}

void GameInfo::setBall(Entity& t_ball) {
  setLockedFrame(true);
  m_ball = t_ball;
  setLockedFrame(false);
}

Players GameInfo::players(uint t_team) {
  Players ret;
  setLockedFrame(true);
  switch (t_team) {
    case 0: ret.assign(m_players.begin(), m_players.end()); break;
    default:
      for (auto& e : m_players) {
        if (e.team() == t_team)
          ret.push_back(e);
      }
  }
  setLockedFrame(false);
  return ret;
}

void GameInfo::setPlayers(Players& t_players) {
  setLockedFrame(true);
  m_players.assign(t_players.begin(), t_players.end());
  setLockedFrame(false);
}

void GameInfo::setEntities(Entity& t_ball, Players& t_players) {
  setLockedFrame(true);
  m_ball = t_ball;
  m_players.assign(t_players.begin(), t_players.end());
  setLockedFrame(false);
}

Timer GameInfo::time() {
  setLockedFrame(true);
  Timer ret(m_time);
  setLockedFrame(false);
  return ret;
}

void GameInfo::setTime(Timer& t_timer) {
  setLockedFrame(true);
  m_time = t_timer;
  setLockedFrame(false);
}
