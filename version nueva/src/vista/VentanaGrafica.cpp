/*
 * VentanaGrafica.cpp
 *
 *  Created on: 26/3/2015
 *      Author: val
 */

#include <iostream>
#include "VentanaGrafica.h"
#include <SDL2/SDL.h>
#include <vector>

VentanaGrafica* VentanaGrafica::instancia_unica = NULL;

VentanaGrafica* VentanaGrafica::Instance()
{
	if (instancia_unica == NULL)
	{
		instancia_unica = new VentanaGrafica();
	}
	return instancia_unica;
}

VentanaGrafica::VentanaGrafica():escenario(NULL){ }

bool VentanaGrafica::init(string titulo, int xpos, int ypos, int height, int width, bool fullscreen){

	this->ancho = width;

	//Inicializamos el Renderizador.
	bool exito = Renderizador::Instance()->init(titulo, xpos, ypos, height, width, fullscreen);
	cout << "VentanaGrafica:: creo Render" << endl;
	if(!exito){
		cout << "Renderizador init es falso" << endl;
		return false;
	}
	cout << "Renderizador inicializado correctamente" << endl;
	return true;
}

void VentanaGrafica::setEscenario(EscenarioGrafico* esc) {
    escenario = esc;
}

void VentanaGrafica::dibujarTodo(){

	cout << "VentanaGrafica::dibujarTodo()" << endl;
}

void VentanaGrafica::cerrar() {
	Renderizador::Instance()->cerrar();
	cout << "Cerrando ventana" << endl;
}

void VentanaGrafica::actualizar() {
    escenario->actualizar();
}

//Devuelve limites logicos del escenario
LimitesLogicos VentanaGrafica::getLimitesLogicos(){

	LimitesLogicos limitesLogicos(this->escenario->getAnchoLogico(), this->escenario->getAltoLogico(), this->escenario->getYPisoLogico());
	return limitesLogicos;
}

//Devuelte true si un punto es válido dentro del escenario.
bool VentanaGrafica::esPosicionValida(Vector2f posicion){
	int limite_izquierdo = 0;
	int limite_inferior = this->escenario->getYPisoLogico();

	if (posicion.X() < limite_izquierdo || (posicion.X() > this->escenario->getAnchoLogico())){
		return false;
	}
	if (posicion.Y() < limite_inferior || (posicion.Y() > this->escenario->getAltoLogico())){
		return false;
	}
	return true;
}

void VentanaGrafica::recibirNotificacion(Observable* unObservable){
	//Verifico posicion del jugador, si llego al limite de la ventana, scrollar.

	Personaje* unPersonaje = (Personaje*) unObservable;
	Vector2f posicionPersonaje = unPersonaje->getPosicion();

	//Personaje en el margen izquierdo.
	float posicion = posicionPersonaje.X();
	if( posicion <= this->limite_izquierdo){
		this->escenario->scrollear_capas(DERECHA);
		this->limite_izquierdo = posicionPersonaje.X();
		this->limite_derecho = limite_izquierdo + this->ancho;
	}
	//Personaje en el margen derecho
	posicion = posicionPersonaje.X()+ unPersonaje->getAncho();
	if( posicion >= this->limite_derecho){
		this->escenario->scrollear_capas(IZQUIERDA);
		this->limite_derecho = posicion;
		this->limite_izquierdo = limite_derecho - this->ancho;
	}
}

VentanaGrafica::~VentanaGrafica(){}
