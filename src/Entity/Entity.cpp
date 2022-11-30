#include "Entity.h"

Entity::Entity(const uint& t_id) : m_id(t_id) {
}

void Entity::outdate() {
  m_updated = false;
}

void Entity::update(const Point& t_position, const float& t_angle) {
  m_position = t_position;
  m_angle = t_angle;
  m_updated = true;
}

Point Entity::position() {
  return m_position;
}

bool Entity::updated() {
  return m_updated;
}

float Entity::angle() {
  return m_angle;
}

void Entity::id(const uint& t_id) {
  m_id = t_id;
}

const uint& Entity::id() {
  return m_id;
}

void Entity::team(const uint& t_team) {
  m_team = t_team;
}

const uint& Entity::team() {
  return m_team;
}

bool operator<(Entity& a, Entity& b) {
  return a.id() < b.id();
}
