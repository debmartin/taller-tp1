#include "Colisionable.h"

Colisionable::Colisionable(Vector2f posicionIn) :
    posicion(posicionIn), posicionCandidata(posicionIn), ataqueActual(NULL), estaColisionando(false) {
}

Colisionable::~Colisionable() {
}

void Colisionable::colisionar(Colisionable* otro){
    if (estaColisionando)
        return;
    estaColisionando = true;
    otro->colisionar(this);
    estaColisionando = false;
}

Ataque* Colisionable::obtenerAtaque(){
    return ataqueActual;
}

Vector2f Colisionable::getPosicion(){
    return posicion;
}
