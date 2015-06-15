/*
 * VueloVertical.h
 *
 *  Created on: 14/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_VUELOVERTICAL_H_
#define SRC_MODELO_ESTADO_VUELOVERTICAL_H_

#include "Estado.h"

class VueloVertical: public Estado {
public:
	VueloVertical(Vector2f posInicial, estado_personaje estado, BVH* caja);
	virtual ~VueloVertical();
	bool estaVolandoVertical();
};

#endif /* SRC_MODELO_ESTADO_VUELOVERTICAL_H_ */
