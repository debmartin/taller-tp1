/*
 * ArmaDibujable.h
 *
 *  Created on: 2/5/2015
 *      Author: val
 */

#ifndef SRC_VISTA_ARMADIBUJABLE_H_
#define SRC_VISTA_ARMADIBUJABLE_H_

#include "Sprite.h"

class ArmaDibujable {
private:
	Sprite* armaDibujable;
public:
	ArmaDibujable();
	ArmaDibujable(Sprite* armaDib);
	virtual ~ArmaDibujable();
};

#endif /* SRC_VISTA_ARMADIBUJABLE_H_ */
