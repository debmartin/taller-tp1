/*
 * Caida.h
 *
 *  Created on: 23/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_CAIDA_H_
#define SRC_MODELO_ESTADO_CAIDA_H_

#include "Estado.h"

class Caida: public Estado {
public:
	Caida(Trayectoria* trayectoriaActual, float tiempoDeCreacion, BVH* caja);
	virtual ~Caida();
};

#endif /* SRC_MODELO_ESTADO_CAIDA_H_ */
