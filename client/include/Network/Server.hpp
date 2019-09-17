/* Server class made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This class contains all the Server network interface we use.
 *
 */

#ifndef SERVER_H
#define SERVER_H
#include "Network/Frame.hpp"
#include "Network/SubscriberConnection.hpp"
#include <atomic>

namespace Network {

    class Server {
        static sf::Uint16 m_port;
        static sf::UdpSocket socket;
        static sf::IpAddress recipient;
        static sf::Int32 frameId;
        static SubscriberConnections connections;
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

    };
};

#endif // SERVER_H
