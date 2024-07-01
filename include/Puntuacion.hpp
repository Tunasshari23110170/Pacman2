#include <iostream>

class Puntuacion {
private:
    int puntuacion;  // Puntuación actual del jugador

public:
    // Constructor
    Puntuacion() : puntuacion(0) {}

    // Método para añadir puntos
    void agregarPuntos(int puntos) {
        puntuacion += puntos;
    }

    // Método para obtener la puntuación actual
    int obtenerPuntuacion() const {
        return puntuacion;
    }

    // Método para restablecer la puntuación
    void restablecer() {
        puntuacion = 0;
    }

    // Método para mostrar la puntuación en la consola
    void mostrar() const {
        std::cout << "Puntuación actual: " << puntuacion << std::endl;
    }
};

