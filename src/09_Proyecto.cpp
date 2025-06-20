#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>

int main() {
    // Configuración de ventana
    sf::RenderWindow window(sf::VideoMode(300, 600), "Juego del Carro Loco");
    window.setFramerateLimit(60);

    // Fondo
    sf::Texture fondoTexture;
    if (!fondoTexture.loadFromFile("assets/images/calle.png")) return -1;
    sf::Sprite fondoSprite1(fondoTexture);
    sf::Sprite fondoSprite2(fondoTexture);
    sf::Sprite fondoSprite3(fondoTexture);

    sf::Vector2u fondoSize = fondoTexture.getSize();
    fondoSprite1.setScale(
        float(window.getSize().x) / fondoSize.x,
        float(window.getSize().y) / fondoSize.y
    );
    fondoSprite2.setScale(
        float(window.getSize().x) / fondoSize.x,
        float(window.getSize().y) / fondoSize.y
    );
    fondoSprite3.setScale(
        float(window.getSize().x) / fondoSize.x,
        float(window.getSize().y) / fondoSize.y
    );

    // Carro del jugador (sin fondo)
    sf::Texture carroTexture;
    if (!carroTexture.loadFromFile("assets/images/carro.png")) return -1;
    carroTexture.setSmooth(true);
    carroTexture.setRepeated(false);
    carroTexture.setSrgb(true);
    sf::Sprite carroSprite(carroTexture);
    carroSprite.setScale(0.5f, 0.5f);
    carroSprite.setPosition(73 + 30, 500); // +30 pixeles a la derecha

    // Carro obstáculo 1 (sin fondo)
    sf::Texture obstaculoTexture;
    if (!obstaculoTexture.loadFromFile("assets/images/carroobstaculo.png")) return -1;
    obstaculoTexture.setSmooth(true);
    obstaculoTexture.setRepeated(false);
    obstaculoTexture.setSrgb(true);
    sf::Sprite obstaculoSprite(obstaculoTexture);
    obstaculoSprite.setScale(0.5f, 0.5f);
    obstaculoSprite.setPosition(73 + 30, -40);

    // Carro obstáculo 2 (carro3.png)
    sf::Texture carro3Texture;
    if (!carro3Texture.loadFromFile("assets/images/carro3.png")) return -1;
    carro3Texture.setSmooth(true);
    carro3Texture.setRepeated(false);
    carro3Texture.setSrgb(true);
    sf::Sprite carro3Sprite(carro3Texture);
    carro3Sprite.setScale(0.5f, 0.5f);
    carro3Sprite.setPosition(87 + 30, -300); // Sale más arriba para alternar

    // Música de fondo
    sf::Music musica;
    if (!musica.openFromFile("assets/music/dark_horse_2.ogg")) return -1;
    musica.setLoop(true);

    // Fuente y texto para puntaje y mensajes
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/FirstTimeWriting.ttf")) return -1;
    sf::Text puntajeText("Puntaje: 0", font, 24);
    puntajeText.setFillColor(sf::Color::White);
    puntajeText.setPosition(10, 10);
    puntajeText.setOutlineColor(sf::Color::Black);
    puntajeText.setOutlineThickness(4);

    sf::Text mensajeInicio("Bienvenido al Juego del Carro \nPresione Espacio para iniciar", font, 24);
    mensajeInicio.setFillColor(sf::Color::Green);
    mensajeInicio.setOutlineColor(sf::Color::Black);
    mensajeInicio.setOutlineThickness(4);
    mensajeInicio.setPosition(0, 250);

    int puntaje = 0;
    bool jugando = false;
    bool gameOver = false;
    float velocidadObstaculo = 6.0f;
    float velocidadObstaculo3 = 6.0f;
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // Variables para el fondo en movimiento
    float fondoY1 = 0.0f;
    float fondoY2 = -float(window.getSize().y);
    float velocidadFondo = 2.0f;

    // Posiciones posibles para los obstáculos en X (+30 pixeles)
    std::vector<float> posicionesX = {73 + 30, 87 + 30, 100 + 30, 113 + 30};

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Pantalla de inicio
        if (!jugando && !gameOver) {
            window.clear();
            // Fondo en movimiento suave (scroll infinito)
            fondoY1 += velocidadFondo;
            fondoY2 += velocidadFondo;
            if (fondoY1 >= window.getSize().y) fondoY1 = fondoY2 - window.getSize().y;
            if (fondoY2 >= window.getSize().y) fondoY2 = fondoY1 - window.getSize().y;
            fondoSprite1.setPosition(0, fondoY1);
            fondoSprite2.setPosition(0, fondoY2);
            window.draw(fondoSprite1);
            window.draw(fondoSprite2);
            window.draw(mensajeInicio);
            window.display();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                jugando = true;
                musica.play();
                puntaje = 0;
                puntajeText.setString("Puntaje: 0");
                carroSprite.setPosition(73 + 30, 500);
                obstaculoSprite.setPosition(73 + 30, -40);
                carro3Sprite.setPosition(87 + 30, -300);
                velocidadObstaculo = 6.0f;
                velocidadObstaculo3 = 6.0f;
                fondoY1 = 0.0f;
                fondoY2 = -float(window.getSize().y);
            }
            continue;
        }

        // Lógica de juego
        if (jugando && !gameOver) {
            // Fondo en movimiento suave (scroll infinito)
            fondoY1 += velocidadFondo;
            fondoY2 += velocidadFondo;
            if (fondoY1 >= window.getSize().y) fondoY1 = fondoY2 - window.getSize().y;
            if (fondoY2 >= window.getSize().y) fondoY2 = fondoY1 - window.getSize().y;

            // Movimiento del jugador solo en X entre 73+30 y 113+30
            float x = carroSprite.getPosition().x;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && x > 73 + 30)
                carroSprite.move(-2.5f, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && x < 113 + 30)
                carroSprite.move(2.5f, 0);

            // Limita la posición exacta para que no se pase del rango
            if (carroSprite.getPosition().x < 73 + 30)
                carroSprite.setPosition(73 + 30, carroSprite.getPosition().y);
            if (carroSprite.getPosition().x > 113 + 30)
                carroSprite.setPosition(113 + 30, carroSprite.getPosition().y);

            // Movimiento de los obstáculos solo en Y
            obstaculoSprite.move(0, velocidadObstaculo);
            carro3Sprite.move(0, velocidadObstaculo3);

            // Si el obstáculo 1 sale de la ventana, reposición y suma puntos
            if (obstaculoSprite.getPosition().y > 600) {
                float nuevaX = posicionesX[std::rand() % posicionesX.size()];
                obstaculoSprite.setPosition(nuevaX, -40);
                puntaje += 2;
                puntajeText.setString("Puntaje: " + std::to_string(puntaje));
                velocidadObstaculo += 0.2f;
            }
            // Si el obstáculo 2 sale de la ventana, reposición y suma puntos
            if (carro3Sprite.getPosition().y > 600) {
                float nuevaX = posicionesX[std::rand() % posicionesX.size()];
                carro3Sprite.setPosition(nuevaX, -40);
                puntaje += 2;
                puntajeText.setString("Puntaje: " + std::to_string(puntaje));
                velocidadObstaculo3 += 0.2f;
            }

            // Colisión
            if (carroSprite.getGlobalBounds().intersects(obstaculoSprite.getGlobalBounds()) ||
                carroSprite.getGlobalBounds().intersects(carro3Sprite.getGlobalBounds())) {
                jugando = false;
                gameOver = true;
                musica.stop();
            }
        }

        // Dibujo
        window.clear();
        fondoSprite1.setPosition(0, fondoY1);
        fondoSprite2.setPosition(0, fondoY2);
        window.draw(fondoSprite1);
        window.draw(fondoSprite2);

        window.draw(carroSprite);
        window.draw(obstaculoSprite);
        window.draw(carro3Sprite);
        window.draw(puntajeText);

        if (gameOver) {
            sf::Text fin("GAME OVER\nPresione espacio para reiniciar", font, 24);
            fin.setFillColor(sf::Color::Red);
            fin.setOutlineColor(sf::Color::Black);
            fin.setOutlineThickness(4);
            fin.setPosition(20, 250);
            window.draw(fin);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                gameOver = false;
                jugando = false;
                velocidadObstaculo = 6.0f;
                velocidadObstaculo3 = 6.0f;
                fondoY1 = 0.0f;
                fondoY2 = -float(window.getSize().y);
            }
        }

        window.display();
    }
    return 0;
}