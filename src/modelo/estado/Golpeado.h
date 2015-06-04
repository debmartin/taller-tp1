/*
 * Golpeado.h
 *
 *  Created on: 22/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_GOLPEADO_H_
#define SRC_MODELO_ESTADO_GOLPEADO_H_

#include "Estado.h"
#include "../Reposo.h"


class Golpeado : public Estado
{
    public:
		Golpeado(Vector2f posInicial, BVH* caja);
		Golpeado(Vector2f posInicial, estado_personaje estado, BVH* caja);
        virtual ~Golpeado();
        bool estaEsperando();
        bool estaGolpeado();
    protected:
    private:
};

#endif /* SRC_MODELO_ESTADO_GOLPEADO_H_ */
