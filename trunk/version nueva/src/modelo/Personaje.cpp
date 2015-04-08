/*
 * Personaje.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Personaje.h"

Personaje::Personaje() {
	this->ancho = 0;
	this->alto = 0;
}

Personaje::Personaje(double ancho, double alto, double sprites_ancho, Vector2f posInicial){
	this->ancho = ancho;
	this->alto = alto;
	this->sprites_ancho = sprites_ancho;
	this->estado = EN_ESPERA;
	//this->limites = limites;
	this->posicion = posInicial;
	this->trayectoria = new Reposo(this->posicion);
	this->tCreacion = 0;
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

	Vector2f P1(this->posicion.X(), this->posicion.Y() + getAlto());

	float alto_mundo = VentanaGrafica::Instance()->getLimitesLogicos().getAltoLogico();
	cout<<"Calcule coordenadas de ventana"<<endl;
	Vector2f P2(this->posicion.X(), alto_mundo - P1.Y());

	return P2;
}

double Personaje::getSpritesAncho() const {
	return sprites_ancho;
}

void Personaje::mover(Movimiento unMovimiento){
	switch(unMovimiento){
		case REPOSO:
			setEstado(EN_ESPERA);
			setTrayectoria(new Reposo(getPosicion()));
			cout<<"seteo trayectoria"<<endl;

			break;
		case CAMINAR_DERECHA:
			cout<<"Estado derecha"<<endl;
			setEstado(CAMINANDO_DERECHA);
			setTrayectoria(new MRU(getPosicion(), Vector2f(180.0f, 0.0f)));
			cout<<"seteo trayectoria"<<endl;

			break;
		case CAMINAR_IZQUIERDA:
			setEstado(CAMINANDO_IZQUIERDA);
			setTrayectoria(new MRU(getPosicion(), Vector2f(-180.0f, 0.0f)));
			break;
		case SALTAR_VERTICAL:
			setEstado(SALTANDO_VERTICAL);
			setTrayectoria(new MRUV(getPosicion(), Vector2f(0,800.0f), Vector2f(0,-1600.0f)));
			break;
	}
}

void Personaje::setTrayectoria(Trayectoria* t) {
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
	this->posicion = this->trayectoria->getPosicion(tActual); //TODO: Val. El personaje dibujable le setea la posicion a Sprite afuera
	notificarObservadores();
}

Personaje::~Personaje(){
	// TODO Auto-generated destructor stub
}

/*
ostream& operator <<(ostream &o, const Personaje &p) {

        o<<"personaje -> [ancho, alto, zindex, sprites_imagen, sprites_ancho]=[";
        o<<p.ancho<<", "<<p.alto<<", "<<p.z_index<<", "<<p.sprites_imagen<<", "<<p.sprites_ancho<<"]";

        return o;
}*/

