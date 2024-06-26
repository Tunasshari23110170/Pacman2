#include "Comida.hpp"

Comida::Comida(float x, float y) {
    if (!texture.loadFromFile("comida.png")) {
        // Error handling
    }
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
}

void Comida::dibujar(sf::RenderWindow &ventana) {
    ventana.draw(sprite);
}

sf::FloatRect Comida::getBounds() const {
    return sprite.getGlobalBounds();
}
