#include <SFML/Graphics.hpp>
#include <iostream>
#include "tiletype.h"
#include "deal.h"


int main()
{
    shuffleDeal();
    /*
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "MahjongHK");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.display();
    }
    */
   return 0;
}
