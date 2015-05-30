/*
 * Poder.h
 *
 *  Created on: 28/4/2015
 *      Author: val
 */

#ifndef SRC_MODELO_PODER_H_
#define SRC_MODELO_PODER_H_

#include "Objeto.h"

#define DANIO_BOLA_DE_HIELO 50
#define DANIO_BOLA_DE_FUEGO 50
#define DANIO_CUCHILLO 20

class Poder {
public:
	Poder();
	virtual ~Poder();
	void ejecutar(Objeto* objeto);
};

#endif /* SRC_MODELO_PODER_H_ */
