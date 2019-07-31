#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <iostream>

int main()
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
    /*
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
    */

    

    while (true) {
        sf::Packet packet;
        port = oport;
        if (socket.receive(packet, sender, port) != sf::Socket::Done)
        {
            // error...
        }
        std::cout << "Received from " << sender << " on port " << port << std::endl;
        sf::Uint8 entitiesSize;
        if (packet >> entitiesSize) {
            std::cout << "entities : " << static_cast<int>(entitiesSize) << std::endl;
        } else {
            std::cout << "Error on retrieving data" << std::endl;
        }
    }

    return 0;
}
