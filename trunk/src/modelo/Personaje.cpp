/*
 * Personaje.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Personaje.h"

#define VELOCIDAD_DESP_HORIZONTAL 180.0f
#define VELOCIDAD_DESP_VERTICAL 800.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_VELOCIDAD_NULA Vector2f(0, 0)
#define VECTOR_GRAVEDAD Vector2f(0, -1600.f)

Personaje::Personaje() {
	this->ancho = 0;
	this->alto = 0;
}

Personaje::Personaje(double anchoIn, double altoIn, Vector2f posInicial, Posicionable* posc) :
    posicionInicial(posInicial), ancho(anchoIn), alto(altoIn), estado(EN_ESPERA), posicionable(posc), posicion(posInicial), tCreacion(0){
	this->trayectoria = new Reposo(this->posicion);
}

double Personaje::getAlto() const {
	return alto;
}

double Personaje::getAncho() const {
	return ancho;
}

void Personaje::setPosicion(int x, int y) {
	this->posicion.setCoordenada(x,y);
}

Vector2f Personaje::getPosicion(){
	return this->posicion;
}

void Personaje::setEstado(estado_personaje unEstado){
	this->estado = unEstado;
}

estado_personaje Personaje::getEstado(){
	return this->estado;
}

void Personaje::setVida(int cantidad){
	this->vida += cantidad;
}

int Personaje::getVida(){
	return this->vida;
}

//Devuelve un vector posicion referenciado desde el eje con origen de coordenadas arriba izquierda.
Vector2f Personaje::obtenerPosicionEnVentana(){
	//la cuenta que se hizo:
	//getAlto()-posicion.Y() = altoEscenario - [ y_piso + ( altoEscenario - altoPersonaje) ]
	Vector2f P1(posicion.X(), this->getAlto()-posicion.Y());
	return VentanaGrafica::Instance()->calcularPosicionEnVentana(P1);
}

bool Personaje::llegoAlLimiteIzquierdo(){
	return VentanaGrafica::Instance()->llegoAlLimiteIzquierdo(this->posicion);
}

bool Personaje::llegoAlLimiteDerecho(){
	return VentanaGrafica::Instance()->llegoAlLimiteDerecho(this->posicion);
}

void Personaje::centrar_en(Vector2f& v){
	this->posicion = v;
}

void Personaje::caminarDerecha(){
    Trayectoria* nuevaTray;
    if (llegoAlLimiteDerecho()) {
        nuevaTray = new Reposo(posicion);
    } else {
        nuevaTray = new MRU(posicion, Vector2f(VELOCIDAD_DESP_HORIZONTAL, VELOCIDAD_NULA));
    }

    setEstado(CAMINANDO_DERECHA);
    cambiarTrayectoria(nuevaTray);
    Logger::getInstance()->debug("Personaje: caminando derecha. Se setea trayectoria.");
}

void Personaje::caminarIzquierda(){
    Trayectoria* nuevaTray;
    if (llegoAlLimiteIzquierdo()) {
        nuevaTray = new Reposo(posicion);
    } else {
        nuevaTray = new MRU(posicion, Vector2f(-VELOCIDAD_DESP_HORIZONTAL, VELOCIDAD_NULA));
    }

    setEstado(CAMINANDO_IZQUIERDA);
    cambiarTrayectoria(nuevaTray);
    Logger::getInstance()->debug("Personaje: caminando izquierda. Se setea trayectoria.");
}

void Personaje::saltarVertical(){
    setEstado(SALTANDO_VERTICAL);
    cambiarTrayectoria(new MRUV(posicion, Vector2f(VELOCIDAD_NULA, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD));
    Logger::getInstance()->debug("Personaje: salto vertical. Se setea trayectoria.");
}

void Personaje::saltarOblicuoDerecha(){
    setEstado(SALTANDO_OBLICUO_DERECHA);
    cambiarTrayectoria(new MRUV(posicion, Vector2f(VELOCIDAD_DESP_HORIZONTAL, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD));
    Logger::getInstance()->debug("Personaje: salto oblicuo derecha. Se setea trayectoria.");
}

void Personaje::saltarOblicuoIzquierda(){
    setEstado(SALTANDO_OBLICUO_IZQUIERDA);
    cambiarTrayectoria(new MRUV(posicion, Vector2f(-VELOCIDAD_DESP_HORIZONTAL, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD));
    Logger::getInstance()->debug("Personaje: salto oblicuo izquierda. Se setea trayectoria.");
}

void Personaje::saltarOblicuoIzquierdaEnLimite(){
	setEstado(SALTANDO_OBLICUO_IZQUIERDA);
	cambiarTrayectoria(new MRUV(posicion, Vector2f(VELOCIDAD_NULA, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD));
}

void Personaje::saltarOblicuoDerechaEnLimite(){
	setEstado(SALTANDO_OBLICUO_DERECHA);
    cambiarTrayectoria(new MRUV(posicion, Vector2f(VELOCIDAD_NULA, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD));
	posicionSalto = posicion;
}

void Personaje::agacharse(){
    setEstado(AGACHADO);
    cambiarTrayectoria(new Reposo(posicion));
    Logger::getInstance()->debug("Personaje: agachado.");
}

void Personaje::mantenerReposo(){
    setEstado(EN_ESPERA);
    cambiarTrayectoria(new Reposo(posicion));
    Logger::getInstance()->debug("Personaje: en reposo.");
}

void Personaje::cambiarTrayectoria(Trayectoria* t) {
    delete trayectoria;
	this->trayectoria = t;
	this->tCreacion = ((float)(SDL_GetTicks()))/1000.0f;
}

void Personaje::agregarObservador(Observador* unObservador){
	Observable::agregarObservador(unObservador);
}

void Personaje::notificarObservadores(){
	Observable::notificarObservadores();
}

void Personaje::update(){
	Logger::getInstance()->debug("Personaje: update.");

	// RECALCULA LA POSICION EN BASE AL OBJETO TRAYECTORIA
	float tActual = ((float)(SDL_GetTicks())/1000.0f) - tCreacion;
	Vector2f posicionCandidata = this->trayectoria->getPosicion(tActual);
	if (posicionable->esValida(posicionCandidata, ancho) && posicionCandidata.Y() >= posicionInicial.Y()) {
        posicion = posicionCandidata;
	} else if (posicionCandidata.Y() < posicionInicial.Y()) {
        Logger::getInstance()->debug("entra a igual");
        posicion = Vector2f(posicionCandidata.X(), posicionInicial.Y());
        mantenerReposo();
    } else if (posicionCandidata.Y() > posicionInicial.Y()) {
        cambiarTrayectoria(new MRUV(posicion, VECTOR_VELOCIDAD_NULA, VECTOR_GRAVEDAD));
    } else {
        mantenerReposo();
    }
	notificarObservadores();
}

Personaje::~Personaje(){
    delete trayectoria;
}

bool Personaje::estaSaltando(){
    return (estado == SALTANDO_OBLICUO_DERECHA || estado == SALTANDO_OBLICUO_IZQUIERDA || estado == SALTANDO_VERTICAL);
}

bool Personaje::estaAgachado(){
    return (estado == AGACHADO);
}

bool Personaje::estaEnReposo(){
    return (estado == EN_ESPERA);
}
