#include <SFML/Graphics.hpp>
#include <chipmunk/chipmunk.h>
#include <GameWindow.hpp>
#include <PhysicsSpace.hpp>
#include <Ground.hpp>
#include <Ball.hpp>


int main()
{
    GameWindow window(800, 600, "Juego de Pelotitas");
    PhysicsSpace physicsSpace;
    Suelo ground(physicsSpace.getSpace());
    Ball ball(physicsSpace.getSpace(), 20.0, 1.0, cpv(400, 300));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        cpSpaceStep(physicsSpace.getSpace(), 1.0 / 120.0);

        window.clear();

        // Dibujar Piso
        sf::RectangleShape groundShape(sf::Vector2f(800, 100));
        groundShape.setPosition(0, 500);
        groundShape.setFillColor(sf::Color::Green);
        window.draw(groundShape);

        // Dibujar Pelotita
        int x = window.getSize().x / 2;
        int y = window.getSize().y / 2;

        sf::CircleShape ballShape(20.0);
        cpVect ballPosition = cpBodyGetPosition(ball.getBody());
        ballShape.setPosition(ballPosition.x, ballPosition.y);
        ballShape.setFillColor(sf::Color::Red);
        window.draw(ballShape);

        window.display();
    }

    return 0;
}
