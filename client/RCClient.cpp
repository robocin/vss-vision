#include <SFML/Graphics.hpp>
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

typedef struct s_Entity {
    int id;
    float x,y,theta;
} Entity;

typedef std::vector<Entity> Entities;

Entities entities;
std::mutex mtx;
std::atomic<bool> Exit;
sf::Font font;
sf::Text text;
char fps_str[128];

void loadFont() {

    if (!font.loadFromFile("font/UbuntuMono-R.ttf"))
    {
        fprintf(stderr,"Error loading font\n");
        exit(1);
    }

    text.setFont(font);
    text.setString("Waiting...");
    text.setColor(sf::Color::White);
    text.setCharacterSize(25);
    text.setPosition(0, 0);
}
sf::Vector2f cvtPosToScreen(const float x, const float y, const sf::Window &window) {
    const float xFactor = 1.0f/170.0f;
    const float yFactor = 1.0f/130.0f;
    return sf::Vector2f(x*xFactor*window.getSize().x,
                        (1.f-y*yFactor)*window.getSize().y);
}

int main()
{
    loadFont();
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
            sf::RenderWindow window(sf::VideoMode(640, 480), "VSS-Vision");
            if (frameRateLimit > 0) window.setFramerateLimit(frameRateLimit);
            sf::CircleShape ballShape(10);
            //sf::RectangleShape robotShape(sf::Vector2f(10,10));
            sf::RectangleShape robotShape(sf::Vector2f(
                                    7.5/170.0*window.getSize().x,
                                    7.5/130.0*window.getSize().y));
            robotShape.setOrigin(sf::Vector2f(
                                    7.5/170.0*window.getSize().x*0.5,
                                    7.5/130.0*window.getSize().y*0.5));
            ballShape.setFillColor(sf::Color(222,120,31)); // Orange
            robotShape.setFillColor(sf::Color::Green);

            sf::Clock clock;
            sf::Time time;
            time = clock.getElapsedTime();

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
                Entities tmp_entities;
                mtx.lock();
                tmp_entities.assign(entities.begin(),entities.end());
                mtx.unlock();

                if (tmp_entities.size() > 0) {
                    text.setString(fps_str);
                    for (auto &entity : tmp_entities) {
                        if (entity.id == 0) {
                            sf::Vector2f v = cvtPosToScreen(entity.x,entity.y,window);
                            ballShape.setPosition(v.x,v.y);
                            window.draw(ballShape);
                        } else {
                            sf::Vector2f v = cvtPosToScreen(entity.x,entity.y,window);
                            robotShape.setPosition(v.x,v.y);
                            robotShape.rotate(entity.theta*RAD_TO_DEG);
                            window.draw(robotShape);
                            robotShape.rotate(-entity.theta*RAD_TO_DEG);
                            printf("entity %d (%f %f %f)\n", entity.id, entity.x, entity.y, entity.theta);
                        }
                    }
                    time = clock.getElapsedTime();
                    //sprintf(fps_str, "FPS: %04.0f", 1.0f/time.asSeconds());
                }// else text.setString("Waiting...");
                
                window.draw(text);
                window.display();
                //usleep(1000);
                clock.restart().asSeconds();
                //sf::sleep(sf::milliseconds(10));
            }
            exit(0);
        }
    }
    

    


    return 0;
}