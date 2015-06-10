/*
 * PantallaSeleccionarModo.h
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#ifndef SRC_MENUS_PANTALLASELECCIONARMODO_H_
#define SRC_MENUS_PANTALLASELECCIONARMODO_H_

#include <string>

#include "Pantalla.h"

using namespace std;

class PantallaSeleccionarModo: public Pantalla {
private:
	string modo_juego_elegido;
public:
	PantallaSeleccionarModo(string tipoDeControl_jugador1, string tipoDeControl_jugador2);
	virtual ~PantallaSeleccionarModo();
	void iniciar();
	string getModoDeJuegoElegido();
};

#endif /* SRC_MENUS_PANTALLASELECCIONARMODO_H_ */
