/*
 * PateandoAltoAgachado.h
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_PATEANDOALTOAGACHADO_H_
#define SRC_MODELO_ESTADO_PATEANDOALTOAGACHADO_H_

#include "Estado.h"
#include "../Reposo.h"

class PateandoAltoAgachado : public Estado
{
	public:
		PateandoAltoAgachado(Vector2f posInicial, BVH* caja);
		virtual ~PateandoAltoAgachado();
		bool estaAtacando();
		bool estaAgachado();
		bool ejecutandoMovimientoEspecial();
};

#endif /* SRC_MODELO_ESTADO_PATEANDOALTOAGACHADO_H_ */
