/*
 * Fatality.h
 *
 *  Created on: 10/6/2015
 *      Author: Juan
 */

#ifndef SRC_MODELO_FATALITY_H_
#define SRC_MODELO_FATALITY_H_

#include "Orden.h"
#include "unistd.h"
#include "modelo/contenedores/Cola.h"
#include "string.h"
//#include "string"

using namespace std;

class Fatality: public Orden {
private:
	string nombre;
	Cola* Movimientos;
	Personaje* Oponente;
	Personaje* Ejecutante;

public:
	Fatality(Personaje* unoponente, Personaje* unpersonaje,Cola* movimientos);
	virtual ~Fatality();
	void Ejecutar();
};
#endif /* SRC_MODELO_FATALITY_H_ */
