/*
 * ControladorBotonera.h
 *
 *  Created on: 10/6/2015
 *      Author: ariel
 */

#ifndef SRC_MENUS_CONTROLADORBOTONERA_H_
#define SRC_MENUS_CONTROLADORBOTONERA_H_

#include "../controlador/ControladorJoystickMenu.h"

class Posicion;

class ControladorBotonera {
private:
	int cant_filas;
	int cant_columnas;
public:
	ControladorBotonera(int cant_filas, int cant_columnas);
	virtual ~ControladorBotonera();
	void identificarOrdenJugador1(Posicion* unaPosicionEnfocadaDelJugador1);
	void identificarOrdenJugador2(Posicion* unaPosicionEnfocadaDelJugador2);
	void identificarOrdenJoystick(Posicion* unaPosicionEnfocada, JoyNumberMenu numeroJoystick);
private:
	void posicionarArriba(Posicion* unaPosicionEnfocada);
	void posicionarAbajo(Posicion* unaPosicionEnfocada);
	void posicionarIzquierda(Posicion* unaPosicionEnfocada);
	void posicionarDerecha(Posicion* unaPosicionEnfocada);
	void elegir(Posicion* unaPosicionEnfocada);
};

#endif /* SRC_MENUS_CONTROLADORBOTONERA_H_ */
