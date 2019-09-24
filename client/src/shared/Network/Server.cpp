/* Server class made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This class contains all the Server network interface we use.
 *
 */
#include "Network/Server.hpp"

sf::Uint16 Network::Server::m_port = static_cast<sf::Uint16>(20000);
sf::UdpSocket Network::Server::m_socket;
sf::SocketSelector Network::Server::m_socketSelector;
bool Network::Server::m_socketSelectorReady = false;
Network::SubscriberConnections Network::Server::connections;
std::atomic<bool> Network::Server::Exit;
#define MAGGIC_STRING "MAGGIC"

#include <string.h>


sf::Packet Network::Server::_buildPacket(Frame &t_frame) {
    Entities &entities = t_frame.entities();
    sf::Packet packet;

    if (!entities.size()) return packet;
    if (entities.size() > 255) {
        spdlog::get("Server")->info("sendFrame:: I cannot send more than 255 entities. You asked {}.\n", entities.size());
        return packet;
    }


    packet << static_cast<sf::Int32>(t_frame.id());
    packet << static_cast<sf::Uint8>(entities.size());

    for (int i=0; i < entities.size(); ++i) {
        packet  << static_cast<sf::Uint8>(entities[i].id())
                << static_cast<Float>(entities[i].position().x)
                << static_cast<Float>(entities[i].position().y)
                << static_cast<Float>(entities[i].angle());
    }
    
    return packet;
}

void Network::Server::_addSubscriber(Subscriber t_subscriber) {
    std::string subscriptionId = Network::to_string(t_subscriber);
    connections[subscriptionId] = new SubscriberConnection(t_subscriber);
}

void Network::Server::_clearSubscribers() {
    for ( auto &e : connections) {
        delete e.second;
    }
}

void Network::Server::sendFrame(Frame t_frame) {
    sf::Packet packet = _buildPacket(t_frame);
    for(auto &connection : connections) {
        connection.second->sendPacket(packet);
    }
}

sf::Uint16 Network::Server::getPort() {
    return m_port;
}

bool Network::Server::waitClient(sf::Time t_time) {
    bool success = false;
    // if (m_socket.isBlocking()) 
    //     m_socket.setBlocking(false);

    // if (!m_socketSelectorReady) {
    //     m_socketSelector.add(m_socket);
    //     m_socketSelectorReady = true;
    // }
    // if (m_socket.bind(m_port) != sf::Socket::Done) {
    //     spdlog::get("Server")->error("waitClient:: Error trying to bind socket on port {}\n", m_port);
    //     return false;
    // }
    // spdlog::get("Server")->info("waitClient:: Waiting for client on port {}.\n", m_port);

    // m_socketSelector.wait(t_time);

    // if (m_socketSelector.isReady(m_socket)) {
    //     sf::Packet t_packet;
    //     sf::IpAddress t_remoteAddress;
    //     sf::Uint16 t_remotePort;
    //     m_socket.receive(t_packet, t_remoteAddress, t_remotePort);
    //     char maggic_string[7];
    //     t_packet >> maggic_string;
    //     if (!strcmp(maggic_string,MAGGIC_STRING)) {
    //         spdlog::get("Server")->info("waitClient:: There's a client in {}.\n", t_remoteAddress.toString());
    //         _addSubscriber(Network::make_subscriber(t_remoteAddress, t_remotePort));
    //         success = true;
    //     } else {
    //         spdlog::get("Server")->info("waitClient:: {} did not sent the MAGGIC_STRING.\n", t_remoteAddress.toString());
    //     }
    // } else {
    //     spdlog::get("Server")->info("waitClient:: Is any client trying to connect?.\n");
    // }
    spdlog::get("Server")->info("waitClient:: Now unbinding...\n");

    // m_socket.unbind();
    return success;
}