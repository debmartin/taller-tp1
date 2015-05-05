/*
 * Jugador.h
 *
 *  Created on: 5/5/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_JUGADOR_H_
#define SRC_MODELO_JUGADOR_H_

#include <iostream>
#include <string>
using namespace std;

class Personaje;
class PersonajeDibujable;

class Jugador {
private:
	Personaje* personaje;
	PersonajeDibujable* personajeDibujable;
	int direccion;
public:
	Jugador();
	Jugador(Personaje* personaje, PersonajeDibujable* personajeDibujable, int direccion);
	virtual ~Jugador();
	int getDireccion() const;
	void setDireccion(int direccion);
	Personaje* getPersonaje() const;
	void setPersonaje(Personaje* personaje);
	PersonajeDibujable* getPersonajeDibujable() const;
	void setPersonajeDibujable(PersonajeDibujable* personajeDibujable);
};

#endif /* SRC_MODELO_JUGADOR_H_ */
