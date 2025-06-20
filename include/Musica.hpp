#pragma once
#include <SFML/Audio.hpp>
#include <iostream>

class Musica {
public:
    Musica(const std::string& archivo) {
        if (!musica.openFromFile(archivo)) {
            std::cerr << "Error al cargar musica " << archivo << std::endl;
            exit(-1);
        }
    }

    void reproducir() {
        musica.setLoop(true);
        musica.play();
    }
    void detener() {
        musica.stop();
    }

private:
    sf::Music musica;
};


