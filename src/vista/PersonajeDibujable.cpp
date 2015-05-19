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
	spritePersonaje = new Sprite(animIni, posicionIni, orientacion, SPR_ARRIBA_CENTRO);
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
			this->spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_CAMINANDO]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			break;
		case CAMINANDO_IZQUIERDA:
			this->spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_CAMINANDO]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
			break;
		case EN_ESPERA:
			this->spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_REPOSO]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			break;
		case SALTANDO_VERTICAL:
			this->spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_SALTANDO_VERTICAL]);
			this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			break;
        case SALTANDO_OBLICUO_DERECHA:
            this->spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_SALTANDO_DIAGONAL]);
            this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case SALTANDO_OBLICUO_IZQUIERDA:
            this->spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_SALTANDO_DIAGONAL]);
            this->spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
            break;
        case AGACHADO:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_AGACHADO]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case DEFENDIENDO:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_DEFENDIENDO]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case DEFENDIENDO_AGACHADO:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_DEFENDIENDO_AGACHADO]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case PINIA_ALTA:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_PINIA_ALTA]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case PINIA_BAJA:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_PINIA_BAJA]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case PINIA_SALTANDO_DIAGONAL_DERECHA:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_PINIA_SALTANDO_DIAGONAL]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case PINIA_SALTANDO_DIAGONAL_IZQUIERDA:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_PINIA_SALTANDO_DIAGONAL]);
            spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
            break;
        case PINIA_SALTANDO_VERTICAL:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_PINIA_SALTANDO_VERTICAL]);
            spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
            break;
        case PATEANDO_ALTO:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_PATEANDO_ALTO]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case PATEANDO_BAJO:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_PATEANDO_BAJO]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case PATEANDO_SALTANDO_DIAGONAL_DERECHA:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_PATEANDO_SALTANDO_DIAGONAL]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case PATEANDO_SALTANDO_DIAGONAL_IZQUIERDA:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_PATEANDO_SALTANDO_DIAGONAL]);
            spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
            break;
        case PATEANDO_SALTANDO_VERTICAL:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_PATEANDO_SALTANDO_VERTICAL]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case PATEANDO_ALTO_AGACHADO:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_PATEANDO_ALTO_AGACHADO]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
        case GANCHO:
            spritePersonaje->cambiarAnimacion(animaciones[ID_SUBZERO_GANCHO]);
            spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
            break;
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
	armaDibujable->actualizar();
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
	this->armaDibujable->getSprite()->cambiarOrientacionHaciaDerecha();
}

void PersonajeDibujable::cambiarOrientacionHaciaIzquierda() {
	this->spritePersonaje->cambiarOrientacionHaciaIzquierda();
	this->armaDibujable->getSprite()->cambiarOrientacionHaciaIzquierda();
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
