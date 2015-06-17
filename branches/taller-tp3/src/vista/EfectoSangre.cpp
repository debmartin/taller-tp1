/*
 * EfectoSangre.cpp
 *
 *  Created on: 19/6/2015
 *      Author: val
 */

#include "EfectoSangre.h"

EfectoSangre::EfectoSangre(Vector2f pos) {
	// TODO Auto-generated constructor stub
	posicion = pos;
	animacionEfecto = new Animacion(Renderizador::Instance()->getRenderer(), PATH_EFECTO_SANGRE, 1, 10, "sangre");
	spriteEfecto = new Sprite(animacionEfecto,
			Renderizador::Instance()->getRenderer(),
			posicion,
			ORIENTACION_DERECHA, SPR_ABAJO_IZQUIERDA);
	visible = false;
}

EfectoSangre::~EfectoSangre() {
	// TODO Auto-generated destructor stub
}

Vector2f EfectoSangre::obtenerPosicionEnVentana(){
	Vector2f P1(posicion.X(), posicion.Y());
	Vector2f P2 = VentanaGrafica::Instance()->calcularPosicionEnVentana(P1);
	return P2;
}

void EfectoSangre::dibujar(){
	spriteEfecto->dibujar();
}

void EfectoSangre::ejecutarEfecto(Vector2f pos){
	posicion = pos;
	visible = true;
	Vector2f vector_auxiliar = obtenerPosicionEnVentana();
	spriteEfecto->setPosicion(vector_auxiliar);
}

void EfectoSangre::update(){

}

void EfectoSangre::posicionar(Vector2f pos){

}
