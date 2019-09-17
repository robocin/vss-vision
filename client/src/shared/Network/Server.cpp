/* Server class made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This class contains all the Server network interface we use.
 *
 */
#include "Network/Server.hpp"

sf::Uint16 Network::Server::m_port = static_cast<sf::Uint16>(54000);
sf::Int32 Network::Server::frameId = 0;
FramesQueue Network::Server::framesQueue;
SubscribersSet Network::Server::subscribersSet;
SubscriberConnections Network::Server::connections;
std::atomic<bool> Network::Server::Exit;


void Network::Server::_sendFrame(Frame &t_frame) {
    Entities &entities = t_frame.entities();

    if (!entities.size()) return;
    if (entities.size() > 255) {
        spdlog::get("Server")->info("sendFrame:: I cannot send more than 255 entities. You asked {}.\n", entities.size());
        return;
    }

    sf::Packet packet;

    packet << static_cast<sf::Int32>(t_frame.id());
    ++frameId;
    packet << static_cast<sf::Uint8>(entities.size());

    for (int i=0; i < entities.size(); ++i) {
        packet  << static_cast<sf::Uint8>(entities[i].id())
                << static_cast<Float>(entities[i].position().x)
                << static_cast<Float>(entities[i].position().y)
                << static_cast<Float>(entities[i].angle());
    }
    

    
}

void Network::Server::_sendPacketToSubscriber(sf::UdpSocket &socket, Subscriber &subscriber, sf::Packet &packet) {
    sf::IpAddress recipient = subscriber.first;
    sf::Uin16 port = subscriber.second;

    if (socket.send(packet, recipient, port) != sf::Socket::Done)
    {
        spdlog::get("Server")->info("sendFrame:: Something went wrong when trying to send the frame to {}.\n", subscriber.ip().c_str());
    }
}

void Network::Server::_subscriberMain(Subscriber &subscriber) {
    sf::UdpSocket socket;
    while(!Exit) {

    }
}

void _addSubscriber(Subscriber &t_subscriber) {
    connections.insert(SubscriberConnection(t_subscriber));
}

void Network::Server::sendFrame(Frame &t_frame) {
    
}

sf::Uint16 Network::Server::getPort() {
    return m_port;
}