/*
 * Sonidos.h
 *
 *  Created on: 5/6/2015
 *      Author: ariel
 */

#ifndef SRC_SONIDOS_H_
#define SRC_SONIDOS_H_

#include <map>
#include <string>

#include "Sonido.h"

class Sonidos {
private:
	static Sonidos* sonidos;
	Sonidos();
	map<string,Sonido*>* mapaSonidos;
public:
	static Sonidos* getInstancia();
	void agregar(string idSonido, Sonido* sonido);
	void reproducirSonido(string idSonido);
	virtual ~Sonidos();
};

#endif /* SRC_SONIDOS_H_ */
