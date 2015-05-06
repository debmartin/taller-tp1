/*
 * Personaje.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Personaje.h"

#include <SDL2/SDL_timer.h>
#include <sstream>

#include "../utils/Logger.h"
#include "../vista/VentanaGrafica.h"
#include "MRU.h"
#include "MRUV.h"
#include "Reposo.h"

#define VELOCIDAD_DESP_HORIZONTAL_SALTANDO 320.0f
#define VELOCIDAD_DESP_HORIZONTAL_CAMINANDO 215.0f
#define VELOCIDAD_DESP_VERTICAL 1120.0f
#define VELOCIDAD_NULA 0.0f
#define VECTOR_VELOCIDAD_NULA Vector2f(0, 0)
#define VECTOR_GRAVEDAD Vector2f(0, -2600.f)

Personaje::Personaje() {
	this->ancho = 0;
	this->alto = 0;
	this->energia = ENERGIA_INICIAL;
}

Personaje::Personaje(string idIn, double anchoIn, double altoIn, Vector2f posInicial, Posicionable* posc, int numJugador) :
    id(idIn), posicionInicial(posInicial), ancho(anchoIn), alto(altoIn), estado(EN_ESPERA), posicionable(posc),
	posicion(posInicial), tCreacion(0), numeroJugador(numJugador){
	this->trayectoria = new Reposo(this->posicion);
	this->energia = ENERGIA_INICIAL;
}

double Personaje::getAlto() const {
	return alto;
}

double Personaje::getAncho() const {
	return ancho;
}

int Personaje::getNumeroJugador(){
	return numeroJugador;
}

Vector2f Personaje::getDimensionesLogicas() const {
	return Vector2f(this->getAncho(), this->getAlto());
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

int Personaje::getEnergia(){
	return this->energia;
}

void Personaje::agregarArma(Objeto* unArma){
	this->arma = unArma;
}

Objeto* Personaje::getArma(){
	return arma;
}

//Devuelve un vector posicion referenciado desde el eje con origen de coordenadas arriba izquierda.
Vector2f Personaje::obtenerPosicionEnVentana(){
	Vector2f P1(posicion.X(), posicion.Y() + getAlto());
	Vector2f P2 = VentanaGrafica::Instance()->calcularPosicionEnVentana(P1);
	return P2;
}

bool Personaje::llegoAlLimiteIzquierdo(){
	return VentanaGrafica::Instance()->llegoAlLimiteIzquierdo(this->posicion.X()-this->getAncho()*0.05);
}

bool Personaje::llegoAlLimiteDerecho(){
	return VentanaGrafica::Instance()->llegoAlLimiteDerecho(Vector2f(this->posicion.X()+this->getAncho()*1.05,this->posicion.Y()));
}

void Personaje::centrar_en(Vector2f& v){
	this->posicion = v;
}

void Personaje::caminarDerecha(){
    Trayectoria* nuevaTray;
    if (llegoAlLimiteDerecho()) {
        nuevaTray = new Reposo(posicion);
    } else {
        nuevaTray = new MRU(posicion, Vector2f(VELOCIDAD_DESP_HORIZONTAL_CAMINANDO, VELOCIDAD_NULA));
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
        nuevaTray = new MRU(posicion, Vector2f(-VELOCIDAD_DESP_HORIZONTAL_CAMINANDO, VELOCIDAD_NULA));
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
    cambiarTrayectoria(new MRUV(posicion, Vector2f(VELOCIDAD_DESP_HORIZONTAL_SALTANDO, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD));
    Logger::getInstance()->debug("Personaje: salto oblicuo derecha. Se setea trayectoria.");
}

void Personaje::saltarOblicuoIzquierda(){
    setEstado(SALTANDO_OBLICUO_IZQUIERDA);
    cambiarTrayectoria(new MRUV(posicion, Vector2f(-VELOCIDAD_DESP_HORIZONTAL_SALTANDO, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD));
    Logger::getInstance()->debug("Personaje: salto oblicuo izquierda. Se setea trayectoria.");
}

void Personaje::agacharse(){
    setEstado(AGACHADO);
    cambiarTrayectoria(new Reposo(posicion));
    recibirDanio(10);
    Logger::getInstance()->debug("Personaje: agachado.");
}

void Personaje::golpeAlto(){
	setEstado(GOLPEANDO_ALTO);
	cambiarTrayectoria(new Reposo(posicion));
	Logger::getInstance()->debug("Personaje: golpe alto.");
}

void Personaje::golpeBajo(){
	setEstado(GOLPEANDO_BAJO);
	cambiarTrayectoria(new Reposo(posicion));
	Logger::getInstance()->debug("Personaje: golpe bajo.");
}

void Personaje::patada(){
	setEstado(PATEANDO);
	cambiarTrayectoria(new Reposo(posicion));
	Logger::getInstance()->debug("Personaje: patada.");
}

/*Patada alta ocurre cuando el personaje está saltando*/
void Personaje::patadaAlta(){
	setEstado(PATEANDO_ALTO);
	Logger::getInstance()->debug("Personaje: patada alta.");
}

