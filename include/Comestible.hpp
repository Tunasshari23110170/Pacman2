#include <iostream>

class Comestible {
private:
    int x;  // Coordenada X del comestible
    int y;  // Coordenada Y del comestible
    int puntuacion;  // Puntuación que da el comestible al ser comido

public:
    // Constructor
    Comestible(int x, int y, int puntuacion) : x(x), y(y), puntuacion(puntuacion) {}

    // Métodos getters
    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    int getPuntuacion() const {
        return puntuacion;
    }
    void setPosition(float newX, float newY)
    {
        x = newX;
        y = newY;
    }

    // Método para verificar si el comestible está en una posición dada
    bool estaEnPosicion(int x, int y) const {
        return this->x == x && this->y == y;
    }

    // Método para dibujar el comestible en la consola (esto es solo un ejemplo)
    void dibujar() const {
        std::cout << "Comestible en (" << x << ", " << y << ") con puntuacion: " << puntuacion << std::endl;
    }
};

