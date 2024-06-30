#include <SFML/Graphics.hpp>
#include <iostream>

class ObjetoComible
{
public:
    ObjetoComible(const sf::Vector2f &position, const std::string &texturePath)
    {
        if (!texture.loadFromFile("./images/comida.png"))
        {
            std::cerr << "Error al cargar la textura del objeto comible" << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setPosition(position);
        sprite.setScale(0.1f, 0.1f); // Ajusta la escala según sea necesario
    }

    void draw(sf::RenderWindow &window)
    {
        window.draw(sprite);
    }

    sf::FloatRect getBounds() const
    {
        return sprite.getGlobalBounds();
    }

private:
    sf::Sprite sprite;
    sf::Texture texture;
};
