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
#include <pair>

namespace Network {
    typedef std::pair<std::string, sf::Uint16> Subscriber;
    typedef std::vector<Subscriber> Subscribers;
    typedef std::set<Subscriber> SubscribersSet;
    std::string to_string(Subscriber &t_subscriber) {
        return t_subscriber.first + std::to_string(t_subscriber.second);
    }
};

#endif // SUBSCRIBER_H
