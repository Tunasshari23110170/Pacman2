#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Pacman.hpp"
#include "Comida.hpp"
#include "Puntuacion.hpp"

int main() {
    sf::RenderWindow ventana(sf::VideoMode(800, 600), "Pac-Man");

    Pacman pacman;
    Puntuacion puntuacion;
    std::vector<Comida> comidas = {
        Comida(200, 200),
        Comida(300, 300),
        Comida(400, 400)
    };

    while (ventana.isOpen()) {
        sf::Event evento;
        while (ventana.pollEvent(evento)) {
            if (evento.type == sf::Event::Closed)
                ventana.close();

            if (evento.type == sf::Event::KeyPressed) {
                pacman.mover(evento.key.code);
            }
        }

        // Comprobar colisiones
        for (auto it = comidas.begin(); it != comidas.end();) {
            if (pacman.getBounds().intersects(it->getBounds())) {
                pacman.comer();
                puntuacion.incrementar(10);
                it = comidas.erase(it);
            } else {
                ++it;
            }
        }

        ventana.clear();
        pacman.dibujar(ventana);
        for (auto &comida : comidas) {
            comida.dibujar(ventana);
        }
        puntuacion.dibujar(ventana);
        ventana.display();
    }

    return 0;
}


