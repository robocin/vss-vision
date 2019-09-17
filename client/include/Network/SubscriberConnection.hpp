/* Subscriber class made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This file has all the Subscriber structures and related things.
 *
 */

#ifndef SUBSCRIBER_CONNECTION_H
#define SUBSCRIBER_CONNECTION_H
#include <SFML/Main.hpp>
#include <vector>
#include <unnordered_map>
#include "Network/Subscriber.hpp"

namespace Network {

    class SubscriberConnection {
        Subscriber m_subscriber;
        void _run() {
            
        }
        public:
        SubscriberConnection(Subscriber &t_subscriber){
            m_subscriber = t_subscriber;
        }
    }

    typedef std::unnordered_map<std::string, SubscriberConnection> SubscriberConnections;
};

#endif // SUBSCRIBER_CONNECTION_H
