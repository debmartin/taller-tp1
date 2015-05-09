#include "Estado.h"
#include <SDL2/SDL_timer.h>

Estado::Estado(Trayectoria* trayectoriaInicial, estado_personaje id, BVH* caja) :
    trayectoria(trayectoriaInicial), ataqueEstado(NULL),
    tCreacion(((float)(SDL_GetTicks()))/1000.0f), id(id), cajas(caja) {
    //ctor
}

Estado::~Estado() {
    delete trayectoria;
}

Ataque* Estado::obtenerAtaque(){
    return ataqueEstado;
}

bool Estado::estaAtacando(){
    return false;
}

bool Estado::estaDefendiendo(){
    return false;
}

bool Estado::estaSaltando(){
    return false;
}

bool Estado::estaAgachado(){
    return false;
}

bool Estado::estaEsperando(){
    return false;
}

bool Estado::estaBloqueado(){
    return false;
}

bool Estado::ejecutandoMovimientoEspecial(){
    return false;
}

Vector2f Estado::obtenerProximaPosicion(){
    float tActual = ((float)(SDL_GetTicks())/1000.0f) - tCreacion;
    return trayectoria->getPosicion(tActual);
}

Vector2f Estado::obtenerVelocidad(){
    float tActual = ((float)(SDL_GetTicks())/1000.0f) - tCreacion;
    return trayectoria->getVelocidad(tActual);
}

estado_personaje Estado::Id(){
    return id;
}

bool Estado::haySuperposicion(BVH* otraCaja) {
    if (!cajas || !otraCaja) return false;
    return cajas->interseccion(otraCaja);
}

BVH* Estado::obtenerCajaColision(){
    return cajas;
}

void Estado::agregarCajaColision(BVH* cajaColision){
    cajas = cajaColision;
}

Trayectoria* Estado::getTrayectoria(){
    return trayectoria;
}

