/*
 * PateandoSaltandoDiagonalIzquierda.h
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_PATEANDOSALTANDODIAGONALIZQUIERDA_H_
#define SRC_MODELO_ESTADO_PATEANDOSALTANDODIAGONALIZQUIERDA_H_

#include "Estado.h"

class PateandoSaltandoDiagonalIzquierda : public Estado {
public:
	PateandoSaltandoDiagonalIzquierda(Vector2f posInicial, BVH* caja);
	virtual ~PateandoSaltandoDiagonalIzquierda();
	bool estaAtacando();
	bool estaSaltando();
	bool estaSaltandoDiagonal();
};

#endif /* SRC_MODELO_ESTADO_PATEANDOSALTANDODIAGONALIZQUIERDA_H_ */
