/* Network classes made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This class contains all the network interface we use.
 *
 */

#ifndef NETWORK_H
#define NETWORK_H
#include "Base.hpp"
#include "Entity.hpp"
#include "SFML/Network.hpp"

class Network {
    static sf::UdpSocket socket;
    static sf::IpAddress recipient;
    static sf::Int32 frameId;
public:
    static sf::Uint16 port;
	/*
	*	@brief	Method to send entities for a frame.
	*	@param[in]  entities  The entities to be sent for a frame.
	*/
    static void sendFrame(std::vector<Entity> &entities);
};

#endif // NETWORK_H
