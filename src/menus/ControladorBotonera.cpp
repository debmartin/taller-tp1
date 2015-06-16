/*
 * ControladorBotonera.cpp
 *
 *  Created on: 10/6/2015
 *      Author: ariel
 */

#include "ControladorBotonera.h"

#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_scancode.h>
#include <SDL2/SDL_stdinc.h>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>

#include "Posicion.h"

ControladorBotonera::ControladorBotonera(int cant_filas, int cant_columnas) {
	this->cant_filas = cant_filas;
	this->cant_columnas = cant_columnas;
}

ControladorBotonera::~ControladorBotonera() {
	// TODO Auto-generated destructor stub
}

void ControladorBotonera::identificarOrdenJugador1(
		Posicion* unaPosicionEnfocadaDelJugador1) {

	const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);
	if (estadoTeclado[SDL_SCANCODE_LEFT])
	{
		this->posicionarIzquierda(unaPosicionEnfocadaDelJugador1);
	}
	else if (estadoTeclado[SDL_SCANCODE_RIGHT])
	{
		this->posicionarDerecha(unaPosicionEnfocadaDelJugador1);
	}
	else if (estadoTeclado[SDL_SCANCODE_UP])
	{
		this->posicionarArriba(unaPosicionEnfocadaDelJugador1);
	}
	else if (estadoTeclado[SDL_SCANCODE_DOWN])
	{
		this->posicionarAbajo(unaPosicionEnfocadaDelJugador1);
	}
	else if (estadoTeclado[SDL_SCANCODE_RETURN])
	{
		this->elegir(unaPosicionEnfocadaDelJugador1);
	}
}

void ControladorBotonera::identificarOrdenJugador2(
		Posicion* unaPosicionEnfocadaDelJugador2) {

	const Uint8* estadoTeclado = SDL_GetKeyboardState(NULL);
	if (estadoTeclado[SDL_SCANCODE_A])
	{
		this->posicionarIzquierda(unaPosicionEnfocadaDelJugador2);
	}
	else if (estadoTeclado[SDL_SCANCODE_D])
	{
		this->posicionarDerecha(unaPosicionEnfocadaDelJugador2);
	}
	else if (estadoTeclado[SDL_SCANCODE_W])
	{
		this->posicionarArriba(unaPosicionEnfocadaDelJugador2);
	}
	else if (estadoTeclado[SDL_SCANCODE_S])
	{
		this->posicionarAbajo(unaPosicionEnfocadaDelJugador2);
	}
	else if (estadoTeclado[SDL_SCANCODE_SPACE])
	{
		this->elegir(unaPosicionEnfocadaDelJugador2);
	}
}

void ControladorBotonera::identificarOrdenJoystick(
		Posicion* unaPosicionEnfocada, JoyNumberMenu numeroJoystick) {

	std::map<string, bool>* estadoJoy = TheInputHandlerMenu::Instance()->getJoystickState(numeroJoystick);

	if ( (*estadoJoy)["JOY_IZQUIERDA"] ){
		this->posicionarIzquierda(unaPosicionEnfocada);

	}else if ( (*estadoJoy)["JOY_DERECHA"] ){
		this->posicionarDerecha(unaPosicionEnfocada);

	}else if ( (*estadoJoy)["JOY_ARRIBA"] ){
		this->posicionarArriba(unaPosicionEnfocada);

	}else if ( (*estadoJoy)["JOY_ABAJO"] ){
		this->posicionarAbajo(unaPosicionEnfocada);

	}else if((*estadoJoy)["JOY_PINIA_BAJA"]){
		this->elegir(unaPosicionEnfocada);
	}

}

void ControladorBotonera::posicionarArriba(Posicion* unaPosicionEnfocada) {
	if ( unaPosicionEnfocada->getY() > 0 )
	{
		unaPosicionEnfocada->deselegir();
		unaPosicionEnfocada->posicionarArriba();
	}
}

void ControladorBotonera::posicionarAbajo(Posicion* unaPosicionEnfocada) {
	int cant_fils = this->cant_filas;
	if ( unaPosicionEnfocada->getY() < (--cant_fils) )
	{
		unaPosicionEnfocada->deselegir();
		unaPosicionEnfocada->posicionarAbajo();
	}
}

void ControladorBotonera::posicionarIzquierda(Posicion* unaPosicionEnfocada) {
	if ( unaPosicionEnfocada->getX() > 0 )
	{
		unaPosicionEnfocada->deselegir();
		unaPosicionEnfocada->posicionarIzquierda();
	}
}

void ControladorBotonera::posicionarDerecha(Posicion* unaPosicionEnfocada) {
	int cant_cols = this->cant_columnas;
	if ( unaPosicionEnfocada->getX() < (--cant_cols) )
	{
		unaPosicionEnfocada->deselegir();
		unaPosicionEnfocada->posicionarDerecha();
	}
}

void ControladorBotonera::elegir(Posicion* unaPosicionEnfocada) {
	unaPosicionEnfocada->elegir();
}

Posicion* ControladorBotonera::posicionarAleatoriamente()
{
	srand(time(NULL));
	int posX_rand = rand()%this->cant_columnas;
	int posY_rand = rand()%this->cant_filas;

	Posicion* posicionAleatoria = new Posicion(posX_rand, posY_rand);
	posicionAleatoria->elegir();

	return posicionAleatoria;
}
