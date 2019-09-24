#include <Network/Subscriber.hpp>


Network::Subscriber Network::make_subscriber(sf::IpAddress t_ipAddress, sf::Uint16 t_port){
    return std::make_pair(std::string(t_ipAddress.toString()), t_port);
}
std::string Network::to_string(Network::Subscriber &t_subscriber) {
    return t_subscriber.first + std::to_string(t_subscriber.second);
}