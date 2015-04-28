/*
 * Cuchillo.h
 *
 *  Created on: 28/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_CUCHILLO_H_
#define SRC_MODELO_CUCHILLO_H_

#include "Objeto.h"
#include "MRU.h"

#define DANIO_CUCHILLO	10

class Cuchillo: public Objeto {
private:
	int damage;
	Vector2f posicion;
	Trayectoria* trayectoria;
	float tCreacion;

public:
	Cuchillo(Vector2f posicion);
	virtual ~Cuchillo();
	int quitarEnergia();
};

#endif /* SRC_MODELO_CUCHILLO_H_ */
