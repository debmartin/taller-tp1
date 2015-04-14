/*
 * Capa.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Capa.h"

Capa::Capa(Animacion* animCapa, Vector2f& tamInicialLogico, Vector2f& posInicial, Vector2f& aspectos) :
    animacionCapa(animCapa), tamanioLogico(tamInicialLogico), relacionAspectos(aspectos) {
	limite_logico_izquierdo = posInicial.X();
    sprite = new Sprite(animacionCapa, posInicial);

    sprite->escalarConTamanio(tamanioLogico.X()*aspectos.X(), tamanioLogico.Y()*aspectos.Y());
}

double Capa::getAnchoLogico() {
	return tamanioLogico.X();
}

double Capa::getLimiteLogicoIzquierdo() {
	return this->limite_logico_izquierdo;
}
double Capa::getLimiteLogicoDerecho() {
	return this->limite_logico_izquierdo + this->tamanioLogico.X();
}
Sprite* Capa::getSprite(){
	return this->sprite;
}

Capa::~Capa() {
    delete sprite;
}

void Capa::dibujar(){
    sprite->dibujar();
}

void Capa::actualizar(){
    sprite->update();
}

void Capa::centrar_en(Vector2f posicion){
	//Centro la capa en la posición dada.
	this->limite_logico_izquierdo = posicion.X() - (getAnchoLogico()/2.0);
	Vector2f vec(this->limite_logico_izquierdo, posicion.Y());
	this->sprite->setPosicion(vec);
}

void Capa::setPosicionX(float nuevoX){
	this->limite_logico_izquierdo = nuevoX;
}
//ostream& operator <<(ostream &o, const Capa &c) {
//
//        o<<"capa -> [imagen_fondo, ancho]=["<<c.imagen_fondo<<", "<<c.ancho<<"]";
//        return o;
//}


