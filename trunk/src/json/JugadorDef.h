/*
 * JugadorDef.h
 *
 *  Created on: 1/5/2015
 *      Author: ariel
 */

#ifndef SRC_JSON_JUGADORDEF_H_
#define SRC_JSON_JUGADORDEF_H_

#include <iostream>
#include <string>

#define DIRECCION_JUGADOR_DERECHA 1
#define DIRECCION_JUGADOR_IZQUIERDA -1

#include "../utils/Loggeable.h"

using namespace std;

class JugadorDef: public Loggeable {
private:
	string idPersonaje; // id del personaje al cual va a estar asociado
	int direccion;

public:
	JugadorDef();
	JugadorDef(string personaje, int direccion);
	virtual ~JugadorDef();
	friend ostream& operator<<(ostream &o, const JugadorDef &j);
	string toString();
	string getIdPersonaje() const;
	int getDireccion() const;
	void setDireccion(int direccion);
};

#endif /* SRC_JSON_JUGADORDEF_H_ */
