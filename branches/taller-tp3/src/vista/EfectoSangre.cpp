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
	animacionEfecto = new Animacion(Renderizador::Instance()->getRenderer(), PATH_EFECTO_SANGRE, 8, 10, "sangre");
	spriteEfecto = new Sprite(animacionEfecto,
			Renderizador::Instance()->getRenderer(),
			posicion,
			ORIENTACION_DERECHA, SPR_ABAJO_CENTRO);
	spriteEfecto->escalarConTamanio(200* VentanaGrafica::Instance()->relacion_de_aspectoX(),200 * VentanaGrafica::Instance()->relacion_de_aspectoY());
	//spriteEfecto->escalarConTamanio(50,100);

	spriteEfecto->setLoopMode(LOOP_NO_REPEAT);
	spriteEfecto->setSentidoReproduccion(HACIA_ADELANTE);
	direccionEfecto = DIRECCION_DERECHA;
	visible = false;
	tiempoVisible = 0;
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
	if(visible){
		spriteEfecto->dibujar();
	}
}

//La dirección del efectoSangre debe ser opuesta a la direccion del personaje.
void EfectoSangre::ejecutarEfecto(Vector2f pos, DireccionObjeto direccion){
	tiempoVisible = 1000;
	visible = true;
	posicion = pos;

	//Posiciono el efecto
	Vector2f vector_auxiliar = obtenerPosicionEnVentana();
	Vector2f posicion_final(vector_auxiliar.X()*VentanaGrafica::Instance()->relacion_de_aspectoX(), vector_auxiliar.Y()*VentanaGrafica::Instance()->relacion_de_aspectoY());

	//Actualizo la posicion del Sprite.
	spriteEfecto->setPosicion(posicion_final);

	if(direccionEfecto == direccion){
		//Cambio la orientacion del sprite.
		if(direccion == DIRECCION_DERECHA){
			spriteEfecto->cambiarOrientacionHaciaIzquierda();
			direccionEfecto = DIRECCION_IZQUIERDA;
		}else{
			spriteEfecto->cambiarOrientacionHaciaDerecha();
			direccionEfecto = DIRECCION_DERECHA;
		}
	}
}

void EfectoSangre::update(){
	spriteEfecto->update();
	if(tiempoVisible <= 0){
		visible = false;
	}
	tiempoVisible -= 1;
}

void EfectoSangre::posicionar(Vector2f pos){

}
