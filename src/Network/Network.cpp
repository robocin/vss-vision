#include "Network/Network.h"
#include "spdlog/spdlog.h"
sf::Uint16 Network::port = static_cast<sf::Uint16>(54000);
sf::IpAddress Network::recipient = "127.0.0.1";
sf::UdpSocket Network::socket;
sf::Int32 Network::frameId = 0;

void Network::sendFrame(std::vector<Entity> &entities, uint32_t timestamp_in_msec) {
    if (!entities.size()) return;
    if (entities.size() > 255) {
        printf("Network:: sendFrame:: I cannot send more than 255 entities. You asked %d.\n", static_cast<int>(entities.size()));
        return;
    }

    sf::Packet packet;
    packet << static_cast<sf::Uint8>('F');
    packet << static_cast<sf::Uint32>(timestamp_in_msec);
    packet << static_cast<sf::Int32>(Network::frameId);
    ++frameId;
    packet << static_cast<sf::Uint8>(entities.size());

    for (size_t i=0; i < entities.size(); ++i) {
        packet  << static_cast<sf::Uint8>(entities[i].id())
                << static_cast<Float>(entities[i].position().x)
                << static_cast<Float>(entities[i].position().y)
                << static_cast<Float>(entities[i].angle());
    }
    
    if (Network::socket.send(packet, recipient, port) != sf::Socket::Done)
    {
        printf("Network:: sendFrame:: Something went wrong when trying to send the frame.\n");
    } // else printf("Network:: sendFrame:: Frame sent.\n");
}