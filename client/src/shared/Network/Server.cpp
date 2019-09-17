/* Server class made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This class contains all the Server network interface we use.
 *
 */
#include "Network/Server.hpp"

sf::Uint16 Server::m_port = static_cast<sf::Uint16>(54000);
sf::Int32 Server::frameId = 0;
FramesQueue Server::framesQueue;
SubscribersSet Server::subscribersSet;
std::atomic<bool> Server::Exit;


void Server::_sendFrame(Frame &t_frame) {
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

void _sendPacketToSubscriber(Subscriber subscriber, sf::Packet &packet) {
    sf::IpAddress recipient = subscriber.ip();
    sf::Uin16 port = subscriber.port();
    sf::UdpSocket socket;

    if (socket.send(packet, recipient, port) != sf::Socket::Done)
    {
        spdlog::get("Server")->info("sendFrame:: Something went wrong when trying to send the frame to {}.\n", subscriber.ip().c_str());
    }
}

void _addSubscriber(Subscriber &t_subscriber) {
    subscribersSet.insert(t_subscriber);
}

void Server::sendFrame(Frame &t_frame) {
    framesQueue.push(t_frame);
}

sf::Uint16 getPort() {
    return m_port;
}

void run() {
    while(!Exit) {
        sendFrame(entities);
        time = clock.getElapsedTime();
        clock.restart().asSeconds();
        sf::sleep(sf::milliseconds(waitTime));
        ++frameId;
    }
}