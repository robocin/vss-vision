#include "Player.h"

Player::Player() {

}

Void Player::updateAngle(const Float &t_angle) {
    m_angle = t_angle;
}

Void Player::update(const Float &t_time, const Point &t_position, const Float &t_angle) {
  Entity::update(t_time, t_position);
  updateAngle(t_angle);
}

Float Player::angle(){
    return m_angle;
}
