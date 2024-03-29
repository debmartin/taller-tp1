#include "Colisionable.h"

Colisionable::Colisionable(Vector2f posicionIn, double anchoIn, double altoIn) :
    posicion(posicionIn), posicionCandidata(posicionIn), ataqueActual(NULL),
    estaColisionando(false), ancho(anchoIn), alto(anchoIn), estaArrastrando(false) {
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

int Colisionable::obtenerDanio(){
    if (! ataqueActual) return 0;
    return ataqueActual->obtenerDanio();
}

Vector2f Colisionable::getPosicion(){
    return posicion;
}

//Vector2f Colisionable::getPivote(){
//    return this->obtenerCajaColision()->getPivote();
//}

bool Colisionable::vaAColisionar(Colisionable* otro, double anchoAct, double altoAct){
	ancho = anchoAct;
	alto = anchoAct;
    int miMitadAncho = ancho/2.0, otroMitadAncho = otro->ancho/2.0;
    return (((posicionAnterior.X() < otro->posicion.X() && posicionCandidata.X() >= otro->posicion.X()) ||
             (posicionAnterior.X() > otro->posicion.X() && posicionCandidata.X() <= otro->posicion.X())) &&
             (posicionCandidata.Y() <= otro->posicion.Y() + otro->alto && posicionCandidata.Y() >= otro->posicion.Y()));
}

double Colisionable::getAlto(){
    return alto;
}

double Colisionable::getAncho(){
    return ancho;
}

bool Colisionable::estaInhabilitado(){
    return false;
}

bool Colisionable::ejecutandoMovimientoEspecial(){
    return false;
}
