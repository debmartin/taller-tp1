/*
 * PersonajeDibujable.cpp
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#include "PersonajeDibujable.h"

PersonajeDibujable::PersonajeDibujable() {

}

PersonajeDibujable::PersonajeDibujable(Animacion* animIni, Vector2f posicionIni, Vector2f tamanioPx, OrientacionSprite orientacion){
	spritePersonaje = new Sprite(animIni, posicionIni, orientacion);
    spritePersonaje->escalarConTamanio(tamanioPx.X(), tamanioPx.Y());
    animaciones[animIni->getId()] = animIni;
}

void PersonajeDibujable::setEstado(estado_personaje unEstado){
	this->estado = unEstado;
}

void PersonajeDibujable::seleccionarSprite(){

	switch(this->estado){
		case CAMINANDO_DERECHA:
			this->spritePersonaje->cambiarAnimacion(animaciones[ID_ZUBZERO_CAMINANDO]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			break;
		case CAMINANDO_IZQUIERDA:
			this->spritePersonaje->cambiarAnimacion(animaciones[ID_ZUBZERO_CAMINANDO]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
			break;
		case EN_ESPERA:
			this->spritePersonaje->cambiarAnimacion(animaciones[ID_ZUBZERO_QUIETO]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			break;
		case SALTANDO_VERTICAL:
			this->spritePersonaje->cambiarAnimacion(animaciones[ID_ZUBZERO_SALTANDOVERTICAL]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			break;
        case SALTANDO_OBLICUO_DERECHA:
            this->spritePersonaje->cambiarAnimacion(animaciones[ID_ZUBZERO_SALTANDODIAGONAL]);
            this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case SALTANDO_OBLICUO_IZQUIERDA:
            this->spritePersonaje->cambiarAnimacion(animaciones[ID_ZUBZERO_SALTANDODIAGONAL]);
            this->spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
            break;
        case AGACHADO:
            spritePersonaje->cambiarAnimacion(animaciones[ID_ZUBZERO_AGACHADO]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
	}
}

PersonajeDibujable::~PersonajeDibujable() {
    delete spritePersonaje;
}

void PersonajeDibujable::agregarAnimacion(Animacion* nuevaAnimacion){
    animaciones[nuevaAnimacion->getId()] = nuevaAnimacion;
}

void PersonajeDibujable::centrar_en(Vector2f v, float limiteLogicoIzquierdoVentana, float relacion_de_aspectoX){
	this->spritePersonaje->setPosicion(v);
}

void PersonajeDibujable::dibujar(){
	spritePersonaje->dibujar();
}

void PersonajeDibujable::actualizar(){
	spritePersonaje->update();
}

void PersonajeDibujable::recibirNotificacion(Observable* unObservable){
	Logger::getInstance()->debug("PersonajeDibujable: Recibió notificación.");

	Personaje* unPersonaje = (Personaje*) unObservable;
	Vector2f nueva_posicion = unPersonaje->obtenerPosicionEnVentana();

	Vector2f posicion_final(nueva_posicion.X()*VentanaGrafica::Instance()->relacion_de_aspectoX(), nueva_posicion.Y()*VentanaGrafica::Instance()->relacion_de_aspectoY());

	//Actualizo la posicion del Sprite.
	this->spritePersonaje->setPosicion(posicion_final);

	//Actualizo el estado del personajeDibujable
	setEstado(unPersonaje->getEstado());

	seleccionarSprite();
}

void PersonajeDibujable::cambiarOrientacionHaciaDerecha() {
	this->spritePersonaje->cambiarOrientacionHaciaDerecha();
}

void PersonajeDibujable::cambiarOrientacionHaciaIzquierda() {
	this->spritePersonaje->cambiarOrientacionHaciaIzquierda();
}

float PersonajeDibujable::getPosicionX() {
	return this->_getSprite()->getPosicion().X();
}
