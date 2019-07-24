#include "GameInfo.h"
#include "Utils/Utils.h"

Void GameInfo::setLockedFrame(const Bool &t_active) {
    if (t_active) {
        m_frameLocker.lock();
    } else {
        m_frameLocker.unlock();
    }
}

GameInfo::GameInfo()
: m_frame(EMPTY_MATRIX) {
//  std::fill(m_behaviorsTable.begin(), m_behaviorsTable.end(), false);
//  std::fill(m_buttonsTable.begin(), m_buttonsTable.end(), INVALID_BUTTON_TYPE);
}

GameInfo &GameInfo::singleton() {
    static GameInfo instance;
    return instance;
}

Void GameInfo::setFrame(const cv::Mat &t_frame) {
  setLockedFrame(true);
  m_frame = t_frame.clone();
  setLockedFrame(false);
}

Void GameInfo::clearFrame() {
  setFrame(EMPTY_MATRIX);
}

Void GameInfo::mergeFrame(const cv::Mat &t_frame) {
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

void GameInfo::setHalf(int half)
{
  m_half = half;
}

int GameInfo::getHalf()
{
  return m_half;
}

Entity &GameInfo::ball() {
  return m_ball;
}

Players &GameInfo::players() {
    return m_players;
}

Timer &GameInfo::time() {
  return m_time;
}
