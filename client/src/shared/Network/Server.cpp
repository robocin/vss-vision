/* Server classes made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This class contains all the SERVER network interface we use.
 *
 */
#include "Network/Server.hpp"

sf::Uint16 Server::port = static_cast<sf::Uint16>(54000);
sf::IpAddress Server::recipient = "0.0.0.0";
sf::UdpSocket Server::socket;
sf::Int32 Server::frameId = 0;

void Server::sendFrame(std::vector<Entity> &entities) {
    if (!entities.size()) return;
    if (entities.size() > 255) {
        spdlog::get("Server")->info("sendFrame:: I cannot send more than 255 entities. You asked {}.\n", entities.size());
        return;
    }

    sf::Packet packet;

    packet << static_cast<sf::Int32>(Server::frameId);
    ++frameId;
    packet << static_cast<sf::Uint8>(entities.size());

    for (int i=0; i < entities.size(); ++i) {
        packet  << static_cast<sf::Uint8>(entities[i].id())
                << static_cast<Float>(entities[i].position().x)
                << static_cast<Float>(entities[i].position().y)
                << static_cast<Float>(entities[i].angle());
    }
    
    if (Server::socket.send(packet, recipient, port) != sf::Socket::Done)
    {
        spdlog::get("Server")->info("sendFrame:: Something went wrong when trying to send the frame.\n");
    }
}