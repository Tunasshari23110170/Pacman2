#include <SFML/Graphics.hpp>
#include <Pacman.hpp>


int main(int argc, char const *argv[])
{
    Pacman pacman;

    // Crear una ventana de SFML
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
        }

        pacman.MoveDown();

        window.clear();

        pacman.Draw(window);

        window.display();
    }

    return 0;
}
