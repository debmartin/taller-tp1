/*
 * Arma.cpp
 *
 *  Created on: 2/5/2015
 *      Author: val
 */

#include "Arma.h"

Arma::Arma(int velocidad, double ancho, double alto, BVH* caja):
		velocidad_arma(velocidad),
		anchoArma(ancho),
		altoArma(alto),
		cajaBVH_arma(caja),
		Colisionable(POS_INICIAL_OBJETO, ancho, alto)
	{
	this->posicion = POS_INICIAL_OBJETO;
	this->trayectoria = new MRU(POS_INICIAL_OBJETO, VELOCIDAD_OBJETO);
	this->tCreacion = 0;
	this->damage = DANIO_ARMA;
	this->estado = NO_VISIBLE;
	this->direccionArma = DIRECCION_DERECHA;
}

int Arma::quitarEnergia(){
	return this->damage;
}

void Arma::posicionar(Vector2f pos){
	posicion = pos;
}

void Arma::cambiarEstado(estado_objeto unEstado){
	this->estado = unEstado;
}

estado_objeto Arma::getEstado(){
	return this->estado;
}

DireccionObjeto Arma::getDireccion(){
	return this->direccionArma;
}

void Arma::orientar(DireccionObjeto dir){
	direccionArma = dir;
}

void Arma::cambiarTrayectoria(Trayectoria* unaTrayectoria){
	this->trayectoria = unaTrayectoria;
}

void Arma::arrojar(){
	//cout<<"Arrojo arma"<<endl;
	if(direccionArma == DIRECCION_DERECHA){
		cout<<"Arrojar hacia derecha"<<endl;
		cambiarTrayectoria(new MRU(posicion, Vector2f(velocidad_arma, VELOCIDAD_ARMA_NULA)));
	}else{
		cout<<"Arrojar hacia izquierda"<<endl;
		cambiarTrayectoria(new MRU(posicion, Vector2f(-velocidad_arma, VELOCIDAD_ARMA_NULA)));
	}
	cambiarEstado(VISIBLE);
}

void Arma::update(){
	if(estado == VISIBLE){
		float tActual = ((float)(SDL_GetTicks())/1000.0f) - tCreacion;
		posicion = this->trayectoria->getPosicion(tActual);
		//cout<<"Posicion arma:"<<posicion.X()<<"||"<<posicion.Y()<<endl;
	}
	notificarObservadores();
}

void Arma::agregarObservador(Observador* unObservador){
	Observable::agregarObservador(unObservador);
}

void Arma::notificarObservadores(){
	Observable::notificarObservadores();
}

Vector2f Arma::obtenerPosicionEnVentana(){
	Vector2f P1(posicion.X(), posicion.Y());
	Vector2f P2 = VentanaGrafica::Instance()->calcularPosicionEnVentana(P1);
	return P2;
}

//Colisiones
void Arma::colisionar(Colisionable* otro){
	Colisionable::colisionar(otro);
	cambiarEstado(NO_VISIBLE);
}

bool Arma::vaAColisionar(Colisionable* enemigo){
	if (Colisionable::vaAColisionar(enemigo, anchoArma, altoArma))
	        return true;
	return false;
}

bool Arma::haySuperposicion(BVH* otraCaja) {
    if (!cajaBVH_arma || !otraCaja) return false;
    return cajaBVH_arma->interseccion(otraCaja);
}

BVH* Arma::obtenerCajaColision(){
	return cajaBVH_arma;
}

bool Arma::empujar(Direccion direccionEmpuje, Vector2f diferencia){
	return false;
}

Arma::~Arma() {
	// TODO Auto-generated destructor stub
}

