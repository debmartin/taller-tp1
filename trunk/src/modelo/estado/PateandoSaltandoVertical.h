/*
 * PateandoSaltandoVertical.h
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_PATEANDOSALTANDOVERTICAL_H_
#define SRC_MODELO_ESTADO_PATEANDOSALTANDOVERTICAL_H_

#include "Estado.h"

class PateandoSaltandoVertical: public Estado {
public:
	PateandoSaltandoVertical(Vector2f posInicial, BVH* caja);
	virtual ~PateandoSaltandoVertical();
	bool estaAtacando();
	bool estaDefendiendo();
};

#endif /* SRC_MODELO_ESTADO_PATEANDOSALTANDOVERTICAL_H_ */
