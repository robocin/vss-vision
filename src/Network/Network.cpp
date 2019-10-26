#include "Network/Network.h"

sf::Uint16 Network::port = static_cast<sf::Uint16>(54000);
sf::IpAddress Network::recipient = "0.0.0.0";
sf::UdpSocket Network::socket;
sf::Int32 Network::frameId = 0;

void Network::sendFrame(std::vector<Entity> &entities, uint32_t timestamp_in_msec) {
    if (!entities.size()) return;
    if (entities.size() > 255) {
        spdlog::get("Network")->info("sendFrame:: I cannot send more than 255 entities. You asked {}.\n", entities.size());
        return;
    }

    sf::Packet packet;
    packet << static_cast<sf::Uint8>('F');
    packet << static_cast<sf::Uint32>(timestamp_in_msec);
    packet << static_cast<sf::Int32>(Network::frameId);
    ++frameId;
    packet << static_cast<sf::Uint8>(entities.size());

    for (int i=0; i < entities.size(); ++i) {
        packet  << static_cast<sf::Uint8>(entities[i].id())
                << static_cast<Float>((entities[i].position().x*(1.4411)))
                << static_cast<Float>(entities[i].position().y*1.3421)
                << static_cast<Float>(entities[i].angle());
    }
    
    if (Network::socket.send(packet, recipient, port) != sf::Socket::Done)
    {
        spdlog::get("Network")->info("sendFrame:: Something went wrong when trying to send the frame.\n");
    }
}

void Network::buttonsMessageTeamColor(bool teamColor)
{
    sf::Packet packet;
    packet << (teamColor==true?static_cast<sf::Uint8>('Y'):static_cast<sf::Uint8>('B')); // Yellow or Blue
    for(int i = 0; i < 10; ++i)
    {
        if (Network::socket.send(packet, recipient, port) != sf::Socket::Done)
        {
            spdlog::get("Network")->info("sendFrame:: Something went wrong when trying to send the frame.\n");
        }
    }
}

void Network::buttonsMessagePlayNN(bool playNN)
{
    //std::cout << (teamColor==true?"Yellow":"Blue") << " | " << (atackRight==true?"Right":"Left") << " | " << (playNN==true?"Play":"Pause") << std::endl;
    sf::Packet packet;
    packet << (playNN==true?static_cast<sf::Uint8>('R'):static_cast<sf::Uint8>('P')); // Play or Stop

    for(int i = 0; i < 10; ++i)
    {
        if (Network::socket.send(packet, recipient, port) != sf::Socket::Done)
        {
            spdlog::get("Network")->info("sendFrame:: Something went wrong when trying to send the frame.\n");
        }
    }
}

void Network::buttonsMessageStop()
{
    sf::Packet packet;
    packet << static_cast<sf::Uint8>('S');

    for(int i = 0; i < 10; ++i)
    {
        if (Network::socket.send(packet, recipient, port) != sf::Socket::Done)
        {
            spdlog::get("Network")->info("sendFrame:: Something went wrong when trying to send the frame.\n");
        }
    }
}
