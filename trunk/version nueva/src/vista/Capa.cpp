/*
 * Capa.cpp
 *
 *  Created on: 19/3/2015
 *      Author: ariel
 */

#include "Capa.h"

double Capa::getAncho() const {
	return ancho;
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

Capa::Capa(Animacion* animCapa, double anchoInicial, Vector2f& posInicial) :
    ancho(anchoInicial), animacionCapa(animCapa) {
    sprite = new Sprite(animacionCapa, posInicial);
}
