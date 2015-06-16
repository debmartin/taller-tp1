/*
 * PersonajeDibujable.cpp
 *
 *  Created on: 25/3/2015
 *      Author: val
 */

#include "PersonajeDibujable.h"

#include <utility>

#include "../modelo/fisica/BVH.h"
#include "../modelo/Personaje.h"
#include "../utils/Logger.h"
#include "ArmaDibujable.h"
#include "Renderizador.h"
#include "VentanaGrafica.h"

PersonajeDibujable::PersonajeDibujable() {

}

PersonajeDibujable::PersonajeDibujable(Animacion* animIni, Vector2f posicionIni, Vector2f tamanioPx, OrientacionSprite orientacion,
										ColorAlternativoDef* unColorAlternativo){
	//spritePersonaje = new Sprite(animIni, posicionIni, orientacion, SPR_ARRIBA_CENTRO);
	spritePersonaje = new Sprite(animIni, Renderizador::Instance()->getRenderer(), posicionIni, orientacion, SPR_ARRIBA_CENTRO);
    spritePersonaje->escalarConTamanio(tamanioPx.X(), tamanioPx.Y());
    animaciones[animIni->getId()] = animIni;
    colorAlternativo = unColorAlternativo;
    this->estadoAnterior = EN_ESPERA;

    // ENVOLVENTE
    this->animacionEnvolvente = new Animacion(Renderizador::Instance()->getRenderer(), "DEFAULT/ENVOLVENTE.png", 1, 1, "ENVOLVENTE");
    this->spriteEnvolvente = new Sprite(this->animacionEnvolvente, Renderizador::Instance()->getRenderer(), posicionIni, orientacion, SPR_ABAJO_IZQUIERDA);
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
	if (estadoAnterior != estado) {
		switch(this->estado) {
			case CAMINANDO_DERECHA:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				this->spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_CAMINANDO]);
				this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case CAMINANDO_IZQUIERDA:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				this->spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_CAMINANDO]);
				this->spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
				break;
			case EN_ESPERA:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				this->spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_REPOSO]);
				this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case SALTANDO_VERTICAL:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				this->spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_SALTANDO_VERTICAL]);
				this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case SALTANDO_OBLICUO_DERECHA:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				this->spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_SALTANDO_DIAGONAL]);
				this->spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case SALTANDO_OBLICUO_IZQUIERDA:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				this->spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_SALTANDO_DIAGONAL]);
				this->spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
				break;
			case AGACHADO:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_AGACHADO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case DEFENDIENDO:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_DEFENDIENDO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case DEFENDIENDO_AGACHADO:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_DEFENDIENDO_AGACHADO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case PINIA_ALTA:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_PINIA_ALTA]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case PINIA_BAJA:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_PINIA_BAJA]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case PINIA_SALTANDO_DIAGONAL_DERECHA:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_PINIA_SALTANDO_DIAGONAL]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case PINIA_SALTANDO_DIAGONAL_IZQUIERDA:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_PINIA_SALTANDO_DIAGONAL]);
				spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
				break;
			case PINIA_SALTANDO_VERTICAL:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_PINIA_SALTANDO_VERTICAL]);
				spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
				break;
			case PATEANDO_ALTO:
				this->spritePersonaje->setLoopMode(LOOP_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_PATEANDO_ALTO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case PATEANDO_BAJO:
				this->spritePersonaje->setLoopMode(LOOP_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_PATEANDO_BAJO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case PATEANDO_SALTANDO_DIAGONAL_DERECHA:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_PATEANDO_SALTANDO_DIAGONAL]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case PATEANDO_SALTANDO_DIAGONAL_IZQUIERDA:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_PATEANDO_SALTANDO_DIAGONAL]);
				spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
				break;
			case PATEANDO_SALTANDO_VERTICAL:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_PATEANDO_SALTANDO_VERTICAL]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case PATEANDO_ALTO_AGACHADO:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_PATEANDO_ALTO_AGACHADO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case PATADA_GIRATORIA:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_PATADA_GIRATORIA]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case DERRIBADO:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_DERRIBADO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case GANCHO:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_GANCHO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case RECIBIENDO_GOLPE:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_RECIBIENDO_GOLPE]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case RECIBIENDO_PINIA_RETROCEDIENDO:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_RECIBIENDO_PINIA_RETROCEDIENDO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case CAIDA_DERECHA:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_CAIDA]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case CAIDA_IZQUIERDA:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_CAIDA]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case MAREADO:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_MAREADO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case TIRANDO_PODER:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_TIRANDO_PODER]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case ARROJADO:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_ARROJADO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case VICTORIA:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_VICTORIA]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case MUERTO:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_CAIDA]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case MUERTO_EN_PISO:
			    this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
			    spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_MUERTO]);
			    spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
			    break;
			case SLIDE:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_SLIDE]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case TIJERA:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_TIJERA]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case BEBE:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_BEBE]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case ANIMALITY:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_ANIMALITY]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case ANIMALITY2:
				this->spritePersonaje->setLoopMode(LOOP_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_ANIMALITY2]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case OSO:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_ANIMALITY]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case OSO2:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_ANIMALITY2]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case FATALITY1:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_FATALITY1]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case DECAPITADO:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_DECAPITADO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case GANCHO_FATALITY:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_GANCHO_FATALITY]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
		}
	}
	estadoAnterior = estado;
}

PersonajeDibujable::~PersonajeDibujable() {
    delete spritePersonaje;
    delete spriteEnvolvente;
}

void PersonajeDibujable::agregarAnimacion(Animacion* nuevaAnimacion){
    animaciones[nuevaAnimacion->getId()] = nuevaAnimacion;
}

void PersonajeDibujable::dibujar(){
	spritePersonaje->dibujar();
	armaDibujable->dibujar();
	spriteEnvolvente->dibujar();
}

void PersonajeDibujable::actualizar(){
	spritePersonaje->update();
	armaDibujable->actualizar();
	spriteEnvolvente->update();
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

	// ENVOLVENTE
	float anchoPx = unPersonaje->getAnchoEnvolvente() * VentanaGrafica::Instance()->relacion_de_aspectoX();
	float altoPx  = unPersonaje->getAltoEnvolvente() * VentanaGrafica::Instance()->relacion_de_aspectoY();
	this->spriteEnvolvente->escalarConTamanio(anchoPx, altoPx);

	Vector2f posicion_abajo_izquierda_logica_en_escenario =
			unPersonaje->obtenerCajaColision()->calcularPosicion();

	Vector2f posicion_abajo_izquierda_logica_en_ventana =
			VentanaGrafica::Instance()->calcularPosicionEnVentana(posicion_abajo_izquierda_logica_en_escenario);

	Vector2f posicion_abajo_izquierda_px_en_ventana = Vector2f(
			posicion_abajo_izquierda_logica_en_ventana.X() * VentanaGrafica::Instance()->relacion_de_aspectoX(),
			posicion_abajo_izquierda_logica_en_ventana.Y() * VentanaGrafica::Instance()->relacion_de_aspectoY());

	this->spriteEnvolvente->setPosicion(posicion_abajo_izquierda_px_en_ventana);
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

Sprite* PersonajeDibujable::getSpritePersonaje() const {
	return spritePersonaje;
}
