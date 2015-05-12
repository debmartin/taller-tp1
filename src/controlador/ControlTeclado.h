/*
 * ControlTeclado.h
 *
 *  Created on: 11/5/2015
 *      Author: ariel
 */

#ifndef SRC_CONTROLADOR_CONTROLTECLADO_H_
#define SRC_CONTROLADOR_CONTROLTECLADO_H_

#include "Control.h"

class ControlDef;

class ControlTeclado: public Control {
public:
	ControlTeclado();
	ControlTeclado(ControlDef* controlDef);
	virtual ~ControlTeclado();
};

#endif /* SRC_CONTROLADOR_CONTROLTECLADO_H_ */
