/* Subscriber class made by the RoboCIn for the project IEEE - VSS
 * @author Lucas Oliveira Maggi
 *
 * This file has all the Subscriber structures and related things.
 *
 */

#ifndef SUBSCRIBER_CONNECTION_H
#define SUBSCRIBER_CONNECTION_H
#include <SFML/Main.hpp>
#include <thread>
#include <mutex>
#include <unordered_map>
#include "Base.hpp"
#include "Network/Subscriber.hpp"
#include "SFML/Network.hpp"

namespace Network {

    // class Thread {
    //     std::mutex m_mtx;
    //     std::atomic<bool> Exit;
    //     std::atomic<bool> m_isFinished;
    //     void m_run() {
    //         run();
    //         m_isFinished = true;
    //     }
    //     std::thread m_thread;
    //     public:
    //     Thread ():Exit(false), m_isFinished(false){
    //         m_thread(m_run)
    //     };
    //     bool isFinished() {
    //         return m_isFinished;
    //     }
    //     void wake() {
    //         m_mtx.unlock();
    //     }
    //     void wait() {
    //         if (!m_isFinished) {
    //             m_mtx.lock();
    //         }
    //     }
    //     void exit() {
    //         Exit = true;
    //     }
    //     virtual void run() = 0;
    // };

    class SubscriberConnection { //: public Thread {
        Subscriber m_subscriber;
        sf::UdpSocket m_socket;
        sf::Packet m_packet;

        void _sendPacketToSubscriber(sf::Packet &packet) {
            sf::IpAddress recipient = m_subscriber.first;
            sf::Uint16 port = m_subscriber.second;

            if (m_socket.send(packet, recipient, port) != sf::Socket::Done)
            {
                spdlog::get("Subscriber")->info("sendPacketToSubscriber:: Something went wrong when trying to send packet to {}.\n", m_subscriber.first.c_str());
            }
        }

        public:
        // void run() {
        //     while(!Exit) {
        //         //Thread::wait();
        //         _sendPacketToSubscriber(m_packet);
        //     }
        // }
        SubscriberConnection(Subscriber &t_subscriber){
            m_subscriber = t_subscriber;
        }
        void sendPacket(sf::Packet &t_packet) {
            m_packet = t_packet;
            _sendPacketToSubscriber(m_packet);
            // Thread::wake();
        }
    };

    typedef std::unordered_map<std::string, SubscriberConnection* > SubscriberConnections;
};

#endif // SUBSCRIBER_CONNECTION_H
