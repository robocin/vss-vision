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

int frameRateLimit = 120;



Entities entities;
std::mutex mtx;
std::atomic<bool> Exit;
char fps_str[128];

int main()
{
    sf::Int32 frameId = 0;
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

    return 0;
}