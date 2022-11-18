/**\ Network classes made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This class contains all the network interface we use.
 *
 */

#ifndef NETWORK_H
#define NETWORK_H

#ifndef EXTERNAL_COMPILATION
    #include "Entity/Entity.h"
    #include "Utils/Utils.h"
#endif
#include "SFML/Network.hpp"

class Network {
    static sf::UdpSocket socket;
    static sf::IpAddress recipient;
public:
    static sf::Int32 frameId;
    static sf::Uint16 port;
	/*
	*	@brief	Method to send entities for a frame.
	*	@param[in]  entities  The entities to be sent for a frame.
	*/
    static void sendFrame(std::vector<Entity> &entities, uint32_t timestamp_in_msec = 0);

    static void buttonsMessageTeamColor(bool teamColor);

    static void buttonsMessagePlayNN(bool playNN);

    static void buttonsMessageStop();
};

#endif /**		NETWORK_H*/
