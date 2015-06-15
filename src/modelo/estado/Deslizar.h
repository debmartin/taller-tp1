/*
 * Deslizar.h
 *
 *  Created on: 1/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_DESLIZAR_H_
#define SRC_MODELO_ESTADO_DESLIZAR_H_

#include "Estado.h"
#include "../MRU.h"

class Deslizar : public Estado
{
    public:
		Deslizar(Vector2f posInicial, estado_personaje estado, BVH* caja, bool direccion);
		Deslizar(Vector2f posInicial, estado_personaje estado, BVH* caja, bool direccion, float velocidad_horizontal);
        virtual ~Deslizar();
        bool estaAtacando();
        bool haciendoFatality();
    protected:
    private:
};

#endif /* SRC_MODELO_ESTADO_DESLIZAR_H_ */
