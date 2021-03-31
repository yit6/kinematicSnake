#include<SFML/Graphics.hpp>
#include<stdlib.h>
#include<math.h>

#include"main.hpp"

int main()
{
    float speed = 5;
    bool reachedMouse = false;
    float bodyResolution = 1;
    float bodyLength = 200;
    bool gameIsOver = false;
    float newSegments = 100;

    sf::RenderWindow window(sf::VideoMode(800,800, 32), "Kinematic Snake",sf::Style::Default);

    sf::CircleShape apple;
    apple.setRadius(10);
    apple.setFillColor(sf::Color::Red);
    apple.setPosition(rand()%800,rand()%800);
    apple.setOrigin(10,10);

    sf::CircleShape player;
    player.setRadius(5);
    player.setOrigin(sf::Vector2f(5,5));
    player.setPosition(sf::Vector2f(400,400));
    player.setFillColor(sf::Color::Green);

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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (!reachedMouse)
            {
                playerSpeed = window.mapPixelToCoords(sf::Mouse::getPosition(window))-player.getPosition();
                float mag = sqrt(playerSpeed.x*playerSpeed.x + playerSpeed.y*playerSpeed.y);
                playerSpeed *= speed;
                if (mag < speed)
                {
                    reachedMouse = true;
                }
                playerSpeed /= mag;
            }
        }
        else
        {
            reachedMouse = false;
        }

        player.move(playerSpeed);
        for (int i = 0; i < bodyLength; i++)
        {
            if (distance(lines[i].position,apple.getPosition()) < 10)
            {
                apple.setPosition(rand()%800,rand()%800);
                sf::Vector2f end = lines[bodyLength-1].position;
                for (int i = 0; i < newSegments; i++)
                {
                    lines.append(end);
                }
                bodyLength+=newSegments;
                break;
            }
        }

        for (int i = 20; i < bodyLength; i++) {
            if (distance(lines[i].position,lines[0].position) < 5)
            {
                gameIsOver = true;
            }
        }

        if (player.getPosition().x < 0 || player.getPosition().x > 800 || player.getPosition().y > 800 || player.getPosition().y < 0)
        {
            gameIsOver = true;
        }

        lines[0].position = player.getPosition();
        for (int i = 1; i < bodyLength; i++) {
            lines[i].position = attach(lines[i-1].position,lines[i].position,bodyResolution);
        }
        //lines[1].position = attach(lines[0].position,lines[1].position);

        window.clear(sf::Color(0,0,0));

        window.draw(lines);

        window.draw(player);

        window.draw(apple);

        window.display();

        if (gameIsOver)
        {
            window.close();
        }
     }
    return 0;
}

sf::Vector2f attach(sf::Vector2f head, sf::Vector2f tail,float length)
{
    float ang = atan2((head-tail).y,(head-tail).x);
    return sf::Vector2f(head.x-length*cos(ang),head.y-length*sin(ang));
}

float distance(sf::Vector2f A, sf::Vector2f B)
{
    sf::Vector2f dist = A-B;
    return sqrt(dist.x*dist.x + dist.y*dist.y);
}