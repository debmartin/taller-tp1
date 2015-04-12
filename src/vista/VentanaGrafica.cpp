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

VentanaGrafica::VentanaGrafica() :
    escenario(NULL), limite_logico_izquierdo(0), ancho_logico_ventana(0), ancho_ventanaPx(0) { }

bool VentanaGrafica::init(string titulo, Vector2f posicion, Vector2f tamanioPixels, Vector2f tamanioLogico, bool fullscreen){

	this->ancho_ventanaPx = tamanioPixels.X();
	this->alto_ventanaPx = tamanioPixels.Y();
	this->ancho_logico_ventana = tamanioLogico.X();
	this->alto_logico_ventana = tamanioLogico.Y();

	//Inicializamos el Renderizador.
	bool exito = Renderizador::Instance()->init(titulo, posicion, tamanioPixels, fullscreen);
	cout << "VentanaGrafica:: creo Render" << endl;
	if(!exito){
		cout << "Renderizador init es falso" << endl;
		return false;
	}
	cout << "Renderizador inicializado correctamente" << endl;
	return true;
}

void VentanaGrafica::agregarEscenario(EscenarioGrafico* esc) {
    escenario = esc;

    //Seteo los limites logicos de la ventana en base al escenario dado.
    limite_logico_izquierdo = (escenario->getAnchoLogico()/2.0) - (ancho_logico_ventana/2.0);
}

void VentanaGrafica::centrar_ventana(){
	this->limite_logico_izquierdo = (this->escenario->getAnchoLogico()/2.0) - (this->ancho_logico_ventana/2.0);
}

Vector2f VentanaGrafica::calcularPosicionEnVentana(Vector2f posicionLogica){
    return Vector2f(posicionLogica.X()-limite_logico_izquierdo, escenario->getAltoLogico() - posicionLogica.Y());
}

void VentanaGrafica::dibujarTodo(){
	Renderizador::Instance()->dibujar(escenario);
}

void VentanaGrafica::actualizar() {
    escenario->actualizar();
}

void VentanaGrafica::recibirNotificacion(Observable* unObservable){
	//Verifico posicion del jugador, si llego al limite de la ventana, scrollar.

	Personaje* unPersonaje = (Personaje*) unObservable;
	Vector2f posicionPersonaje = unPersonaje->getPosicion();

	//Personaje en el margen izquierdo.
	float posicion = posicionPersonaje.X();
	if( posicion <= this->limite_logico_izquierdo){
		this->limite_logico_izquierdo = posicionPersonaje.X();
		this->escenario->scrollear_capas();
	}
	//Personaje en el margen derecho
	posicion = posicionPersonaje.X()+ unPersonaje->getAncho();
	if( posicion >= getLimiteLogicoDerecho()){
		//Muevo los limites de la ventana.
		this->limite_logico_izquierdo = posicion - this->ancho_logico_ventana;
		this->escenario->scrollear_capas();
	}
}

float VentanaGrafica::getLimiteLogicoIzquierdo(){
	return this->limite_logico_izquierdo;
}

float VentanaGrafica::getLimiteLogicoDerecho(){
	return limite_logico_izquierdo + ancho_logico_ventana;
}

float VentanaGrafica::getAnchoLogico() {
	return ancho_logico_ventana;
}
/*
float VentanaGrafica::relacion_de_aspectoX(){
	return this->ancho_ventanaPx / (getLimiteLogicoDerecho() - this->limite_logico_izquierdo);
}
*/
float VentanaGrafica::relacion_de_aspectoX(){
	//cout << "VentanaGrafica:Aspectos:" << this->ancho_ventanaPx<<";"<< this->limite_logico_derecho<<";"<< this->limite_logico_izquierdo<<endl;
	float res = this->ancho_ventanaPx / ((this->limite_logico_izquierdo + this->ancho_logico_ventana) - this->limite_logico_izquierdo);
	//cout << "VentanaGrafica:relacion de aspectoX:" << res << endl;
	return res;
}

float VentanaGrafica::relacion_de_aspectoY(){
	//cout << "VentanaGrafica:relacion de aspectoY:" << this->ancho_ventanaPx<<";"<< this->alto_logico_ventana<<endl;
	return this->alto_ventanaPx / (this->alto_logico_ventana);
}

Vector2f VentanaGrafica::obtener_relacion_aspectos(){
	Vector2f vec(relacion_de_aspectoX(), relacion_de_aspectoY());
	return vec;
}

VentanaGrafica::~VentanaGrafica(){
    delete Renderizador::Instance();
}

bool VentanaGrafica::esValida(Vector2f posicion){
    return escenario->esValida(posicion); //Cuando haya mas de un personaje se agregarán el resto de las condiciones
}
