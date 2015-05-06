/*
 * PersonajeDibujable.cpp
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#include "PersonajeDibujable.h"

#include <utility>

#include "../utils/Logger.h"
#include "ArmaDibujable.h"
#include "VentanaGrafica.h"

PersonajeDibujable::PersonajeDibujable() {

}

PersonajeDibujable::PersonajeDibujable(Animacion* animIni, Vector2f posicionIni, Vector2f tamanioPx, OrientacionSprite orientacion,
										ColorAlternativoDef* unColorAlternativo){
	spritePersonaje = new Sprite(animIni, posicionIni, orientacion);
    spritePersonaje->escalarConTamanio(tamanioPx.X(), tamanioPx.Y());
    animaciones[animIni->getId()] = animIni;
    colorAlternativo = unColorAlternativo;
}

void PersonajeDibujable::setEstado(estado_personaje unEstado){
	this->estado = unEstado;
}

void PersonajeDibujable::agregarArma(ArmaDibujable* unArma){
	this->armaDibujable = unArma;
}

ArmaDibujable* PersonajeDibujable::getArma(){
	return armaDibujable;
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

void PersonajeDibujable::dibujar(){
	spritePersonaje->dibujar();
	armaDibujable->dibujar();
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

ColorAlternativoDef* PersonajeDibujable::getColorAlternativo() const {
	return colorAlternativo;
}

void PersonajeDibujable::cambiarColor(ColorAlternativoDef* colorAlternativoDef) {

	for (std::map<std::string, Animacion*>::iterator it = this->animaciones.begin() ; it != this->animaciones.end(); ++it)
	{
		it->second->cambiarColor(colorAlternativoDef);
	}

}
