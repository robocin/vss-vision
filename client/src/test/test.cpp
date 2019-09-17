#include <SFML/Main.hpp>
#include <iostream>
#include <vector>
#include <mutex>
#include <atomic>
#include <omp.h>
#include <unistd.h>
#include <math.h>
#include "Network.hpp"

#define RAD_TO_DEG 180.0/M_PI

#define APP_NAME "test"

Entities entities;
std::mutex mtx;
std::atomic<bool> Exit;

int manyEntities = 22;
int waitTime = 10;

int messages_to_send = 1000;

int main()
{
    sf::Int32 frameId = 0;

    sf::Clock clock;
    sf::Time time;
    time = clock.getElapsedTime();

    entities.resize(manyEntities);
    for(int i=0; i < entities.size(); ++i) {
        entities[i].id() = i;
    }

    sf::sleep(sf::seconds(2));
    while (!Exit)
    {
        if (frameId < messages_to_send) {
            Network::sendFrame(entities);
            time = clock.getElapsedTime();
            clock.restart().asSeconds();
            sf::sleep(sf::milliseconds(waitTime));
            ++frameId;
        } else Exit = true;
    }

    return 0;
}