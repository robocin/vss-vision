/* Frame class made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This file has all the Frame structures and related things.
 *
 */

#ifndef FRAME_H
#define FRAME_H
#include <SFML/Main.hpp>
#include <Entity.hpp>
#include <queue>
#include <vector>

class Frame {
    Entities m_entities;
    sf::Int32 m_frameId;
    public:
    Frame():m_frameId(0){}
    Frame(Entities &t_entities) {
        m_entities.assign(t_entities.begin(),t_entities.end());
    }
    Frame(int t_frameId, Entities &t_entities) {
        m_entities.assign(t_entities.begin(),t_entities.end());
    }
    Entities &entities() {
        return m_entities;
    }
    sf::Int32 &id() {
        return m_frameId;
    }
};
typedef std::vector<Frame> Frames;
typedef std::queue<Frame> FramesQueue;

#endif // FRAME_H