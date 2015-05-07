/*
 * ArmaDibujable.h
 *
 *  Created on: 2/5/2015
 *      Author: val
 */

#ifndef SRC_VISTA_ARMADIBUJABLE_H_
#define SRC_VISTA_ARMADIBUJABLE_H_

#include "Sprite.h"
#include "Dibujable.h"
#include "../modelo/Arma.h"
#include "../modelo/Observable.h"
#include "VentanaGrafica.h"

class ArmaDibujable: public Observador {
private:
	Sprite* armaDibujable;
	estado_objeto estado;
public:
	ArmaDibujable();
	ArmaDibujable(Sprite* armaDib);
	virtual ~ArmaDibujable();
	void dibujar();
	void actualizar();
	void cambiarEstado(estado_objeto estado);
	void recibirNotificacion(Observable* unObservable);
};

#endif /* SRC_VISTA_ARMADIBUJABLE_H_ */
