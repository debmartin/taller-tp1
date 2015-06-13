/*
 * TomandoOponente.h
 *
 *  Created on: 12/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_TOMANDOOPONENTE_H_
#define SRC_MODELO_ESTADO_TOMANDOOPONENTE_H_

#include "Estado.h"

class TomandoOponente: public Estado {
public:
	TomandoOponente(Vector2f posInicial, estado_personaje estado,BVH* caja);
	virtual ~TomandoOponente();
	bool estaTomandoAlOponente();
	bool ejecutandoMovimientoEspecial();
	bool estaAtacando();
};

#endif /* SRC_MODELO_ESTADO_TOMANDOOPONENTE_H_ */
