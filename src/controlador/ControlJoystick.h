/*
 * ControlJoystick.h
 *
 *  Created on: 11/5/2015
 *      Author: ariel
 */

#ifndef SRC_CONTROLADOR_CONTROLJOYSTICK_H_
#define SRC_CONTROLADOR_CONTROLJOYSTICK_H_

#include "Control.h"

class ControlDef;

class ControlJoystick: public Control {
public:
	ControlJoystick();
	ControlJoystick(ControlDef* controlDef);
	virtual ~ControlJoystick();
};

#endif /* SRC_CONTROLADOR_CONTROLJOYSTICK_H_ */
