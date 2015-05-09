/*
 * ArmaDef.h
 *
 *  Created on: 9/5/2015
 *      Author: val
 */

#ifndef SRC_JSON_ARMADEF_H_
#define SRC_JSON_ARMADEF_H_

#include "SpriteDef.h"

class ArmaDef {
private:
	SpriteDef* spriteArma;
	int velocidadArma;
public:
	ArmaDef();
	ArmaDef(SpriteDef* unArma, int velocidad);
	virtual ~ArmaDef();
	SpriteDef* getSpriteDefArma();
	int getVelocidad();
};

#endif /* SRC_JSON_ARMADEF_H_ */
