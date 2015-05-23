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
    sprite = new Sprite(
    				animacionCapa,
					Renderizador::Instance()->getRenderer(),
					posInicial,
					ORIENTACION_DERECHA);

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

void Capa::centrar_en(Vector2f v, float limiteLogicoIzquierdoVentana, float relacion_de_aspectoX){
	//Centro la capa en la posición dada.

	this->limite_logico_izquierdo = v.X() - (this->tamanioLogico.X() / 2.0f);
	float xPosSpritePx = (this->getLimiteLogicoIzquierdo() - limiteLogicoIzquierdoVentana ) * relacion_de_aspectoX;
	Vector2f nuevaPosicionPx(xPosSpritePx, v.Y());
	this->sprite->setPosicion(nuevaPosicionPx);
}

void Capa::setPosicionX(float nuevoX){
	this->limite_logico_izquierdo = nuevoX;
}



