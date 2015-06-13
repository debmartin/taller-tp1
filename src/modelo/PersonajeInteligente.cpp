#include "PersonajeInteligente.h"

#define TURNO_MIN 0
#define TURNO_MAX 5

PersonajeInteligente::PersonajeInteligente(string id,
        double ancho,
        double alto,
        Vector2f posInicial,
        Posicionable* posc,
        int numJugador,
        map<estado_personaje, BVH*>* cajas_orientacion_derecha,
        DireccionObjeto orientacionInicialPersonaje) :
    Personaje(id, ancho, alto, posInicial, posc, numJugador, cajas_orientacion_derecha, orientacionInicialPersonaje),
    contadorAtaque(TURNO_MAX), contadorReposo(TURNO_MAX){
}

PersonajeInteligente::~PersonajeInteligente(){
    //dtor
}

void PersonajeInteligente::caminarHaciaEnemigo(Colisionable* enemigo) {
    if (estaCaminando())
        return;
    (enemigo->getPosicion().X() < posicion.X()) ? caminarIzquierda() : caminarDerecha();
}

void PersonajeInteligente::caminarLejosEnemigo(Colisionable* enemigo) {
    if (estaCaminando())
        return;
    (enemigo->getPosicion().X() < posicion.X()) ? caminarDerecha() : caminarIzquierda();
}

void PersonajeInteligente::calcularProximoMovimiento(Personaje* otro){
    if (estaBloqueado() || estaEnCaida()) return;

    if (contadorAtaque < TURNO_MAX){
        contadorAtaque++;
        return;
    } else if (contadorReposo < TURNO_MAX) {
        contadorReposo++;
        return;
    }
    if (estaAtacando()) {
        mantenerReposo();
        contadorReposo = TURNO_MIN;
        return;
    }
    bool otroEstaCerca = estaCerca(otro);
    contadorAtaque = TURNO_MIN;
    if (otroEstaCerca){
        otro->obtenerAntidoto(this);
    } else if (! estaCaminando()) {
        caminarHaciaEnemigo(otro);
    }
}

