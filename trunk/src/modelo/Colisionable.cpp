#include "Colisionable.h"

Colisionable::Colisionable(Vector2f posicionIn, double anchoIn, double altoIn) :
    posicion(posicionIn), posicionCandidata(posicionIn), ataqueActual(NULL), estaColisionando(false), ancho(anchoIn), alto(anchoIn) {
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

bool Colisionable::vaAColisionar(Colisionable* otro){
    return (((posicionAnterior.X() + ancho/2 < otro->posicion.X() && posicionCandidata.X() + ancho/2 >= otro->posicion.X()) ||
             (posicionAnterior.X() > otro->posicion.X() + otro->ancho/2 && posicionCandidata.X() <= otro->posicion.X() + otro->ancho/2)) &&
             (posicionCandidata.Y() <= otro->posicion.Y() + otro->alto));


}
