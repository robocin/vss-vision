/* Subscriber class made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This file has all the Subscriber structures and related things.
 *
 */

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include <SFML/Main.hpp>
#include <vector>
#include <set>


class Subscriber {
    std::string m_ip;
    sf::Uint16 m_port;
    public:
    Subscriber(std::string &t_ip, sf::Uint16 t_port){
        m_ip.assign(t_ip.begin(),t_ip.end());
        m_port = t_port;
    }
    std::string &ip() {
        return m_ip;
    }
    sf::Uin16 &port() {
        return m_port;
    }
}

typedef std::vector<Subscriber> Subscribers;
typedef std::set<Subscriber> SubscribersSet;

#endif // SUBSCRIBER_H
