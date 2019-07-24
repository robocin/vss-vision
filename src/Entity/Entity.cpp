#include "Entity.h"

Entity::Entity() {
}

Void Entity::updateTime(const Float &t_time) {
    m_lastTimes.emplace_front(t_time);
    m_time = m_lastTimes[0];
    if (m_lastTimes.size() > 1) {
        m_accumulateTime += m_lastTimes[0] - m_lastTimes[1];
    }
    if (m_lastTimes.size() > MAX_ITERATIONS) {
        size_t sz = m_lastTimes.size();
        Float delta = m_lastTimes[sz - 2] - m_lastTimes[sz - 1];
        m_accumulateTime -= delta;
        m_lastTimes.pop_back();
    }
}

Void Entity::updatePosition(const Point &t_position) {
    m_lastPositions.emplace_front(t_position);
    m_position = m_lastPositions[0];
    if (m_lastPositions.size() > 1) {
        Point delta = m_lastPositions[0] - m_lastPositions[1];
        delta.x = std::abs(delta.x);
        delta.y = std::abs(delta.y);
        m_accumulatePosition += delta;
    }
    if (m_lastPositions.size() > MAX_ITERATIONS) {
        size_t sz = m_lastPositions.size();
        Point delta = m_lastPositions[sz - 2] - m_lastPositions[sz - 1];
        delta.x = std::abs(delta.x);
        delta.y = std::abs(delta.y);
        m_accumulatePosition -= delta;
        if (std::abs(m_accumulatePosition.x) < Global::eps()) {
            m_accumulatePosition.x = 0;
        }
        if (std::abs(m_accumulatePosition.y) < Global::eps()) {
            m_accumulatePosition.y = 0;
        }
        m_lastPositions.pop_back();
    }
}

Void Entity::updateSpeed() {
    if (m_lastTimes.size() > 1 && m_lastPositions.size() > 1) {
        m_lastSpeeds.emplace_front(m_accumulatePosition / (m_accumulateTime / 1000.0));
        m_speed = m_lastSpeeds[0];
    }
    if (m_lastSpeeds.size() > 1) {
        Point delta = m_lastSpeeds[0] - m_lastSpeeds[1];
        delta.x = std::abs(delta.x);
        delta.y = std::abs(delta.y);
        m_accumulateSpeed += delta;
    }
    if (m_lastSpeeds.size() > MAX_ITERATIONS) {
        size_t sz = m_lastSpeeds.size();
        Point delta = m_lastSpeeds[sz - 2] - m_lastSpeeds[sz - 1];
        delta.x = std::abs(delta.x);
        delta.y = std::abs(delta.y);
        m_accumulateSpeed -= delta;
        if (std::abs(m_accumulateSpeed.x) < Global::eps()) {
            m_accumulateSpeed.x = 0;
        }
        if (std::abs(m_accumulateSpeed.y) < Global::eps()) {
            m_accumulateSpeed.y = 0;
        }
        m_lastSpeeds.pop_back();
    }
}

Void Entity::updateAcceleration() {
    if (m_lastTimes.size() > 1 && m_lastSpeeds.size() > 1) {
        m_lastAccelerations.emplace_front(m_accumulateSpeed / (m_accumulateTime / 1000.0));
        m_acceleration = m_lastAccelerations[0];
    }
    if (m_lastAccelerations.size() > MAX_ITERATIONS) {
        m_lastAccelerations.pop_back();
    }
}

Void Entity::update(const Float &t_time, const Point &t_position) {
    // MAX_ITERATIONS VARIA COM OS FPS DA CAMERA
    // ACREDITO QUE TALVEZ PRECISE NAO SER UMA CTE!
    static_assert (MAX_ITERATIONS > 5, "Max iterations should be greater");
    updateTime(t_time);
    updatePosition(t_position);
    updateSpeed();
    updateAcceleration();
}

Void Entity::setActive(const Bool &t_active) {
    m_active = t_active;
}

const Point &Entity::position() {
    return m_position;
}

void Entity::setUpdated(const Bool &t_updated)
{
  m_updated = t_updated;
}

const Bool &Entity::isUpdated()
{
  return m_updated;
}

void Entity::setAngle(const Float &t_angle)
{
  m_angle = t_angle;
}

const Float &Entity::getAngle()
{
  return m_angle;
}

void Entity::setColor(const Int &t_color)
{
  m_color = t_color;
}

Int &Entity::getColor()
{
  return m_color;
}
