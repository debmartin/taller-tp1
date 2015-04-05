/*
 * Capa.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Capa.h"

Capa::Capa(Animacion* animCapa, Vector2f& tamInicial, Vector2f& posInicial) :
    animacionCapa(animCapa), tamanio(tamInicial) {
    sprite = new Sprite(animacionCapa, posInicial);
    sprite->escalarConTamanio(tamanio.X(), tamanio.Y());
}

double Capa::getAncho() {
	return tamanio.X();
}

//string Capa::getImagenFondo() const {
//	return imagen_fondo;
//}

Capa::~Capa() {
	SDL_DestroyTexture(animacionCapa->getTextura());
}

void Capa::dibujar(){
    sprite->dibujar();
}

void Capa::actualizar(){
    sprite->update();
}
//ostream& operator <<(ostream &o, const Capa &c) {
//
//        o<<"capa -> [imagen_fondo, ancho]=["<<c.imagen_fondo<<", "<<c.ancho<<"]";
//        return o;
//}


