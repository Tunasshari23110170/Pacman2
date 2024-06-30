#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Personaje.hpp"
#include "PantallaInicio.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pac-Man");

    PantallaInicio pantallaInicio("Pac-Man", "./images/Pacman.png", "./fonts/Brose.ttf");

    std::string nombreJugador = pantallaInicio.mostrar(window);

    if (nombreJugador.empty())
    {
        return 0; // Terminar el programa si no se proporciona un nombre
    }

    Personaje pacman(sf::Vector2f(500, 500));

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

        window.clear();
        
        // Dibujar los fondos
        window.draw(fondoSprite1);
        
        // Dibujar el personaje
        pacman.draw(window);

        window.display();
    }

    return 0;
}
