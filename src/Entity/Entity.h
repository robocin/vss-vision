#ifndef Entity_H
#define Entity_H

#include "Utils/Utils.h"

// Comentar o uso das funcoes

class Entity {
  Bool m_updated;
  Point m_position;

public:
  Entity();

  Void update(const Float &t_time, const Point &t_position);

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
   * Set if this entity is updated
   */
  void setUpdated(const Bool &t_updated);
  /**
   * Get if entity is updated or not
   * @return Boolean that is true if entity is updated or false if entity is not updated
   */
  const Bool &isUpdated();
  /**
   * Set entity's angle
   */
  void setAngle(const Float &t_angle);
  /**
   * Get entity's angle
   * @return Float with the entity's angle in radians
   */
  const Float &getAngle();
};

#endif // Entity_H
