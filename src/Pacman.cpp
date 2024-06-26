#include "Pacman.h"

Pacman::Pacman() : vida(3), puntuacion(0) {
    if (!texture.loadFromFile("pacman.png")) {
        // Error handling
    }
    sprite.setTexture(texture);
    sprite.setPosition(100, 100);

    // Cargar el sonido de comer
    if (!bufferComer.loadFromFile("comer.wav")) {
        // Error handling
    }
    sonidoComer.setBuffer(bufferComer);
}

void Pacman::mover(sf::Keyboard::Key key) {
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

void Pacman::dibujar(sf::RenderWindow &ventana) {
    ventana.draw(sprite);
}

void Pacman::comer() {
    puntuacion += 10;
    sonidoComer.play();
}

int Pacman::getPuntuacion() const {
    return puntuacion;
}

sf::FloatRect Pacman::getBounds() const {
    return sprite.getGlobalBounds();
}
