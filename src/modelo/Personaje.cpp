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

Personaje::Personaje(double anchoIn, double altoIn, double sprites_ancho, Vector2f posInicial, Posicionable* posc) :
    posicionInicial(posInicial), ancho(anchoIn), alto(altoIn), estado(EN_ESPERA), posicionable(posc), posicion(posInicial), tCreacion(0) {
	this->sprites_ancho = sprites_ancho;
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
	Vector2f P1(posicion.X(), posicion.Y() + getAlto());
	return VentanaGrafica::Instance()->calcularPosicionEnVentana(P1);
}

double Personaje::getSpritesAncho() const {
	return sprites_ancho;
}

void Personaje::centrar_en(Vector2f& v){
	this->posicionInicial = v;
	this->posicion = v;
}

void Personaje::caminarDerecha(){
    cout<<"Estado derecha"<<endl;
    setEstado(CAMINANDO_DERECHA);
    cambiarTrayectoria(new MRU(posicion, Vector2f(VELOCIDAD_DESP_HORIZONTAL, VELOCIDAD_NULA)));
    cout<<"seteo trayectoria"<<endl;
}

void Personaje::caminarIzquierda(){
    setEstado(CAMINANDO_IZQUIERDA);
    cambiarTrayectoria(new MRU(posicion, Vector2f(-VELOCIDAD_DESP_HORIZONTAL, VELOCIDAD_NULA)));
}

void Personaje::saltarVertical(){
    setEstado(SALTANDO_VERTICAL);
    cambiarTrayectoria(new MRUV(posicion, Vector2f(VELOCIDAD_NULA, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD));
}

void Personaje::saltarOblicuo(){
    setEstado(SALTANDO_OBLICUO);
    cambiarTrayectoria(new MRUV(posicion, Vector2f(VELOCIDAD_DESP_HORIZONTAL, VELOCIDAD_DESP_VERTICAL), VECTOR_GRAVEDAD));
}

void Personaje::mantenerReposo(){
    setEstado(EN_ESPERA);
    cambiarTrayectoria(new Reposo(posicion));
}

void Personaje::cambiarTrayectoria(Trayectoria* t) {
    delete trayectoria;
	this->trayectoria = t;
	this->tCreacion = ((float)(SDL_GetTicks()))/1000.0f; //TODO: Solo funciona en el caso particular de este video juego porque anda lo suficientemente rapido
}

void Personaje::agregarObservador(Observador* unObservador){
	Observable::agregarObservador(unObservador);
}

void Personaje::notificarObservadores(){
	cout<<"Entro a notificar"<<endl;

	Observable::notificarObservadores();
}

void Personaje::update(){
	cout<<"Update personaje"<<endl;

	// RECALCULA LA POSICION EN BASE AL OBJETO TRAYECTORIA
	float tActual = ((float)(SDL_GetTicks())/1000.0f) - tCreacion; //TODO: pasar a personaje
	Vector2f posicionCandidata = this->trayectoria->getPosicion(tActual); //TODO: Val. El personaje dibujable le setea la posicion a Sprite afuera
	if (posicionable->esValida(posicionCandidata) && posicionCandidata.Y() >= posicionInicial.Y()) {
        posicion = posicionCandidata;
    } else if (posicionCandidata.Y() >= posicionInicial.Y()) {
        estado = SALTANDO_VERTICAL;
        cambiarTrayectoria(new MRUV(posicion, VECTOR_VELOCIDAD_NULA, VECTOR_GRAVEDAD));
        posicion = trayectoria->getPosicion(tActual);
    } else if (posicion.Y() != posicionInicial.Y()){
        posicion = Vector2f(posicion.X(), posicionInicial.Y());
    } else {
        mantenerReposo();
    }
	notificarObservadores();
}

Personaje::~Personaje(){
    delete trayectoria;
}

bool Personaje::estaSaltando(){
    return (estado == SALTANDO_OBLICUO || estado == SALTANDO_VERTICAL);
}
/*
ostream& operator <<(ostream &o, const Personaje &p) {

        o<<"personaje -> [ancho, alto, zindex, sprites_imagen, sprites_ancho]=[";
        o<<p.ancho<<", "<<p.alto<<", "<<p.z_index<<", "<<p.sprites_imagen<<", "<<p.sprites_ancho<<"]";

        return o;
}*/

