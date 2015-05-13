/*
 * Jugador.h
 *
 *  Created on: 5/5/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_JUGADOR_H_
#define SRC_MODELO_JUGADOR_H_
class Control;

using namespace std;

class Personaje;
class PersonajeDibujable;

class Jugador {
private:
	Personaje* personaje;
	PersonajeDibujable* personajeDibujable;
	Control* control;
public:
	Jugador();
	Jugador(Personaje* personaje, PersonajeDibujable* personajeDibujable, Control* control);
	virtual ~Jugador();
	Personaje* getPersonaje() const;
	void setPersonaje(Personaje* personaje);
	PersonajeDibujable* getPersonajeDibujable() const;
	void setPersonajeDibujable(PersonajeDibujable* personajeDibujable);
	void posicionarPersonaje_enEjeX(double x);
	Control* getControl() const;
};

#endif /* SRC_MODELO_JUGADOR_H_ */