/* Server classes made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This class contains all the SERVER network interface we use.
 *
 */

#ifndef SERVER_H
#define SERVER_H
#include "Base.hpp"
#include "Entity.hpp"
#include "SFML/Network.hpp"

class Server {
    static sf::UdpSocket socket;
    static sf::IpAddress recipient;
    static sf::Int32 frameId;
    static void _sendFrame(std::vector<Entity> &entities);
public:
    static sf::Uint16 port;
	/*
	*	@brief	Method to send entities for a frame.
	*	@param[in]  entities  The entities to be sent for a frame.
	*/
    static void sendFrame(std::vector<Entity> &entities);
};

#endif // SERVER_H
