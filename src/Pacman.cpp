#include <SFML/Graphics.hpp>
#include "Pacman.hpp"

Pacman::pacman() : vida(3), puntuacion(0) {
    if (!texture.loadFromFile("pacman.png")) {
        // Error handling
    }
    sprite.setTexture(texture);
    sprite.setPosition(100, 100);

    // Cargar el sonido de inicio
    if (!bufferInicio.loadFromFile("intro.wav")) {
        // Error handling
    }
    sonidoInicio.setBuffer(bufferInicio);
}

void pacman::mover(sf::Keyboard::Key key) {
    switch (key) {
        case sf::Keyboard::Left:
            sprite.move(-10, 0);
            break;
        case sf::Keyboard::Right:
            sprite.move(10, 0);
            break;
        case sf::Keyboard::Up:
            sprite.move(0, -10);
            break;
        case sf::Keyboard::Down:
            sprite.move(0, 10);
            break;
        default:
            break;
    }
}

void pacman::draw(sf::RenderWindow &ventana) {
    ventana.draw(sprite);
}


int pacman::getPuntuacion() const {
    return puntuacion;
}

sf::FloatRect pacman::getBounds() const {
    return sprite.getGlobalBounds();
}
