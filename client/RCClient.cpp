#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <vector>
#include <mutex>
#include <atomic>
#include <omp.h>


typedef struct s_Entity {
    int id;
    float x,y,theta;
} Entity;

typedef std::vector<Entity> Entities;

Entities entities;
std::mutex mtx;
std::atomic<bool> Exit;

int main()
{
    #pragma omp parallel sections
    {
        #pragma omp section 
        {
            // UDP socket:
            sf::UdpSocket socket;
            sf::IpAddress sender = "0.0.0.0";
            sf::Uint16 oport = 54000, port = oport;

            // bind the socket to a port
            if (socket.bind(port) != sf::Socket::Done)
            {
                fprintf(stderr,"Error trying to bind socket on port %d\n", port);
            }
            while (!Exit) {
                sf::Packet packet;
                port = oport;
                if (socket.receive(packet, sender, port) != sf::Socket::Done)
                {
                    // error...
                }
                std::cout << "Received from " << sender << " on port " << port << std::endl;
                sf::Uint8 entitiesSize, id;
                float posX, posY, angle;
                if (packet >> entitiesSize) {
                    std::cout << "entities : " << static_cast<int>(entitiesSize) << std::endl;
                    mtx.lock();
                    entities.resize(static_cast<int>(entitiesSize));
                    for (int i=0; i < entitiesSize; ++i) {
                        if (packet >> id >> posX >> posY >> angle) {
                            entities[i].id = id;
                            entities[i].x = posX;
                            entities[i].y = posY;
                            entities[i].theta = angle;
                        } else {
                            entities.resize(i);
                            std::cerr << "Error on retrieving entity data" << std::endl;
                            break;
                        }
                    }
                    mtx.unlock();
                } else {
                    std::cerr << "Error on retrieving data" << std::endl;
                }
            }
        }

        #pragma omp section 
        {
            sf::RenderWindow window(sf::VideoMode(640, 480), "Game Window");
            sf::CircleShape ballShape(10);
            sf::RectangleShape robotShape(sf::Vector2f(10,10));
            ballShape.setFillColor(sf::Color(222,120,31)); // Orange
            robotShape.setFillColor(sf::Color::Green);

            while (window.isOpen())
            {
                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed) {
                        window.close();
                        Exit = true;
                    }
                }

                window.clear();
                mtx.lock();
                for (auto &entity : entities) {
                    if (entity.id == 0) {
                        ballShape.setPosition(entity.x,entity.y);
                        window.draw(ballShape);
                        printf("entity %d (%f %f %f)\n", entity.id, entity.x, entity.y, entity.theta);
                    } else {
                        robotShape.setPosition(entity.x,entity.y);
                        window.draw(robotShape);
                    }
                }
                mtx.unlock();
                window.display();
            }
        }
    }
    

    


    return 0;
}
