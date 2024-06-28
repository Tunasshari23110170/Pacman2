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
        sprite.setPosition(20,24);
        sprite.scale(sf::Vector2f(0.70f, 0.70f));

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