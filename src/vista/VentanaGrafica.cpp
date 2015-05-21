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

VentanaGrafica::VentanaGrafica() {} // TODO: GASTON: INICIALIZAR CORRECTAMENTE
    //escenario(NULL), limite_logico_izquierdo(0), ancho_logico_ventana(0), ancho_ventanaPx(0) { }

bool VentanaGrafica::init(string titulo, Vector2f posicionVentanaPrograma, Vector2f tamanioPixels, Vector2f tamanioLogico, bool fullscreen){

	this->tamPixels = tamanioPixels;
	this->tamLogico = Vector2f(tamanioLogico.X(), tamanioLogico.Y() * PORCENTAJE_TAMANIO_VENTANA);
	this->vibracion = Vibracion(PORCENTAJE_ESPACIO_INFERIOR_VENTANA * tamanioLogico.X());
	//Inicializamos el Renderizador.
	bool exito = Renderizador::Instance()->init(titulo, posicionVentanaPrograma, tamanioPixels, fullscreen);
	if(!exito){
		Logger::getInstance()->error(
						"Falla al inicializar el Renderizador.");
		return false;
	}
	Logger::getInstance()->debug(
					"Inicialiazación de Renderizador correcta.");
	return true;
}

void VentanaGrafica::agregarEscenario(EscenarioGrafico* esc) {
    escenario = esc;
    centrar_ventana();
}

void VentanaGrafica::centrar_ventana() {
	this->posLogico.X((this->escenario->getAnchoLogico()/2.0) - (this->tamLogico.X()/2.0));
	this->posLogico.Y(this->escenario->getAltoLogico() * PORCENTAJE_ESPACIO_INFERIOR_VENTANA);
}

Vector2f VentanaGrafica::calcularPosicionEnVentana(Vector2f posicionLogica) {
	Vector2f V1 = getPosLogico() + Vector2f(0, this->tamLogico.Y());
	Vector2f vNuevo = posicionLogica - V1;
	vNuevo.Y(-vNuevo.Y());
	return vNuevo;
}

void VentanaGrafica::vibrar() {
	if (this->vibracion.estaVibrando())
		return;
	this->vibracion.iniciar();
}

Vector2f VentanaGrafica::getPosLogico() {
	// VIBRACION PARA MOVER PERSONAJES
	return Vector2f(this->posLogico + vibracion.getOffset());
}

void VentanaGrafica::dibujarTodo() {
	Renderizador::Instance()->dibujar(escenario);
}

void VentanaGrafica::actualizar() {
    escenario->actualizar();
    cout << *this << endl;
}

void VentanaGrafica::recibirNotificacion(Observable* unObservable){
	//Verifico posicion del jugador, si llego al limite de la ventana, scrollar.
	Logger::getInstance()->debug("VentanaGrafica: Recibió notificación.");
	Personaje* unPersonaje = (Personaje*) unObservable;
	Vector2f posicionPersonaje = unPersonaje->getPosicion();

	//Personaje en el margen izquierdo.
	float posicion = posicionPersonaje.X();
	if( posicion <= getPosLogico().X()){
		//this->limite_logico_izquierdo = posicionPersonaje.X();
		this->posLogico = Vector2f(posicionPersonaje.X(), posLogico.Y());
		this->escenario->scrollear_capas();
	}
	//Personaje en el margen derecho
	posicion = posicionPersonaje.X()+ unPersonaje->getAnchoEnvolvente();
	if( posicion >= getLimiteLogicoDerecho()){
		//Muevo los limites de la ventana.
		//this->limite_logico_izquierdo = posicion - this->tamLogico.X();
		this->posLogico = Vector2f(posicion - this->tamLogico.X(), posLogico.Y());
		this->escenario->scrollear_capas();
	}
}

float VentanaGrafica::getLimiteLogicoIzquierdo(){
	return getPosLogico().X();
}

float VentanaGrafica::getLimiteLogicoSuperior(){
	// VIBRACION PARA MOVER CAPAS
	return this->vibracion.getOffset().Y();
}

float VentanaGrafica::getLimiteLogicoDerecho(){
	return getPosLogico().X() + this->tamLogico.X();
}

float VentanaGrafica::getAnchoLogico() {
	return this->tamLogico.X();
}

float VentanaGrafica::getAnchoPx(){
	//return this->ancho_ventanaPx;
	return this->tamPixels.X();
}

bool VentanaGrafica::llegoAlLimiteIzquierdo(Vector2f posicion){
	return (posicion.X() <= 0);
}

bool VentanaGrafica::llegoAlLimiteDerecho(Vector2f posicion){
	return (posicion.X() >= escenario->getAnchoLogico());
}

float VentanaGrafica::relacion_de_aspectoX(){
	//float res = this->ancho_ventanaPx / ((this->limite_logico_izquierdo + this->ancho_logico_ventana) - this->limite_logico_izquierdo);
	float res = this->tamPixels.X() / ((getPosLogico().X() + this->tamLogico.X()) - getPosLogico().X());
	return res;
}

float VentanaGrafica::relacion_de_aspectoY(){
	//return this->alto_ventanaPx / (this->alto_logico_ventana);
	return this->tamPixels.Y() / (this->tamLogico.Y());
}

Vector2f VentanaGrafica::obtener_relacion_aspectos(){
	Vector2f vec(relacion_de_aspectoX(), relacion_de_aspectoY());
	return vec;
}

VentanaGrafica::~VentanaGrafica(){
    delete Renderizador::Instance();
    instancia_unica = NULL;
}

bool VentanaGrafica::esValida(Vector2f posicion, double ancho){
    return escenario->esValida(posicion, ancho);
}

bool VentanaGrafica::enExtremos(float distancia, double ancho){
    float ancho_restante = this->tamLogico.X() -ancho*2;
    return (distancia >= ancho_restante);
}

EscenarioGrafico* VentanaGrafica::getEscenario() const {
	return escenario;
}

ostream& operator <<(ostream &o, const VentanaGrafica &v) {
       	//cout << "VENTANA_GRAFICA-TAMANIO_PIXELS:" << v.tamPixels << endl;
        //cout << "VENTANA_GRAFICA-TAMANIO_LOGICO:" << v.tamLogico << endl;
       	//cout << "VENTANA_GRAFICA-POSICION_LOGICA:" << v.posLogico << endl;
       	cout << "VENTANA_GRAFICA-LIMITE_IZQUIERDO:" << v.posLogico.X() << endl;
       	cout << "VENTANA_GRAFICA-LIMITE_DERECHO:" << v.posLogico.X() + v.tamLogico.X() << endl;
        return o;
}

