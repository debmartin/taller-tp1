/*
 * VentanaGrafica.cpp
 *
 *  Created on: 26/3/2015
 *      Author: val
 */

#include <iostream>
#include "VentanaGrafica.h"
#include "../modelo/Observable.h"
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

bool VentanaGrafica::init(string titulo, int xpos, int ypos, int alto, int anchoPx, int ancho_logico, bool fullscreen){

	this->ancho_ventanaPx = anchoPx;
	this->ancho_logico_ventana = ancho_logico;

	//Inicializamos el Renderizador.
	bool exito = Renderizador::Instance()->init(titulo, xpos, ypos, alto, anchoPx, fullscreen);
	cout << "VentanaGrafica:: creo Render" << endl;
	if(!exito){
		cout << "Renderizador init es falso" << endl;
		return false;
	}
	cout << "Renderizador inicializado correctamente" << endl;
	return true;
}

void VentanaGrafica::setEscenario(EscenarioGrafico* esc) {
    this->escenario = esc;
    LimitesLogicos limites_logicos = getLimitesLogicos();

    //Seteo los limites logicos de la ventana en base al escenario dado.
    this->limite_logico_izquierdo = (limites_logicos.getAnchoLogico()/2.0) - (this->ancho_logico_ventana/2.0);
    this->limite_logico_derecho = this->limite_logico_izquierdo + this->ancho_logico_ventana;
}

void VentanaGrafica::dibujarTodo(){
	Renderizador::Instance()->dibujar(this->escenario);
	//cout << "VentanaGrafica::dibujarTodo()" << endl;
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
	if( posicion <= this->limite_logico_izquierdo){
		this->limite_logico_izquierdo = posicionPersonaje.X();
		this->limite_logico_derecho = limite_logico_izquierdo + this->ancho_logico_ventana;
		this->escenario->scrollear_capas();
	}
	//Personaje en el margen derecho
	posicion = posicionPersonaje.X()+ unPersonaje->getAncho();
	if( posicion >= this->limite_logico_derecho){
		//Muevo los limites de la ventana.
		this->limite_logico_derecho = posicion;
		this->limite_logico_izquierdo = limite_logico_derecho - this->ancho_logico_ventana;

		this->escenario->scrollear_capas();
	}
}

float VentanaGrafica::getLimiteLogicoIzquierdo(){
	return this->limite_logico_izquierdo;
}

float VentanaGrafica::getLimiteLogicoDerecho(){
	return this->limite_logico_derecho;
}

float VentanaGrafica::relacion_de_aspectoX(){
	return this->ancho_ventanaPx / (this->limite_logico_derecho - this->limite_logico_izquierdo);
}

VentanaGrafica::~VentanaGrafica(){}
