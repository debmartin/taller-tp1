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

Vector2f Colisionable::getPivote(){
    return this->obtenerCajaColision()->getPivote();
}

bool Colisionable::vaAColisionar(Colisionable* otro, double anchoAct, double altoAct){
	ancho = anchoAct;
	alto = anchoAct;
//    cout << posicion.X() << "," << posicionCandidata.X() << "," << posicionAnterior.X()<<endl;
    return (((posicionAnterior.X() + ancho < otro->posicion.X() && posicionCandidata.X() + ancho >= otro->posicion.X()) ||
             (posicionAnterior.X() > otro->posicion.X() + otro->ancho && posicionCandidata.X() <= otro->posicion.X() + otro->ancho)) &&
             (posicionCandidata.Y() <= otro->posicion.Y() + otro->alto));
}

