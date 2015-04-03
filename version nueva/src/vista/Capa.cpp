/*
 * Capa.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Capa.h"

Capa::Capa(Animacion* animCapa, Vector2& tamInicial, Vector2f& posInicial) :
    animacionCapa(animCapa), tamanio(tamInicial) {
    sprite = new Sprite(animacionCapa, posInicial);
    sprite->escalarConTamanio(tamanio.getCoordenadaX(), tamanio.getCoordenadaY());
}

double Capa::getAncho() {
	return tamanio.getCoordenadaX();
}

//string Capa::getImagenFondo() const {
//	return imagen_fondo;
//}

Capa::~Capa() {
	// TODO Auto-generated destructor stub
}

void Capa::dibujar(){
    sprite->dibujar();
}
//ostream& operator <<(ostream &o, const Capa &c) {
//
//        o<<"capa -> [imagen_fondo, ancho]=["<<c.imagen_fondo<<", "<<c.ancho<<"]";
//        return o;
//}


