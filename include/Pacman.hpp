#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Vida.hpp"

class Pacman {
private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::SoundBuffer bufferComer;
    sf::Sound sonidoComer;
    Vida vida;
    int puntuacion;
public:
    Pacman();
    void mover(sf::Keyboard::Key key);
    void dibujar(sf::RenderWindow &ventana);
    void comer();
    int getPuntuacion() const;
    sf::FloatRect getBounds() const;
};

