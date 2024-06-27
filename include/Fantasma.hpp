#include <SFML/Graphics.hpp>

class Fantasma
{
private:
    sf::Texture imagen;
    sf::Sprite sprite;
    float velocidad;
public:
    Fantasma() {
        imagen.loadFromFile("./images/fantasma.png");
        velocidad = 0.1;
        sprite.setTexture(imagen);
        sprite.scale(sf::Vector2f(0.25f, 0.25f));
    }
    ~Fantasma() {}
    void MoveRight(){
        sprite.move(sf::Vector2f(velocidad, 0));
    }
    void MoveLeft(){
        sprite.move(sf::Vector2f(velocidad*-1, 0));
    }
    void MoveUp(){
        sprite.move(sf::Vector2f(0, 0));
    }
    void MoveDown(){
        sprite.move(sf::Vector2f(0, velocidad));
    }
    void Draw(sf::RenderWindow &window){
        window.draw(sprite);
    }


};
//hola 