/*
 * PantallaSeleccionarPersonaje.h
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#ifndef SRC_MENUS_PANTALLASELECCIONARPERSONAJE_H_
#define SRC_MENUS_PANTALLASELECCIONARPERSONAJE_H_

#include <string>

#include "Pantalla.h"

using namespace std;

class PantallaSeleccionarPersonaje: public Pantalla {
private:
	string IdPersonaje1Elegido;
	string IdPersonaje2Elegido;
	string modo_juego_elegido;
public:
	PantallaSeleccionarPersonaje(string modo_juego_elegido);
	virtual ~PantallaSeleccionarPersonaje();
	void iniciar();
	string getIdPersonaje1Elegido();
	string getIdPersonaje2Elegido();
	string getModoJuegoElegido() const;
};

#endif /* SRC_MENUS_PANTALLASELECCIONARPERSONAJE_H_ */
