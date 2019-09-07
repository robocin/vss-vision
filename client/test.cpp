#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <mutex>
#include <atomic>
#include <omp.h>
#include <unistd.h>
#include <math.h>

#define RAD_TO_DEG 180.0/M_PI

int frameRateLimit = 120;
class Vec2 {
public:
    float x,y;
    Vec2(float t_x = 0.f, float t_y = 0.f):x(t_x), y(t_y) {
    }
};

class Entity {
    int m_id;
    Vec2 m_position;
    float m_angle;

public:
    int &id() {
        return m_id;
    }
    Vec2 &position() {
        return m_position;
    }
    float &angle() {
        return m_angle;
    }
};

typedef std::vector<Entity> Entities;
#define EXTERNAL_COMPILATION
#include "../src/Network/Network.h"

Entities entities;
std::mutex mtx;
std::atomic<bool> Exit;
char fps_str[128];

int main()
{
    sf::Int32 frameId = 0;
    #pragma omp parallel sections
    {
        ///*
        #pragma omp section
        {
            // UDP socket:
            sf::UdpSocket socket;
            sf::IpAddress sender = "0.0.0.0";
            sf::Uint16 oport = 54000, port = oport;
            sf::Clock clock;
            sf::Time time;
            float fps = 0;
            time = clock.getElapsedTime();
            sf::Int32 lastFrameId = -1;

            // bind the socket to a port
            if (socket.bind(port) != sf::Socket::Done)
            {
                fprintf(stderr,"Error trying to bind socket on port %d\n", port);
                exit(2);
            }
            while (!Exit) {
                sf::Packet packet;
                port = oport;
                if (socket.receive(packet, sender, port) != sf::Socket::Done)
                {
                    fprintf(stderr,"Error trying to receive data from socket.");
                    continue;
                }
                std::cout << "Received from " << sender << " on port " << port << std::endl;
                sf::Uint8 entitiesSize, id;
                double posX, posY, angle;

                // Extract frameId from packet and verify if receveid packed has outdated frame
                packet >> frameId;
                if (frameId < lastFrameId) continue; // ignore older frames
                lastFrameId = frameId;

                if (packet >> entitiesSize) {
                    std::cout << "entities : " << static_cast<int>(entitiesSize) << std::endl;
                    mtx.lock();
                    entities.resize(static_cast<int>(entitiesSize));
                    for (int i=0; i < entitiesSize; ++i) {
                        if (packet >> id >> posX >> posY >> angle) {
                            entities[i].id() = id;
                            entities[i].position().x = posX;
                            entities[i].position().y = posY;
                            entities[i].angle() = angle;
                        } else {
                            entities.resize(i);
                            std::cerr << "Error on retrieving entity data" << std::endl;
                            break;
                        }
                    }
                    mtx.unlock();
                    time = clock.getElapsedTime();
                    fps = fps*0.9 + 1.0f/time.asSeconds()*0.1;
                    sprintf(fps_str, "FPS: %04.0f", fps);
                    clock.restart().asSeconds();
                } else {
                    std::cerr << "Error on retrieving data" << std::endl;
                }
                //usleep(100000);
                //printf("ke");
            }
        }
        //*/

        #pragma omp section
        {
            

            sf::Clock clock;
            sf::Time time;
            time = clock.getElapsedTime();

            while (!Exit)
            {
                time = clock.getElapsedTime();
                //usleep(1000);
                clock.restart().asSeconds();
                //sf::sleep(sf::milliseconds(10));
            }
            exit(0);
        }
    }

    return 0;
}