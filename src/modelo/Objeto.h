/*
 * Objeto.h
 *
 *  Created on: 28/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_OBJETO_H_
#define SRC_MODELO_OBJETO_H_

#include "Trayectoria.h"
#define VELOCIDAD_OBJETO Vector2f(10,10)

class Objeto {
public:
	Objeto();
	Objeto(Vector2f posicion);
	virtual ~Objeto();
	int quitarEnergia();
};

#endif /* SRC_MODELO_OBJETO_H_ */
