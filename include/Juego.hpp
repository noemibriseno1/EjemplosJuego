#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <Fondo.hpp>
#include <CarroUno.hpp>
#include <CarroObstaculo.hpp>

class Juego {
public:
    Juego()
        :ventana(sf::VideoMode(800, 600), "Juego SFML"),
        jugador("./assets/images/carro.png", {73,500}),
        fondo("./assets/images/calle.png")
    {
        ventana.setFramerateLimit(60);
        obsVel = 2;
        generar = 0;
        puntaje = 0;
        pausado = false;
        if (!fuente.loadFromFile("./assets/fonts/FirstTimeWriting.ttf")) exit(-1);
        puntajeTexto.setFont(fuente);
        puntajeTexto.setCharacterSize(24);
        puntajeTexto.setFillColor(sf::Color::White);
        puntajeTexto.setPosition(100, 10);
        puntajeTexto.setString("Puntaje: 0");
        std::srand(std::time(0));

        // Carga la textura para los obstáculos
        if (!tileset.loadFromFile("assets/images/carroobstaculo.png")) {
            exit(-1);
        }
        // Carga la textura para el segundo obstáculo
        if (!tileset3.loadFromFile("assets/images/carro3.png")) {
            exit(-1);
        }
    }

    void run() {
        while (ventana.isOpen()) {
            sf::Event evento;
            while (ventana.pollEvent(evento)) {
                if (evento.type == sf::Event::Closed) {
                    ventana.close();
                }
            }

            if (!pausado) {
                manejarInput();
                generarObstaculos();
                moverObstaculos();
                contarPuntaje();
                eliminarObstaculos();
                checarColisiones();
                obsVel += 0.001f; // Aumentar la velocidad de los obstáculos
            } else {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    reiniciar();
                }
            }

            dibujar();
        }
    }

    private:
    sf::RenderWindow ventana;
    CarroUno jugador;
    Fondo fondo;
    std::vector<CarroObstaculo> obstaculos;
    std::vector<CarroObstaculo> obstaculos3; // <-- Nuevo vector para carro3
    sf::Texture tileset;
    sf::Texture tileset3; // <-- Textura para carro3
    float obsVel;
    float generar;
    int puntaje;
    bool pausado;
    sf::Font fuente;
    sf::Text puntajeTexto;
    void manejarInput() {
        float ancho = jugador.getAncho();
       
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
            jugador.move(-5.2f, 0);
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
            jugador.move(5.2f, 0);
        
        sf::Vector2f pos = jugador.getPosition();
        if (pos.x < 0) jugador.setPosition(0, pos.y);
        if (pos.x + ancho > 800) jugador.setPosition(800 - ancho, pos.y);

    }

    void generarObstaculos() {
        generar ++;
        if (generar > 100) {
            generar = 0;
            int espacioX = std::rand() % 700;
            sf::IntRect tileRect(0, 0, 50, 20);
            // Obstáculo 1
            for (int x =0; x < espacioX; x += 50) {
                obstaculos.emplace_back(tileset, tileRect, sf::Vector2f((float)x, 700));
            } 
            for (int x = espacioX + 50; x < 800; x += 50) {
                obstaculos.emplace_back(tileset, tileRect, sf::Vector2f((float)x, 700));
            }
            // Obstáculo 2 (carro3)
            int espacioX3 = std::rand() % 700;
            for (int x =0; x < espacioX3; x += 50) {
                obstaculos3.emplace_back(tileset3, tileRect, sf::Vector2f((float)x, 500));
            } 
            for (int x = espacioX3 + 50; x < 800; x += 50) {
                obstaculos3.emplace_back(tileset3, tileRect, sf::Vector2f((float)x, 500));
            }
        }
    }

    void moverObstaculos() {
        for (auto& obs : obstaculos) {
            obs.move(0, -obsVel);
        }
        for (auto& obs : obstaculos3) {
            obs.move(0, -obsVel - 1.5f); // carro3 más rápido
        }
    }
    void contarPuntaje() {
        for (auto& obs : obstaculos) {
            if (!obs.contado && obs.getX() == 0 && obs.getY() + 20 < jugador.getPosition().y) {
                puntaje++;
                obs.contado = true;
                puntajeTexto.setString("Puntaje: " + std::to_string(puntaje));
            }
        }
        
    }

    void eliminarObstaculos() {
        obstaculos.erase(std::remove_if(obstaculos.begin(), obstaculos.end(),
            [](const CarroObstaculo& obs) { return obs.getY() < -20; }), obstaculos.end());
        obstaculos3.erase(std::remove_if(obstaculos3.begin(), obstaculos3.end(),
            [](const CarroObstaculo& obs) { return obs.getY() < -20; }), obstaculos3.end());
    }
    void checarColisiones() {
        for (const auto& obs : obstaculos) {
            if (jugador.getGlobalBounds().intersects(obs.getGlobalBounds())) {
                pausado = true;
                break;
            }
        }
        for (const auto& obs : obstaculos3) {
            if (jugador.getGlobalBounds().intersects(obs.getGlobalBounds())) {
                pausado = true;
                break;
            }
        }
    }

    void reiniciar() {
        jugador.setPosition(385, 100);
        obstaculos.clear();
        obstaculos3.clear(); // Limpiar el vector de carro3
        obsVel = 2;
        generar = 0;
        puntaje = 0;
        pausado = false;
        puntajeTexto.setString("Puntaje: 0");
    }

    void dibujar() {
        ventana.clear();
        fondo.draw(ventana);
        jugador.draw(ventana);
        for (auto& obs : obstaculos) {
            obs.draw(ventana);
        }
        for (auto& obs : obstaculos3) {
            obs.draw(ventana);
        }
        ventana.draw(puntajeTexto);

        if (pausado) {
            sf::Text pausaTexto;
            pausaTexto.setFont(fuente);
            pausaTexto.setCharacterSize(50);
            pausaTexto.setFillColor(sf::Color::Red);
            pausaTexto.setString("Presiona Espacio para reiniciar");
            pausaTexto.setPosition(200, 250);
            ventana.draw(pausaTexto);
        }
        ventana.display();
    }
};



