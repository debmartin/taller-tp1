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
	PateandoSaltandoDiagonalIzquierda(Trayectoria* trayectoriaActual, float tiempoDeCreacion, BVH* caja);
	PateandoSaltandoDiagonalIzquierda(Vector2f posInicial, BVH* caja);
	virtual ~PateandoSaltandoDiagonalIzquierda();
	bool estaAtacando();
	bool estaSaltando();
	bool estaSaltandoDiagonalIzquierda();
	bool ejecutandoMovimientoEspecial();
};

#endif /* SRC_MODELO_ESTADO_PATEANDOSALTANDODIAGONALIZQUIERDA_H_ */
