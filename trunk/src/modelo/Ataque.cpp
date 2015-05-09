#include "Ataque.h"

Ataque::Ataque(int danioAtaque) :
    danio(danioAtaque) {
}

Ataque::~Ataque(){
}

int Ataque::obtenerDanio(){
    return danio;
}
