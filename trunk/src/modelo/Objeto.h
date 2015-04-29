/*
 * Objeto.h
 *
 *  Created on: 28/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_OBJETO_H_
#define SRC_MODELO_OBJETO_H_


#include "Trayectoria.h"

#define POS_INICIAL_OBJETO Vector2f(0,0)
#define VELOCIDAD_OBJETO Vector2f(10,10)

class Objeto {
public:
	Objeto();
	Objeto(Vector2f posicion);
	virtual ~Objeto();
	virtual void posicionar(Vector2f posicion) = 0;
	virtual int quitarEnergia() = 0;
	virtual void update() = 0;
};

#endif /* SRC_MODELO_OBJETO_H_ */
