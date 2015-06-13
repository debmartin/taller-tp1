/*
 * RecibiendoFatality.h
 *
 *  Created on: 13/6/2015
 *      Author: val
 */

#ifndef SRC_MODELO_ESTADO_RECIBIENDOFATALITY_H_
#define SRC_MODELO_ESTADO_RECIBIENDOFATALITY_H_

#include "Estado.h"
#include "../../utils/Logger.h"

class RecibiendoFatality : public Estado
{
    public:
		RecibiendoFatality(Vector2f posInicial, estado_personaje estado,BVH* caja);
        virtual ~RecibiendoFatality();
        bool estaEsperando();
        bool ejecutandoMovimientoEspecial();
        bool recibioFatality();
};
#endif /* SRC_MODELO_ESTADO_RECIBIENDOFATALITY_H_ */
