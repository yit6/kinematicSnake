#include<SFML/Graphics.hpp>
#include<math.h>

#include"main.hpp"

int main()
{
    float speed = 5;

    sf::RenderWindow window(sf::VideoMode(800,800, 32), "first",sf::Style::Titlebar | sf::Style::Close);

    sf::CircleShape player;
    player.setRadius(5);
    player.setOrigin(sf::Vector2f(5,5));
    player.setPosition(sf::Vector2f(400,400));
    player.setFillColor(sf::Color::Red);

    sf::Vector2f playerSpeed(0,0);

    sf::VertexArray lines(sf::LineStrip, bodyLength);

    for (int i = 1; i < bodyLength; i++) {
        lines[i].position=sf::Vector2f(0,i);
    }
    lines[0].position=player.getPosition();

    window.setVerticalSyncEnabled(true);
    while(window.isOpen())
     {
         sf::Event event;
         while(window.pollEvent(event))
         {
             if ((event.type == sf::Event::Closed) ||
               ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
            {
                window.close();
                break;
            }
         }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            playerSpeed = sf::Vector2f(0,-speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            playerSpeed = sf::Vector2f(0,speed);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            playerSpeed = sf::Vector2f(-speed,0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            playerSpeed = sf::Vector2f(speed,0);
        }

        player.move(playerSpeed);

        lines[0].position = player.getPosition();
        for (int i = 1; i < bodyLength; i++) {
            lines[i].position = attach(lines[i-1].position,lines[i].position);
        }
        //lines[1].position = attach(lines[0].position,lines[1].position);

        window.clear(sf::Color(0,0,0));

        window.draw(lines);

        window.draw(player);

        window.display();
     }
    return 0;
}

sf::Vector2f attach(sf::Vector2f head, sf::Vector2f tail)
{
    float ang = atan2((head-tail).y,(head-tail).x);
    return sf::Vector2f(head.x-bodyResolution*cos(ang),head.y-bodyResolution*sin(ang));
}