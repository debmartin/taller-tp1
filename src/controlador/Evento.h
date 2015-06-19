/*
 * Evento.h
 *
 *  Created on: 18/6/2015
 *      Author: gaston
 */

#ifndef SRC_CONTROLADOR_EVENTO_H_
#define SRC_CONTROLADOR_EVENTO_H_
#include <iostream>
#include "Evento.h"

using namespace std;

class Evento {
public:
	Evento(string nombreEvento);
	virtual ~Evento();

	void colorear();
	bool estaColoreado();
	string getNombre();

private:
	Evento();
	string nombre;
	bool coloreado;
};

#endif /* SRC_CONTROLADOR_EVENTO_H_ */
