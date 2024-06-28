#include <SFML/Graphics.hpp>
#include <Fantasma.hpp>

int main(int argc, char const *argv[])
{
    Fantasma fantasma;

    // Crear una ventana de SFML
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

    // Crear una forma circular de SFML
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Verificar si se ha cerrado la ventana
            if (event.type == sf::Event::Closed)
                window.close();
        }

        fantasma.MoveDown();

        // Limpiar la ventana
        window.clear();

        fantasma.Draw(window);

        // Mostrar la ventana
        window.display();
    }

    return 0;
}
//kk