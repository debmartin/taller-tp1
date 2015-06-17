/*
 * EfectosEspeciales.h
 *
 *  Created on: 12/6/2015
 *      Author: val
 */

#ifndef SRC_VISTA_EFECTOSESPECIALES_H_
#define SRC_VISTA_EFECTOSESPECIALES_H_

#include <iostream>
#include <map>

#include "Efecto.h"
#include "EfectoSangre.h"

using namespace std;

class EfectosEspeciales {
private:
	// SINGLETON
	EfectosEspeciales();
	static EfectosEspeciales* instancia_unica;
	std::map<string, Efecto*>* mapaEfectosEspeciales;

public:
	virtual ~EfectosEspeciales();
	static EfectosEspeciales* Instance();
	void dibujar();
	void update();
	void ejecutarEfecto(string id, Vector2f pos);
	bool init();
};

#endif /* SRC_VISTA_EFECTOSESPECIALES_H_ */
