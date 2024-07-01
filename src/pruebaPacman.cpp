#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include "Personaje.hpp"
#include "PantallaInicio.hpp"
#include "Puntuacion.hpp"
#include "Comestible.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pac-Man");

    PantallaInicio pantallaInicio("Pac-Man", "./images/Pacman.png", "./fonts/Brose.ttf");

    std::string nombreJugador = pantallaInicio.mostrar(window);

    if (nombreJugador.empty())
    {
        return 0; // Terminar el programa si no se proporciona un nombre
    }

    Personaje pacman(sf::Vector2f(200, 300));

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
    Comestible comestible1(0, 0, 100);
    comestible1.setPosition(200, 200);
    comestibles.push_back(comestible1);

    Comestible comestible2(0, 0, 200);
    comestible2.setPosition(400, 400);
    comestibles.push_back(comestible2);

    Comestible comestible3(0, 0, 200);
    comestible3.setPosition(300, 300);
    comestibles.push_back(comestible3);

    Comestible comestible4(0, 0, 200);
    comestible4.setPosition(600, 600);
    comestibles.push_back(comestible4);

    double velocidad = 100.0;

    sf::Clock deltaClock;

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

        sf::Time deltaTime = deltaClock.restart();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            pacman.move(-velocidad * deltaTime.asSeconds(), 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            pacman.move(velocidad * deltaTime.asSeconds(), 0);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            pacman.move(0, -velocidad * deltaTime.asSeconds());
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            pacman.move(0, velocidad * deltaTime.asSeconds());
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

        window.display();
    }

    return 0;
}
