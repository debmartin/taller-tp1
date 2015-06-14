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

#include "../utils/Loggeable.h"

class ControlDef;

using namespace std;

class JugadorDef: public Loggeable {
private:
	string id;
	string idPersonaje; // id del personaje al cual va a estar asociado
	string tipo_control;
	int tolerancia;
	ControlDef* controlDef;

public:
	JugadorDef();
	JugadorDef(string id, string tipo_control, int tolerancia, ControlDef* controlDef);
	virtual ~JugadorDef();
	friend ostream& operator<<(ostream &o, const JugadorDef &j);
	string toString();
	string getIdPersonaje() const;
	ControlDef* getControlDef() const;
	int getTolerancia() const;
	string getTipoControl() const;
	void cargarIdPersonajeDesdeMenu(string nuevoIdPersonaje);
	string getId() const;
};

#endif /* SRC_JSON_JUGADORDEF_H_ */
