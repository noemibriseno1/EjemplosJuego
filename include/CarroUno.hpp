#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <Musica.hpp>
#include <Fondo.hpp>
#include <CarroObstaculo.hpp>

class CarroUno {
public:
    CarroUno(const std::string& rutaDer, const std::string& rutaIzq, sf::Vector2f posicion) {
        if (!texturaDer.loadFromFile(rutaDer)) {
            std::cerr << "Error al cargar imagen " << rutaDer << std::endl;
            exit(-1);
        }
        if (!texturaIzq.loadFromFile(rutaIzq)) {
            std::cerr << "Error al cargar imagen " << rutaIzq << std::endl;
            exit(-1);
        }
        sprite.setTexture(texturaDer);
        sprite.setPosition(posicion);
        mirandoDerecha = true;
    }
    void mover(float x, float y) {
        sprite.move(x, y);
        if (x < 0 && mirandoDerecha) {
            sprite.setTexture(texturaIzq);
            mirandoDerecha = false;
        } else if (x > 0 && !mirandoDerecha) {
            sprite.setTexture(texturaDer);
            mirandoDerecha = true;
        }
    }

    void move(float dx, float dy) {
        sprite.move(dx, dy);
    }

    void setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }
    sf::FloatRect getGlobalBounds() const {
        return sprite.getGlobalBounds();
    }
    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }
    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }
    float getAncho() const {
        return sprite.getGlobalBounds().width;
    }
    

private:
    sf::Texture texturaDer;
    sf::Sprite sprite;
    sf::Texture texturaIzq;
    bool mirandoDerecha;

};


