#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

// Función para mostrar la pantalla de inicio
std::string mostrarPantallaInicio(sf::RenderWindow &window, sf::Font &font)
{
    // Cargar la imagen de bienvenida
    sf::Texture texture;
    if (!texture.loadFromFile("./images/Pacman.png"))
    {
        std::cerr << "Error al cargar la imagen de bienvenida" << std::endl;
    }
    sf::Sprite sprite(texture);

    // Ajustar la posición del sprite de la imagen de bienvenida
    sprite.setPosition(300, 400);
    sprite.scale(.5,.5); 

    // Configurar el texto de bienvenida
    sf::Text textoBienvenida("Bienvenido a Pac-Man", font, 35);
    textoBienvenida.setFillColor(sf::Color::Red);
    textoBienvenida.setPosition(100, 100);

    sf::Text textoNombre("Ingrese su nombre: ", font, 30);
    textoNombre.setFillColor(sf::Color::Blue);
    textoNombre.setPosition(100, 180);

    sf::Text textoInstrucciones("Presione Enter para comenzar", font, 20);
    textoInstrucciones.setFillColor(sf::Color::Yellow);
    textoInstrucciones.setPosition(100, 350);

    std::string nombreJugador;
    sf::Text textoNombreJugador("", font, 30);
    textoNombreJugador.setFillColor(sf::Color::Blue);
    textoNombreJugador.setPosition(200, 250);

    // Bucle de la pantalla de inicio
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode == '\b') // Borrar carácter con la tecla Backspace
                {
                    if (!nombreJugador.empty())
                    {
                        nombreJugador.pop_back();
                    }
                }
                else if (event.text.unicode < 128) // Aceptar solo caracteres ASCII
                {
                    nombreJugador += static_cast<char>(event.text.unicode);
                }
                textoNombreJugador.setString(nombreJugador);
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter && !nombreJugador.empty())
                {
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

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Pac-Man");

    // Cargar la fuente desde un archivo
    sf::Font font;
    if (!font.loadFromFile("./fonts/Brose.ttf"))
    {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return 1; // Salir del programa si no se puede cargar la fuente
    }

    std::string nombreJugador = mostrarPantallaInicio(window, font);

    if (nombreJugador.empty())
    {
        return 0; // Terminar el programa si no se proporciona un nombre
    }

    // Aquí iría el resto del código del juego
    // Crear una instancia del personaje Pac-Man en la posición (400, 300)
   

    return 0;
}
