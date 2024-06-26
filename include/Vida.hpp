#include "Vida.hpp"

Vida::Vida(int v) : vidas(v) {}

void Vida::perderVida() {
    if (vidas > 0) vidas--;
}

void Vida::ganarVida() {
    vidas++;
}

int Vida::getVidas() const {
    return vidas;
}
