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

int Arma::obtenerDanio(){
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
	cout<<"Arrojo arma"<<endl;
	tCreacion = SDL_GetTicks() / 1000.0f;
	if(direccionArma == DIRECCION_DERECHA){
		cout<<"Arrojar hacia derecha"<<endl;
		cambiarTrayectoria(new MRU(posicion, Vector2f(velocidad_arma, VELOCIDAD_ARMA_NULA)));
	}else{
		cout<<"Arrojar hacia izquierda"<<endl;
		cambiarTrayectoria(new MRU(posicion, Vector2f(-velocidad_arma, VELOCIDAD_ARMA_NULA)));
	}
	cambiarEstado(VISIBLE);
}

void Arma::update(Colisionable* enemigo){
    posicionAnterior = posicion;

	if(estado == VISIBLE){
		float tActual = ((float)(SDL_GetTicks())/1000.0f) - tCreacion;
		posicionCandidata = this->trayectoria->getPosicion(tActual);
		cout<<"Posicion arma:"<<posicion.X()<<"||"<<posicion.Y()<<endl;

		if (vaAColisionar(enemigo)){
            colisionar(enemigo);
        }else
            posicion = posicionCandidata;
	} else {
        posicion = POS_INICIAL_OBJETO;
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

bool Arma::vaAColisionar(Colisionable* otro){
//	if (Colisionable::vaAColisionar(otro, anchoArma, altoArma))
//    cout << "ant: " << posicionAnterior << "pos:" << posicion <<
    if (((posicionAnterior.X() < otro->getPosicion().X() && posicionCandidata.X() >= otro->getPosicion().X() - otro->getAncho()) ||
             (posicionAnterior.X() > otro->getPosicion().X() + otro->getAncho() && posicionCandidata.X()  <= otro->getPosicion().X() + otro->getAncho())))
//             (posicionCandidata.Y() - alto/2<= otro->getPosicion().Y() + otro->getAlto()))
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

bool Arma::empujar(Direccion direccionEmpuje, Vector2f diferencia){
	return false;
}

bool Arma::estaEnReposo(){
	return true;
}

Arma::~Arma() {
	// TODO Auto-generated destructor stub
}

