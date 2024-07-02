#include <cstdlib> // Para std::rand
#include <ctime>   // Para std::time
#include <SFML/Graphics.hpp>

class Fantasma {
public:
    Fantasma(const sf::Vector2f& position);
    void moveRandomly(sf::Time deltaTime);
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getGlobalBounds() const;

    void setScale(float scaleX, float scaleY); // Agregar método para establecer la escala

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f velocity;
};

Fantasma::Fantasma(const sf::Vector2f& position) {
    if (!texture.loadFromFile("./images/spritefantasma.png")) {
        // Handle error
    }
    sprite.setTexture(texture);
    sprite.setPosition(position);
    velocity = sf::Vector2f((std::rand() % 200) - 100, (std::rand() % 200) - 100);
}

void Fantasma::moveRandomly(sf::Time deltaTime) {
    // Mover el fantasma aleatoriamente en ambas direcciones
    sf::Vector2f movement(velocity.x * deltaTime.asSeconds(), velocity.y * deltaTime.asSeconds());
    sprite.move(movement);

    // Cambiar dirección si se llega a los bordes de la ventana (800x600)
    sf::Vector2f position = sprite.getPosition();
    if (position.x < 0 || position.x > 800) {
        velocity.x = -velocity.x;
    }
    if (position.y < 0 || position.y > 600) {
        velocity.y = -velocity.y;
    }
}

void Fantasma::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

sf::FloatRect Fantasma::getGlobalBounds() const {
    return sprite.getGlobalBounds();
}

void Fantasma::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}


