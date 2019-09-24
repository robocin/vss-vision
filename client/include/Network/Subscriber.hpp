/* Subscriber class made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This file has all the Subscriber structures and related things.
 *
 */

#ifndef SUBSCRIBER_H
#define SUBSCRIBER_H
#include <SFML/Main.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <utility>

namespace Network {
    typedef std::pair<std::string, sf::Uint16> Subscriber;
    typedef std::vector<Subscriber> Subscribers;
    Subscriber make_subscriber(sf::IpAddress t_ipAddress, sf::Uint16 t_port);
    std::string to_string(Subscriber &t_subscriber);
};

#endif // SUBSCRIBER_H
