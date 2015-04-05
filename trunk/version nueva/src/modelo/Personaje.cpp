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

Personaje::Personaje(double ancho, double alto,
		Posicionable* limites, double sprites_ancho)
{
	this->ancho = ancho;
	this->alto = alto;
	this->sprites_ancho = sprites_ancho;
	this->limites = limites;
}

double Personaje::getAlto() const {
	return alto;
}

double Personaje::getAncho() const {
	return ancho;
}

void Personaje::setPosicion(int x, int y) {
	this->unaCoordenada.setCoordenada(x,y);
}

Vector2f Personaje::getPosicion(){
	return this->unaCoordenada;
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

	Vector2f P1(this->unaCoordenada.X(), this->unaCoordenada.Y() + getAlto());
	float alto_mundo = this->limites->getLimitesLogicos().getAltoLogico();
	Vector2f P2(this->unaCoordenada.X(), alto_mundo - P1.Y());
	return P2;
}

//TODO: en esta parte iria la parte de los objetos trayectoria en lugar de los métodos siguientes:
void Personaje::aumentar_velocidadX(){
	void notificarObservadores();
	//this->velocidad.mover_en_X(DELTA_PASO);
}

void Personaje::disminuir_velocidadX(){
	void notificarObservadores();
	//this->velocidad.mover_en_X(-DELTA_PASO);
}

void Personaje::aumentar_velocidadY(){
	void notificarObservadores();
	//this->velocidad.mover_en_X(DELTA_PASO);
}

void Personaje::disminuir_velocidadY(){
	void notificarObservadores();
	//this->velocidad.mover_en_X(-DELTA_PASO);
}

double Personaje::getSpritesAncho() const {
	return sprites_ancho;
}

void Personaje::mover(){
	//Valido que no camine fuera del escenario en X
	//if((this->unaCoordenada.getCoordenadaX() > this->limite_izquierdo) && (this->unaCoordenada.getCoordenadaX() + this->ancho) < this->limite_derecho){
		//this->unaCoordenada.mover_en_X(this->velocidad.getCoordenadaX());
	//}
	//Valido que no camine fuera del escenario en Y
	//if((this->unaCoordenada.getCoordenadaY() > this->limite_inferior) && (this->unaCoordenada.getCoordenadaY() + this->alto) < this->limite_superior){
		//this->unaCoordenada.mover_en_Y(this->velocidad.getCoordenadaY());
	//}
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

