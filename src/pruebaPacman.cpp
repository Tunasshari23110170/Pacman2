#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <PantallaInicio.hpp>
#include <Personaje.hpp> 

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pac-Man");

    // Load background textures
    sf::Texture backgroundTexture1; //carga el mapa 1
    if (!backgroundTexture1.loadFromFile("./images/map1.png"))
    {
        // Handle error
        std::cerr << "Error loading background texture 1" << std::endl;
    }

    sf::Texture backgroundTexture2; //mapa 2
    if (!backgroundTexture2.loadFromFile("./images/map2.png"))
    {
        // Handle error
        std::cerr << "Error loading background texture 2" << std::endl;
    }

    sf::Texture backgroundTexture3; //mapa 3
    if (!backgroundTexture3.loadFromFile("./images/map3.png"))
    {
        // Handle error
        std::cerr << "Error loading background texture 3" << std::endl;
    }
    
    sf::Texture backgroundTexture4; //mapa 4
    if (!backgroundTexture4.loadFromFile("./images/map4.png"))
    {
        // Handle error
        std::cerr << "Error loading background texture 4" << std::endl;
    }

    // Create background sprites
    sf::Sprite backgroundSprite1;
    backgroundSprite1.setTexture(backgroundTexture1);
    backgroundSprite1.setScale(0.9f, 0.9f); // Scale the first background

    sf::Sprite backgroundSprite2;
    backgroundSprite2.setTexture(backgroundTexture2);
    backgroundSprite2.setPosition(0, 0); // Position the second background next to the first one
    backgroundSprite2.setScale(0.9f, 0.9f); // Scale the second background
    
    sf::Sprite backgroundSprite3;
    backgroundSprite3.setTexture(backgroundTexture3);
    backgroundSprite3.setPosition(0, 0); 
    backgroundSprite3.setScale(0.9f, 0.9f); 
    
    sf::Sprite backgroundSprite4;
    backgroundSprite4.setTexture(backgroundTexture4);
    backgroundSprite4.setPosition(0, 0); // Position the fourth background next to the first one
    backgroundSprite4.setScale(0.9f, 0.9f); // Scale the fourth background

    // Load background music
    sf::Music backgroundMusic;
    if (!backgroundMusic.openFromFile("./sounds/intro.wav"))
    {
        // Handle error
        std::cerr << "Error loading background music" << std::endl;
    }
    backgroundMusic.setLoop(true); // Set the music to loop
    backgroundMusic.play(); // Play the music

    Personaje pacman(sf::Vector2f(500, 500));

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
        window.draw(backgroundSprite1); // Draw the first background
        window.draw(backgroundSprite2); // Draw the second background
        window.draw(backgroundSprite3); // Draw the third background
        window.draw(backgroundSprite4); // Draw the fourth background
        pacman.draw(window); // Draw Pac-Man
        window.display();
    }

    return 0;
}

