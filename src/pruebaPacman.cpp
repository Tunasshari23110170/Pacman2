#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Personaje.hpp"
#include "PantallaInicio.hpp"
#include "Puntuacion.hpp"
#include "Comestible.hpp"
#include "Fantasma.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pac-Man");

    PantallaInicio pantallaInicio("Pac-Man", "./images/Pacman.png", "./fonts/Brose.ttf");

    std::string nombreJugador = pantallaInicio.mostrar(window);

    if (nombreJugador.empty())
    {
        return 0; // Terminar el programa si no se proporciona un nombre
    }

    Personaje pacman(sf::Vector2f(250, 300));

    // Cargar imágenes de fondo
    sf::Texture fondoTexture1;
    if (!fondoTexture1.loadFromFile("./images/Mapa1.png"))
    {
        std::cerr << "Error al cargar la imagen de fondo" << std::endl;
        return 1;
    }

    sf::Sprite fondoSprite1(fondoTexture1);

    // Ajustar la escala del fondo para que se ajuste a la ventana
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = fondoTexture1.getSize();
    fondoSprite1.setScale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y
    );

    // Ajustar las posiciones de los fondos
    fondoSprite1.setPosition(0, 0);

    // Cargar el sonido de inicio
    sf::SoundBuffer buffer;
    if (!buffer.loadFromFile("./sounds/intro.wav"))
    {
        std::cerr << "Error al cargar el archivo de sonido" << std::endl;
        return 1;
    }
    sf::Sound startSound;
    startSound.setBuffer(buffer);
    startSound.play();

    // Crear la puntuación
    Puntuacion puntuacion;

    // Crear comestibles y ajustar posiciones
    std::vector<Comestible> comestibles;
    Comestible comestible1(0, 0, 1);
    comestible1.setPosition(200, 200);
    comestibles.push_back(comestible1);

    Comestible comestible2(0, 0, 1);
    comestible2.setPosition(400, 330);
    comestibles.push_back(comestible2);

    Comestible comestible3(0, 0, 1);
    comestible3.setPosition(260, 280);
    comestibles.push_back(comestible3);

    Comestible comestible4(0, 0, 1);
    comestible4.setPosition(530, 220);
    comestibles.push_back(comestible4);

    double velocidad = 100.0;

    sf::Clock deltaClock;

    // Crear fantasmas y ajustar posiciones y escalas
    std::vector<Fantasma> fantasmas;
    fantasmas.emplace_back(sf::Vector2f(100, 100));
    fantasmas.emplace_back(sf::Vector2f(700, 100));
    fantasmas.emplace_back(sf::Vector2f(100, 500));
    fantasmas.emplace_back(sf::Vector2f(700, 500));

    for (auto& fantasma : fantasmas)
    {
        fantasma.setScale(0.10f, 0.10f); // Ajustar la escala de los fantasmas
    }

    bool juegoEnCurso = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (juegoEnCurso)
        {
            sf::Time deltaTime = deltaClock.restart();

            // Control de movimiento invertido
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                pacman.move(velocidad * deltaTime.asSeconds(), 0); // Movimiento a la derecha
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                pacman.move(-velocidad * deltaTime.asSeconds(), 0); // Movimiento a la izquierda
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                pacman.move(0, velocidad * deltaTime.asSeconds()); // Movimiento hacia abajo
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                pacman.move(0, -velocidad * deltaTime.asSeconds()); // Movimiento hacia arriba
            }

            // Update Pac-Man animation
            pacman.update();

            // Verificar si Pac-Man ha comido algún comestible
            for (auto it = comestibles.begin(); it != comestibles.end();)
            {
                sf::FloatRect comestibleBounds(it->getX(), it->getY(), 20, 20); // Asume que el comestible es un círculo de 20x20
                if (pacman.getGlobalBounds().intersects(comestibleBounds))
                {
                    puntuacion.agregarPuntos(it->getPuntuacion());
                    it = comestibles.erase(it); // Eliminar el comestible comido
                }
                else
                {
                    ++it;
                }
            }

            // Mover fantasmas aleatoriamente
            for (auto& fantasma : fantasmas)
            {
                fantasma.moveRandomly(deltaTime);
            }

            // Verificar colisiones entre Pac-Man y fantasmas
            for (const auto& fantasma : fantasmas)
            {
                if (pacman.getGlobalBounds().intersects(fantasma.getGlobalBounds()))
                {
                    juegoEnCurso = false;
                    break;
                }
            }

            window.clear();

            // Dibujar los fondos
            window.draw(fondoSprite1);

            // Dibujar los comestibles
            for (const auto& comestible : comestibles)
            {
                sf::CircleShape shape(5); // Radio de 5
                shape.setFillColor(sf::Color::Red);
                shape.setPosition(comestible.getX(), comestible.getY());
                window.draw(shape);
            }

            // Dibujar los fantasmas
            for (const auto& fantasma : fantasmas)
            {
                fantasma.draw(window);
            }

            // Dibujar el personaje
            pacman.draw(window);

            // Mostrar la puntuación
            sf::Font font;
            if (!font.loadFromFile("./fonts/Brose.ttf"))
            {
                std::cerr << "Error al cargar la fuente" << std::endl;
                return 1;
            }

            sf::Text text;
            text.setFont(font);
            text.setString("Puntuacion: " + std::to_string(puntuacion.obtenerPuntuacion()));
            text.setCharacterSize(24);
            text.setFillColor(sf::Color::White);
            text.setPosition(10, 10);

            window.draw(text);

            // Verificar si se han comido todos los comestibles
            if (comestibles.empty())
            {
                // Mostrar el mensaje de victoria
                sf::Text winText;
                winText.setFont(font);
                winText.setString("GANASTE!");
                winText.setCharacterSize(72);
                winText.setFillColor(sf::Color::Yellow);
                winText.setPosition(200, 200);

                window.draw(winText);
            }

            // Verificar si ha perdido
            if (!juegoEnCurso)
            {
                sf::Text loseText;
                loseText.setFont(font);
                loseText.setString("PERDISTE!!");
                loseText.setCharacterSize(72);
                loseText.setFillColor(sf::Color::Red);
                loseText.setPosition(200, 200);

                window.draw(loseText);
            }

            window.display();
        }
    }

    return 0;
}




