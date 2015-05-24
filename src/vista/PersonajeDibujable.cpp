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
			case GANCHO:
				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_GANCHO]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
			case RECIBIENDO_GOLPE:
				this->spritePersonaje->setLoopMode(LOOP_MOD);
				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_RECIBIENDO_GOLPE]);
				spritePersonaje->setSentidoReproduccion(HACIA_ADELANTE);
				break;
//			case RECIBIENDO_GOLPE_CAIDA:
//				this->spritePersonaje->setLoopMode(LOOP_NO_REPEAT);
//				spritePersonaje->cambiarAnimacion(animaciones[ID_PERSONAJE_RECIBIENDO_GOLPE_CAIDA]);
//				spritePersonaje->setSentidoReproduccion(HACIA_ATRAS);
//				break;
		}
	}
	estadoAnterior = estado;
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
			unPersonaje->obtenerCajaColision()->calcularPosicion() + Vector2f(0, 310);
	cout << "ABAJO_IZQUIERDA:" << posicion_abajo_izquierda_logica_en_escenario << endl;
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