void Personaje::patadaBaja(){
	setEstado(PATEANDO_BAJO);
	cambiarTrayectoria(new Reposo(posicion));
	Logger::getInstance()->debug("Personaje: patada baja.");
}

void Personaje::defender(){
	setEstado(DEFENDIENDO);
	cambiarTrayectoria(new Reposo(posicion));
	Logger::getInstance()->debug("Personaje: defensa.");
}

void Personaje::defender_agachado(){
	setEstado(DEFENDIENDO_AGACHADO);
	cambiarTrayectoria(new Reposo(posicion));
	Logger::getInstance()->debug("Personaje: defensa.");
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

void Personaje::update(Vector2f posicionObjetivo){
	Logger::getInstance()->debug("Personaje: update.");

	arma->update();
	//float miPosicionX =this->posicion.X();

	// RECALCULA LA POSICION EN BASE AL OBJETO TRAYECTORIA
	float tActual = ((float)(SDL_GetTicks())/1000.0f) - tCreacion;
	Vector2f posicionCandidata = this->trayectoria->getPosicion(tActual);

	float distanciaAObjetivo = posicionCandidata.X() - posicionObjetivo.X();
	if (distanciaAObjetivo < 0) distanciaAObjetivo = -distanciaAObjetivo;

	if (posicionable->esValida(posicionCandidata, ancho) && posicionCandidata.Y() >= posicionInicial.Y()) {
		if (! posicionable->enExtremos(distanciaAObjetivo, ancho))
            posicion = posicionCandidata;
	} else if (posicionCandidata.Y() < posicionInicial.Y()) {
        posicion = Vector2f(posicionCandidata.X(), posicionInicial.Y());
        mantenerReposo();
    } else if (posicionCandidata.Y() > posicionInicial.Y()) {
    	Vector2f velocActual = this->trayectoria->getVelocidad(tActual);
        cambiarTrayectoria(new MRUV(posicion, Vector2f(0.0f, velocActual.Y()), VECTOR_GRAVEDAD));
    } else {
        mantenerReposo();
    }
	/*
	if(llegoAlLimiteIzquierdo() || llegoAlLimiteDerecho()){
		this->estaEnLimite = true;
	}else{
		this->estaEnLimite = false;
	}*/

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

void Personaje::arrojarArma(){
	//Posiciono el poder respecto a la posicion del personaje
	Vector2f posicionObjeto(posicion.X()+ancho,alto);
	arma->posicionar(posicionObjeto);
	arma->cambiarEstado(VISIBLE);
}

void Personaje::recibirDanio(int danio){
	this->energia -= danio;
}

ostream& operator <<(ostream &o, const Personaje &p) {

        o<<"Personaje -> [ancho, alto, posInicial]=["<<p.ancho<<", "<<p.alto<<", "<<p.posicionInicial<<"]";
        return o;
}

Personaje& Personaje::operator=(const Personaje& p) {

	posicionInicial = p.posicionInicial;
	ancho = p.ancho;
	alto = p.alto;
	posicion = p.posicion;
	posicionable = p.posicionable; // TODO ver de no copiar la referencia
	z_index = p.z_index;
	energia = p.energia;
	arma = p.arma; // TODO ver de no copiar la referencia
	estado = p.estado;
	trayectoria = p.trayectoria; // TODO ver de no copiar la referencia
	tCreacion = p.tCreacion;

	return *this;
}

string Personaje::getId() const {
	return id;
}

string Personaje::toString() {
    ostringstream stream;
    stream <<*this;
	return stream.str();
}
