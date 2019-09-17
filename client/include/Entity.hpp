#ifndef ENTITY_H
#define ENTITY_H
#include "Base.hpp"

class Entity {
    int m_id;
    Vec2 m_position;
    float m_angle;

public:
    int &id() {
        return m_id;
    }
    Vec2 &position() {
        return m_position;
    }
    float &angle() {
        return m_angle;
    }
};

typedef std::vector<Entity> Entities;
typedef std::vector<Entities> ListOfEntities;

#endif // ENTITY_H