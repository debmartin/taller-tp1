/*
 * CaidaDerecha.h
 *
 *  Created on: 28/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_CAIDADERECHA_H_
#define SRC_MODELO_ESTADO_CAIDADERECHA_H_

#include "Estado.h"

class CaidaDerecha : public Estado
{
    public:
		CaidaDerecha(Vector2f posInicial, BVH* caja);
		CaidaDerecha(Vector2f posInicial, float velocidadEnY, BVH* caja);
		CaidaDerecha(Vector2f posInicial, estado_personaje estado , BVH* caja);
        virtual ~CaidaDerecha();
        bool estaSaltando();
        bool estaSaltandoDiagonalDerecha();
        bool estaEnCaida();
    protected:
    private:
};

#endif /* SRC_MODELO_ESTADO_CAIDADERECHA_H_ */
