/*
 * Mareado.h
 *
 *  Created on: 10/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_MAREADO_H_
#define SRC_MODELO_ESTADO_MAREADO_H_

#include "Estado.h"
#include "../Reposo.h"

class Mareado: public Estado {
 public:
		Mareado(Vector2f posInicial, BVH* caja);
		Mareado(Vector2f posInicial, estado_personaje estado, BVH* caja);
        virtual ~Mareado();
        bool estaEsperando();
        bool estaGolpeado();
        bool estaMareado();
    protected:
    private:
};
#endif /* SRC_MODELO_ESTADO_MAREADO_H_ */
