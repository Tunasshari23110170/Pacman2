#include <SFML/Graphics.hpp>
#include <stdexcept>
class Pacman
{
private:
   sf::Texture imagen;
   sf::Sprite sprite;
   float velocidad;
public:
    Pacman() {
        if(!imagen.loadFromFile("./images/pacman1.png")){
            throw std::runtime_error("No se pudo cargar imagen");
        }
        velocidad = 0.1;
        sprite.setTexture(imagen);
        sprite.scale(sf::Vector2f(0.2f,0.2f));

    }
    ~Pacman() {}
    void MoveRight(){
        sprite.move(sf::Vector2f(velocidad,0));

    }
    void MoveLeft(){
        sprite.move(sf::Vector2f(velocidad*-1,0));
    }
    void MoveUp(){
        sprite.move(sf::Vector2f(0,0));
    }
    void MoveDown(){
        sprite.move(sf::Vector2f(0, velocidad));
    }
    void Draw(sf::RenderWindow &window){
        window.draw(sprite);
    }
  
};