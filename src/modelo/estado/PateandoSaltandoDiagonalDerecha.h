/*
 * PateandoSaltandoDiagonalDerecha.h
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_PATEANDOSALTANDODIAGONALDERECHA_H_
#define SRC_MODELO_ESTADO_PATEANDOSALTANDODIAGONALDERECHA_H_

#include "Estado.h"

class PateandoSaltandoDiagonalDerecha: public Estado {
public:
	PateandoSaltandoDiagonalDerecha(Trayectoria* trayectoriaActual, BVH* caja);
	PateandoSaltandoDiagonalDerecha(Vector2f posInicial, BVH* caja);
	virtual ~PateandoSaltandoDiagonalDerecha();
	bool estaAtacando();
	bool estaSaltando();
	bool estaSaltandoDiagonalDerecha();
};

#endif /* SRC_MODELO_ESTADO_PATEANDOSALTANDODIAGONALDERECHA_H_ */
