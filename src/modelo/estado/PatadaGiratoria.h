/*
 * PatadaGiratoria.h
 *
 *  Created on: 10/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_PATADAGIRATORIA_H_
#define SRC_MODELO_ESTADO_PATADAGIRATORIA_H_

#include "Estado.h"
#include "../Reposo.h"

class PatadaGiratoria : public Estado
{
	public:
		PatadaGiratoria(Vector2f posInicial, BVH* caja);
		virtual ~PatadaGiratoria();
		bool estaAtacando();
		bool estaAgachado();
		bool ejecutandoMovimientoEspecial();
		bool efectuandoPatadaGiratoria();
};
#endif /* SRC_MODELO_ESTADO_PATADAGIRATORIA_H_ */
