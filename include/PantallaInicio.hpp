#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp> 

class PantallaInicio {
public:
     {
        // Cargar la imagen de bienvenida
        if (!texture.loadFromFile("./images/Pacman.png")) {
            std::cerr << "Error al cargar la imagen de bienvenida" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(300, 400);
        sprite.scale(0.5f, 0.5f);

        // Configurar el texto de bienvenida
        textoBienvenida.setString("Bienvenido a Pac-Man");
        textoBienvenida.setFont(font);
        textoBienvenida.setCharacterSize(35);
        textoBienvenida.setFillColor(sf::Color::Red);
        textoBienvenida.setPosition(100, 100);

        textoNombre.setString("Ingrese su nombre: ");
        textoNombre.setFont(font);
        textoNombre.setCharacterSize(30);
        textoNombre.setFillColor(sf::Color::Blue);
        textoNombre.setPosition(100, 180);

        textoInstrucciones.setString("Presione Enter para comenzar");
        textoInstrucciones.setFont(font);
        textoInstrucciones.setCharacterSize(20);
        textoInstrucciones.setFillColor(sf::Color::Yellow);
        textoInstrucciones.setPosition(100, 350);

        textoNombreJugador.setFont(font);
        textoNombreJugador.setCharacterSize(30);
        textoNombreJugador.setFillColor(sf::Color::Blue);
        textoNombreJugador.setPosition(200, 250);
    }

    std::string mostrarPantallaInicio() {
        std::string nombreJugador;

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                } else if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode == '\b') { // Borrar carácter con la tecla Backspace
                        if (!nombreJugador.empty()) {
                            nombreJugador.pop_back();
                        }
                    } else if (event.text.unicode < 128) { // Aceptar solo caracteres ASCII
                        nombreJugador += static_cast<char>(event.text.unicode);
                    }
                    textoNombreJugador.setString(nombreJugador);
                } else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter && !nombreJugador.empty()) {
                        return nombreJugador; // Iniciar el juego cuando se presione Enter
                    }
                }
            }

            window.clear();
            window.draw(sprite); // Dibujar la imagen de bienvenida en la nueva posición
            window.draw(textoBienvenida);
            window.draw(textoNombre);
            window.draw(textoInstrucciones);
            window.draw(textoNombreJugador);
            window.display();
        }

        return ""; // En caso de que la ventana se cierre sin iniciar el juego
    }

private:
    sf::RenderWindow& window;
    sf::Font& font;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Text textoBienvenida;
    sf::Text textoNombre;
    sf::Text textoInstrucciones;
    sf::Text textoNombreJugador;
};

