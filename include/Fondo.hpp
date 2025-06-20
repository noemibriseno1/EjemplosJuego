#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include <Musica.hpp>
#include <CarroUno.hpp>
#include <CarroObstaculo.hpp>

class Fondo {
public:
    Fondo(const std::string& ruta) {
        if (!textura.loadFromFile(ruta)) {
            // Manejar el error si no se puede cargar la imagen
            std::cerr << "Error al cargar imagen " << ruta << std::endl;
            exit(-1);
        }
        sprite.setTexture(textura);
        sf::Vector2u tamañoOriginal = textura.getSize();
        float escalaX = 800.0f / tamañoOriginal.x;
        float escalaY = 600.0f / tamañoOriginal.y;
        sprite.setScale(escalaX, escalaY);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite); // o el objeto que uses para el fondo
    }

private:
    sf::Texture textura;
    sf::Sprite sprite;
};


