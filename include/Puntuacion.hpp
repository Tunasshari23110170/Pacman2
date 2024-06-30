#include <iostream>
#include "Puntuacion.hpp"

Puntuacion::Puntuacion() : puntuacion(0) {
    if (!font.loadFromFile("Browse.ttf")) {
        // Error handling
    }
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Blue);
    text.setPosition(10, 10);
}

void Puntuacion::incrementar(int puntos) {
    puntuacion += puntos;
    text.setString("tu puntuacion es: " + std::to_string(puntuacion));
}

void Puntuacion::dibujar(sf::RenderWindow &ventana) {
    ventana.draw(text);
}
