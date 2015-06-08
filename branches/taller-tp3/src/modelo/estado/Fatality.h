/*
 * Fatality.h
 *
 *  Created on: 7/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_FATALITY_H_
#define SRC_MODELO_ESTADO_FATALITY_H_

#include "Estado.h"
#include "../../utils/Logger.h"

class Fatality : public Estado
{
    public:
		Fatality(Vector2f posInicial, estado_personaje estado,BVH* caja);
        virtual ~Fatality();
        bool estaEsperando();
        bool haciendoFatality();
    protected:
    private:
};

#endif /* SRC_MODELO_ESTADO_FATALITY_H_ */
