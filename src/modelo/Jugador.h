/*
 * Jugador.h
 *
 *  Created on: 5/5/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_JUGADOR_H_
#define SRC_MODELO_JUGADOR_H_

using namespace std;

class Personaje;
class PersonajeDibujable;

class Jugador {
private:
	Personaje* personaje;
	PersonajeDibujable* personajeDibujable;
public:
	Jugador();
	Jugador(Personaje* personaje, PersonajeDibujable* personajeDibujable);
	virtual ~Jugador();
	Personaje* getPersonaje() const;
	void setPersonaje(Personaje* personaje);
	PersonajeDibujable* getPersonajeDibujable() const;
	void setPersonajeDibujable(PersonajeDibujable* personajeDibujable);
	void posicionarPersonaje_enEjeX(double x);
};

#endif /* SRC_MODELO_JUGADOR_H_ */
