#include "Network/Network.h"

sf::Uint32 Network::port = static_cast<sf::Uint32>(54000);
sf::IpAddress Network::recipient = "0.0.0.0";
sf::UdpSocket Network::socket;

void Network::sendFrame(std::vector<Entity> &entities) {
    if (!entities.size()) return;
    if (entities.size() > 255) {
        spdlog::get("Network")->info("sendFrame:: I cannot send more than 255 entities. You asked {}.\n", entities.size());
        return;
    }

    sf::Packet packet;

    packet << static_cast<sf::Uint8>(entities.size());

    for (int i=0; i < entities.size(); ++i) {
        packet  << static_cast<sf::Uint8>(entities[i].id())
                << static_cast<Float>(entities[i].position().x)
                << static_cast<Float>(entities[i].position().y)
                << static_cast<Float>(entities[i].angle());
    }
    
    if (Network::socket.send(packet, recipient, port) != sf::Socket::Done)
    {
        spdlog::get("Network")->info("sendFrame:: Something went wrong when trying to send the frame.\n");
    }
}
