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

using namespace std;

class JugadorDef: public Loggeable {
private:
	string idPersonaje; // id del personaje al cual va a estar asociado
public:
	JugadorDef();
	JugadorDef(string personaje);
	virtual ~JugadorDef();
	friend ostream& operator<<(ostream &o, const JugadorDef &j);
	string toString();
	string getIdPersonaje() const;
};

#endif /* SRC_JSON_JUGADORDEF_H_ */
