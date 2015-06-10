/*
 * Jugador.h
 *
 *  Created on: 5/5/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_JUGADOR_H_
#define SRC_MODELO_JUGADOR_H_

#include <string>
#include "MapaDeCombos.h"

using namespace std;

class Personaje;
class PersonajeDibujable;
class Control;

class Jugador {
private:
	Personaje* personaje;
	PersonajeDibujable* personajeDibujable;
	Control* control;
	string tipo_control;
	MapaDeCombos* mapa_de_combos;
public:
	Jugador();
	Jugador(Personaje* personaje, PersonajeDibujable* personajeDibujable, Control* control, string tipo_control, MapaDeCombos* mapa);
	virtual ~Jugador();
	Personaje* getPersonaje() const;
	void setPersonaje(Personaje* personaje);
	PersonajeDibujable* getPersonajeDibujable() const;
	void setPersonajeDibujable(PersonajeDibujable* personajeDibujable);
	void posicionarPersonaje_enEjeX(double x);
	Control* getControl() const;
	string getTipoControl() const;
	MapaDeCombos* getMapaDeCombos();
};

#endif /* SRC_MODELO_JUGADOR_H_ */
