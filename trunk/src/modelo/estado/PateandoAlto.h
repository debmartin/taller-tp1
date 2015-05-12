/*
 * PateandoAlto.h
 *
 *  Created on: 12/5/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_PATEANDOALTO_H_
#define SRC_MODELO_ESTADO_PATEANDOALTO_H_

#include "Estado.h"

class PateandoAlto : public Estado
{
    public:
        PateandoAlto(Vector2f posInicial, BVH* caja);
        virtual ~PateandoAlto();
        bool estaAtacando();
        bool estaDefendiendo();
};

#endif /* SRC_MODELO_ESTADO_PATEANDOALTO_H_ */
