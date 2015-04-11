/*
 * Capa.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Capa.h"

Capa::Capa(Animacion* animCapa, Vector2f& tamInicialLogico, Vector2f& posInicial) :
    animacionCapa(animCapa), tamanioLogico(tamInicialLogico) {
	limite_logico_izquierdo = posInicial.X();
    sprite = new Sprite(animacionCapa, posInicial);
    sprite->escalarConTamanio(tamanioLogico.X(), tamanioLogico.Y());
}

double Capa::getAnchoLogico() {
	return tamanioLogico.X();
}

double Capa::getLimiteLogicoIzquierdo() {
	return this->limite_logico_izquierdo;
}

Sprite* Capa::getSprite(){
	return this->sprite;
}

//string Capa::getImagenFondo() const {
//	return imagen_fondo;
//}

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

//ostream& operator <<(ostream &o, const Capa &c) {
//
//        o<<"capa -> [imagen_fondo, ancho]=["<<c.imagen_fondo<<", "<<c.ancho<<"]";
//        return o;
//}


