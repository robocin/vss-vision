#ifndef Entity_H
#define Entity_H

#include "Utils/Utils.h"

// Comentar o uso das funcoes

class Entity {
  Bool m_active;

  Float m_time;

  Float m_accumulateTime;
  Point m_accumulatePosition;
  Point m_accumulateSpeed;

  Point m_position;
  Point m_speed;
  Point m_acceleration;

  Deque<Float> m_lastTimes;
  Deque<Point> m_lastPositions;
  Deque<Point> m_lastSpeeds;
  Deque<Point> m_lastAccelerations;

  Void updateTime(const Float &t_time);
  Void updatePosition(const Point &t_position);
  Void updateSpeed();
  Void updateAcceleration();

public:
  Entity();

  Void update(const Float &t_time, const Point &t_position);

  Void setActive(const Bool &t_active = true);

  const Bool &isActive();

  const Float &accumulateTime();
  const Point &accumulatePosition();
  const Point &accumulateSpeed();

  /**
   * Get entity position
   * @return Point with the value of position in each axis
   */
  const Point &position();
  /**
   * Get entity speed
   * @return Point with the value of speed in each axis
   */
  const Point &speed();
  /**
   * Get entity acceleration
   * @return Point with the value of acceleration in each axis
   */
  const Point &acceleration();

  /**
   * Get last times
   * @return Deque of floating points, where the index 0 is the most recent value
   */
  const Deque<Float> &lastTimes();
  /**
   * Get last positions
   * @return Deque of points, where the index 0 is the most recent value
   */
  const Deque<Point> &lastPositions();
  /**
   * Get last speeds
   * @return Deque of points, where the index 0 is the most recent value
   */
  const Deque<Point> &lastSpeeds();
  /**
   * Get last accelerations
   * @return Deque of points, where the index 0 is the most recent value
   */
  const Deque<Point> &lastAccelerations();
};

#endif // Entity_H
