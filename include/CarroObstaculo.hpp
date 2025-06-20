#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <Musica.hpp>
#include <CarroUno.hpp>
#include <Fondo.hpp>

class CarroObstaculo {
public:
    CarroObstaculo(sf::Texture& tileset, sf::IntRect tileRect, sf::Vector2f posicion) 
        : contado(false)
    {
        sprite.setTexture(tileset);
        sprite.setTextureRect(tileRect);
        sprite.setPosition(posicion);
    }
    void move(float x, float y) {
        sprite.move(x, y);
    }
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
    sf::FloatRect getGlobalBounds() const {
        return sprite.getGlobalBounds();
    }
    float getX() const {
        return sprite.getPosition().x;
    }
    float getY() const {
        return sprite.getPosition().y;
    }
    bool contado;

private:
    
    sf::Sprite sprite;
};


        
