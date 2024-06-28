#include <SFML/Graphics.hpp>
#include <iostream>

class Personaje
{
public:
    Personaje(sf::Vector2f position)
    {
        if (!texture.loadFromFile("./images/spritepacman.png"))
        {
            // Handle error
            std::cerr << "Error loading texture" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(2,1); // Initial sprite position
        sprite.scale(sf::Vector2f(0.75f, 0.75f));

        // Adjust the frame size based on the texture
        frameWidth = texture.getSize().x / numFrames;
        frameHeight = texture.getSize().y;
    }

    void move(float offsetX, float offsetY)
    {
        sprite.move(offsetX, offsetY);
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }

    void update()
    {
        // Update the animation frame
        if (clock.getElapsedTime().asSeconds() >= frameTime)
        {
            currentFrame = (currentFrame + 1) % numFrames;
            sprite.setTextureRect(sf::IntRect(currentFrame * frameWidth, 0, frameWidth, frameHeight));
            clock.restart();
        }
    }

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Clock clock;
    float frameTime = 0.2f; // Time between each frame in seconds
    int currentFrame = 0;
    int numFrames = 4; // Total number of frames in the animation
    int frameWidth;
    int frameHeight;
};

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pac-Man");

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
        pacman.draw(window);
        window.display();
    }

    return 0;
}

