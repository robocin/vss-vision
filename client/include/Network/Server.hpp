/* Server class made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This class contains all the Server network interface we use.
 *
 */

#ifndef SERVER_H
#define SERVER_H
#include "Frame.hpp"
#include "SFML/Network.hpp"
#include <atomic>

class Server {
    static sf::Uint16 m_port;
    static sf::UdpSocket socket;
    static sf::IpAddress recipient;
    static sf::Int32 frameId;
    static FramesQueue framesQueue;
    static SubscribersSet subscribersSet;
    static std::atomic<bool> Exit;

    static void _sendFrame(Frame &t_frame);
    static void _addSubscriber(Subscriber &t_subscriber);
public:
    /*
	*	@brief	Method to set port number to be used.
	*	@param[in]  t_port  The port number.
	*/
    static void setPort(sf::Uint16 t_port);

    /*
	*	@brief	Method to get port number that's being used.
	*/
    static sf::Uint16 getPort();

	/*
	*	@brief	Method to send entities for a frame.
	*	@param[in]  t_frame  The frame that should be sent.
	*/
    static void sendFrame(Frame &t_frame);

    /*
	*	@brief	Method to be called by a thread. This is thread blocking.
	*/
    static void run();

};

#endif // SERVER_H
