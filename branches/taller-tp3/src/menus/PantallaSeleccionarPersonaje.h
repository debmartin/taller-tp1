/*
 * PantallaSeleccionarPersonaje.h
 *
 *  Created on: 30/5/2015
 *      Author: ariel
 */

#ifndef SRC_MENUS_PANTALLASELECCIONARPERSONAJE_H_
#define SRC_MENUS_PANTALLASELECCIONARPERSONAJE_H_

#include <map>
#include <string>

#include "../vista/PersonajeDibujable.h"
#include "Pantalla.h"

using namespace std;

class PantallaSeleccionarPersonaje: public Pantalla {
private:
	string IdPersonaje1Elegido;
	string IdPersonaje2Elegido;
	string modo_juego_elegido;
	string nombrePersonaje1;
	string nombrePersonaje2;
	map<string, PersonajeDibujable*>* personajesDibujables;
public:
	PantallaSeleccionarPersonaje(int anchopx, int altopx, string modo_juego_elegido, string tipoDeControl_jugador1,
								string tipoDeControl_jugador2, map<string, PersonajeDibujable*>* personajesDibujables);
	virtual ~PantallaSeleccionarPersonaje();
	void iniciar();
	string getIdPersonaje1Elegido();
	string getIdPersonaje2Elegido();
	string getModoJuegoElegido() const;
	string getNombrePersonaje1() const;
	string getNombrePersonaje2() const;
private:
	void dibujarPersonajeEnfocado(int posX, int posY, string idPersonajeEnfocado);
};

#endif /* SRC_MENUS_PANTALLASELECCIONARPERSONAJE_H_ */
