#include "GameInfo.h"
#include "Utils/Utils.h"


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
  
  m_frame = t_frame.clone();
  
}

Void GameInfo::clearFrame() {
  setFrame(EMPTY_MATRIX);
}

Void GameInfo::mergeFrame(const cv::Mat &t_frame) {
  
  m_frame += t_frame.clone();
  
}

cv::Mat GameInfo::frameCopy() {
  cv::Mat ret;
  
  ret = m_frame.clone();
  
  return ret;
}

void GameInfo::setHalf(int half)
{
  
  m_half = half;
  
}

int GameInfo::getHalf()
{
  
  int ret = m_half;
  
  return ret;
}

Entity GameInfo::ball() {
  
  Entity ret(m_ball);
  
  return ret;
}

void GameInfo::setBall(Entity& t_ball) {
  
  m_ball = t_ball;
  
}

Players GameInfo::players(uint t_team) {
    Players ret;
    
    switch (t_team) {
        case 0:
            ret.assign(m_players.begin(),m_players.end());
            break;
        default:
            for (auto& e : m_players) {
                if (e.team() == t_team)
                    ret.push_back(e);
            }
    }
    
    return ret;
}

void GameInfo::setPlayers(Players& t_players) {
    
    m_players.assign(t_players.begin(),t_players.end());
    
}

void GameInfo::setEntities(Entity &t_ball, Players &t_players) {
    
    m_ball = t_ball;
    m_players.assign(t_players.begin(),t_players.end());
    
}
