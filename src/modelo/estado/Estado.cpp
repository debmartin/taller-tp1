#include "Estado.h"
#include <SDL2/SDL_timer.h>

Estado::Estado(Trayectoria* trayectoriaInicial, estado_personaje id, BVH* caja) :
    trayectoria(trayectoriaInicial), ataqueEstado(NULL),
    tCreacion(((float)(SDL_GetTicks()))/1000.0f), id(id), cajas(caja), ataqueEfectuado(false) {
    Vector2f posInicial = trayectoria->getPosicion(0);
    caja->setPosicion(posInicial);
 //   cout<<"******Cajas********"<<endl;
 //   cout<<*caja<<endl;
 //   cout<<"******************"<<endl;
}

Estado::Estado(Trayectoria* trayectoriaInicial, float tiempoCreacion, estado_personaje id, BVH* caja) :
    trayectoria(trayectoriaInicial), ataqueEstado(NULL),
    tCreacion(tiempoCreacion), id(id), cajas(caja) {
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

bool Estado::estaSaltandoVertical(){
    return false;
}

bool Estado::estaSaltandoDiagonalDerecha(){
    return false;
}

bool Estado::estaSaltandoDiagonalIzquierda(){
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

bool Estado::estaCaminando(){
    return false;
}

bool Estado::estaEnCaida(){
    return false;
}

bool Estado::estaGolpeado(){
    return false;
}

bool Estado::estaGolpeando(){
    return false;
}

bool Estado::estaEnPiso(){
	return false;
}

bool Estado::ejecutandoMovimientoEspecial(){
    return false;
}

bool Estado::efectuandoGancho(){
    return false;
}

Vector2f Estado::obtenerProximaPosicion(){
    return trayectoria->getPosicion(obtenerTiempoActual());
}

void Estado::actualizar(Vector2f nuevaPosicion){
    //Vector2f posInicial = cajas->calcularPosicion();
    //cajas->desplazarBVH(nuevaPosicion - posInicial);
	Vector2f posInicial = cajas->getPivote();
	cajas->desplazarBVH(nuevaPosicion - posInicial);
}

Vector2f Estado::obtenerVelocidad(){
    return trayectoria->getVelocidad(obtenerTiempoActual());
}

float Estado::obtenerTiempoActual(){
    return ((float)(SDL_GetTicks())/1000.0f) - tCreacion;
}

float Estado::obtenerTiempoDeCreacion(){
	return tCreacion;
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

void Estado::reducirVelocidad(){
    Vector2f velocidadActual = trayectoria->getVelocidad(obtenerTiempoActual());
    Vector2f velocidadNueva(velocidadActual.X()/2.0, velocidadActual.Y());
    trayectoria->reducirVelocidad(velocidadNueva);
}

double Estado::calcularAncho() {
    return cajas->calcularAnchoEnvolvente();
}

double Estado::calcularAlto() {
    return cajas->calcularAltoEnvolvente();
}

void Estado::efectuarAtaque() {
    ataqueEfectuado = true;
}

bool Estado::ataqueFueEfectuado() {
    return ataqueEfectuado;
}
