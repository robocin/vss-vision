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
#include <string>

namespace Network {

    class Server {
        static sf::Uint16 m_port;
        static sf::UdpSocket m_socket;
        static sf::SocketSelector m_socketSelector;
        static bool m_socketSelectorReady;
        static sf::IpAddress recipient;
        static sf::Int32 frameId;
        static SubscriberConnections connections;
        static std::atomic<bool> Exit;

        static void _sendFrame(Frame &t_frame);
        static void _addSubscriber(Subscriber t_subscriber);
        static void _clearSubscribers();
        static sf::Packet _buildPacket(Frame &t_frame);
    public:
        /*
        *	@brief	Method to set port number to be used.
        *	@param[in]  t_port  The port number.
        */
        static void setPort(sf::Uint16 t_port);

        /*
        *	@brief	Method to get port number that's being used.
        *   @return sf::Uint16  The port number.
        */
        static sf::Uint16 getPort();

        /*
        *	@brief	Method to send entities for a frame.
        *	@param[in]  t_frame  The frame that should be sent.
        */
        static void sendFrame(Frame t_frame);

        /*
        *	@brief	Method to wait for a client subscription.
        *	@param[in]  t_time  The time that the server will wait for a client subscription.
        *   @return     bool    Return true if there's a client with the MAGGIC_STRING as message.
        */
        static bool waitClient(sf::Time t_time);

    };
};

#endif // SERVER_H
