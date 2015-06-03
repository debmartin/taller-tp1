/*
 * Muerto.h
 *
 *  Created on: 2/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_MUERTO_H_
#define SRC_MODELO_ESTADO_MUERTO_H_

#include "Estado.h"
#include "../Reposo.h"

class Muerto : public Estado
{
    public:
                Muerto(Vector2f posInicial, BVH* caja);
                Muerto(Vector2f posInicial, estado_personaje estado,BVH* caja);
        virtual ~Muerto();
        bool estaEnPiso();
    protected:
    private:
};

#endif /* SRC_MODELO_ESTADO_MUERTO_H_ */
