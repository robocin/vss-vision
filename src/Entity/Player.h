#ifndef PLAYER_H
#define PLAYER_H

#include "Entity.h"

class Player : public Entity {
  Float m_angle;

  Void updateAngle(const Float &t_angle);

public:
  Player();

  Void update(const Float &t_time, const Point &t_position, const Float &t_angle);

  Float angle();
};

#endif // PLAYER_H
