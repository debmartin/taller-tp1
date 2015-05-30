/*
 * Arma.cpp
 *
 *  Created on: 2/5/2015
 *      Author: val
 */

#include "Arma.h"

Arma::Arma(int velocidad, double ancho, double alto, BVH* caja):
		Colisionable(POS_INICIAL_OBJETO, ancho, alto),
		velocidad_arma(velocidad),
		anchoArma(ancho),
		altoArma(alto),
		cajaBVH_arma(caja)
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

int Arma::obtenerDanio(){
	return this->damage;
}

void Arma::posicionar(Vector2f pos){
	posicion = pos;
	cajaBVH_arma->setPosicion(posicion);
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
	cout<<"*******************"<<endl;
	cout<<"Arrojando arma"<<endl;
	cout<<"*******************"<<endl;
	tCreacion = SDL_GetTicks() / 1000.0f;
	if(direccionArma == DIRECCION_DERECHA){
		cambiarTrayectoria(new MRU(posicion, Vector2f(velocidad_arma, VELOCIDAD_ARMA_NULA)));
	}else{
		cambiarTrayectoria(new MRU(posicion, Vector2f(-velocidad_arma, VELOCIDAD_ARMA_NULA)));
	}
	cambiarEstado(VISIBLE);
}

void Arma::update(Colisionable* enemigo){
    posicionAnterior = posicion;

	if(estado == VISIBLE){
		float tActual = ((float)(SDL_GetTicks())/1000.0f) - tCreacion;
		posicionCandidata = this->trayectoria->getPosicion(tActual);

		if (vaAColisionar(enemigo)){
            colisionar(enemigo);
        }else
            posicion = posicionCandidata;
	} else {
        posicion = POS_INICIAL_OBJETO;
	}
//	cout << "arma " << posicion << endl;
//	cout << "Caja Arma: " << *cajaBVH_arma << endl;
	cajaBVH_arma->desplazarBVH(posicion - posicionAnterior);
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
	//if(!(otro->verEstado()->estaAgachado()))
	Colisionable::colisionar(otro);
	cambiarEstado(NO_VISIBLE);
}

bool Arma::vaAColisionar(Colisionable* otro){
    if (Colisionable::vaAColisionar(otro, anchoArma, altoArma))
        return true;
    return haySuperposicion(otro->obtenerCajaColision());
}

bool Arma::haySuperposicion(BVH* otraCaja) {
    if (!cajaBVH_arma || !otraCaja) return false;
    return cajaBVH_arma->interseccion(otraCaja);
}

BVH* Arma::obtenerCajaColision(){
	return cajaBVH_arma;
}

bool Arma::empujar(Vector2f& diferencia){
	return false;
}

bool Arma::estaEnReposo(){
	return true;
}

Estado* Arma::verEstado(){
	return NULL;
}

Arma::~Arma() {
	// TODO Auto-generated destructor stub
}

bool Arma::estaAtacando(){
    return true;
}
