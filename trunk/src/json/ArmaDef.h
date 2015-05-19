/*
 * ArmaDef.h
 *
 *  Created on: 9/5/2015
 *      Author: val
 */

#ifndef SRC_JSON_ARMADEF_H_
#define SRC_JSON_ARMADEF_H_

#include "SpriteDef.h"
#define VELOCIDAD_ARMA_DEFAULT 50
#define ALTO_ARMA_DEFAULT 50
#define ANCHO_ARMA_DEFAULT 50

class ArmaDef {
private:
	SpriteDef* spriteArma;
	double alto;
	double ancho;
	int velocidadArma;
public:
	ArmaDef();
	ArmaDef(SpriteDef* unArma, int velocidad, double ancho, double alto);
	virtual ~ArmaDef();
	SpriteDef* getSpriteDefArma();
	double getAlto();
	double getAncho();
	int getVelocidad();
};

#endif /* SRC_JSON_ARMADEF_H_ */
