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
	this->velocidad.setCoordenada(0,0);

}

Personaje::Personaje(double ancho, double alto, Posicionable* limites, double sprites_ancho){
	this->ancho = ancho;
	this->alto = alto;
	this->sprites_ancho = sprites_ancho;
	this->limites = limites;
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

void Personaje::setEstado(int unEstado){
	this->estado = unEstado;
}

int Personaje::getEstado(){
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
	float alto_mundo = this->limites->getLimitesLogicos().getAltoLogico();
	Vector2f P2(this->posicion.X(), alto_mundo - P1.Y());
	return P2;
}

double Personaje::getSpritesAncho() const {
	return sprites_ancho;
}

void Personaje::setTrayectoria(Trayectoria* t) {
	this->trayectoria = t;
	this->tCreacion = ((float)(SDL_GetTicks()))/1000.0f; //TODO: Solo funciona en el caso particular de este video juego porque anda lo suficientemente rapido
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

