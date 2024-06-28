#include <SFML/Graphics.hpp>
#include <iostream>

class Fantasma {
public:
    Fantasma(sf::Vector2f position) {
        if (!texture.loadFromFile("./images/spritefantasma.png")) {
            std::cerr << "Error loading texture" << std::endl;
        } else {
            sprite.setTexture(texture);
            sprite.setPosition(position);
            sprite.setScale(sf::Vector2f(0.25f, 0.25f)); // Ajusta el tamaño del sprite
        }
    }

    void move(float offsetX, float offsetY) {
        sprite.move(offsetX, offsetY);
    }

    void draw(sf::RenderWindow &window) {
        window.draw(sprite);
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Fantasma");

    Fantasma fantasma(sf::Vector2f(100, 100));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            fantasma.move(-0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            fantasma.move(0.1f, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            fantasma.move(0.0f, -0.1f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            fantasma.move(0.0f, 0.1f);
        }

        window.clear();
        fantasma.draw(window);
        window.display();
    }

    return 0;
}