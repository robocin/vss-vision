#include "Entity.h"

Entity::Entity(const Int &t_id) {
    m_id = t_id;
}

Void Entity::update(const Point &t_position, const Float &t_angle) {
    m_position = t_position;
    m_angle = t_angle;
    m_updated = true;
}

const Point &Entity::position() {
    return m_position;
}

const Bool &Entity::updated()
{
  return m_updated;
}

const Float &Entity::angle()
{
  return m_angle;
}

const Int &Entity::id()
{
  return m_id;
}
