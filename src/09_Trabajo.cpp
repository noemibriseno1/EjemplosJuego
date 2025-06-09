#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include <cmath>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Image");

    sf::Texture texture;
    if (!texture.loadFromFile("./assets/images/images.png"))
        return -1;

    sf::Sprite sprite(texture);
    sprite.setScale(0.9f, 0.9f);

    float spriteWidth = sprite.getLocalBounds().width * sprite.getScale().x;
    float spriteHeight = sprite.getLocalBounds().height * sprite.getScale().y;

    float posX = 0, posY = 0, velX = 0, velY = 0;

    std::mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    std::uniform_real_distribution<float> angleDist(0, 2 * 3.14159265f);

    auto setRandomDirection = [&]() {
        float angle = angleDist(rng);
        float speed = 0.03f; // velocidad ajustable
        velX = speed * std::cos(angle);
        velY = speed * std::sin(angle);
    };

    setRandomDirection();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        posX += velX;
        posY += velY;

        bool teleported = false;
        
        if (posX + spriteWidth < 0) 
        { 
            posX = 800;
            teleported = true; 
        }
        
        else if (posX > 800)       
        { 
            posX = -spriteWidth; 
            teleported = true; 
        }
        
        if (posY + spriteHeight < 0)
        { 
            posY = 600; 
            teleported = true; 
        }
        else if (posY > 600)        
        {
             posY = -spriteHeight; 
             teleported = true; 
        }
        if (teleported) 
        setRandomDirection();

        sprite.setPosition(posX, posY);

        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}
