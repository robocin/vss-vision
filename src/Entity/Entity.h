#ifndef Entity_H
#define Entity_H

#include "Utils/Utils.h"

class Entity {
  Int m_id;
  Bool m_updated;
  Point m_position;
  Float m_angle;

public:
  /**
   * Constructor of Entity's class that uses an default '-1' id.
   * @return An Entity object
   */
  Entity(const Int &t_id = -1);
  /**
   * Update entity's position and angle
   */
  Void update(const Point &t_position, const Float &t_angle = 0);
  /**
   * Get entity position
   * @return Point with the value of position in each axis
   */
  const Point &position();
  /**
   * Get if entity is updated or not
   * @return Boolean that is true if entity is updated or false if entity is not updated
   */
  const Bool &updated();
  /**
   * Set updated as false, invalidating values
   */
  Void outdate();
  /**
   * Get entity's angle
   * @return Float with the entity's angle in radians
   */
  const Float &angle();
  /**
   * Get entity's id number
   * @return Integer with the entity's id number
   */
  const Int &id();
};

#endif // Entity_H
