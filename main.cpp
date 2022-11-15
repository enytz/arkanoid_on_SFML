//#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Window.h"

int main()
{
    Game game;
    while (game.IsRunning())
    {
        game.Update();
        game.LateUpdate();
        game.Draw();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }
    /*
    sf::RenderWindow window(sf::VideoMode(800,600),"SFML sadf");
    sf::CircleShape shape (100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    
    window.clear();
    window.draw(shape);
    window.display();
    }*/
    return 0;
}