/*
 * Posicion.h
 *
 *  Created on: 21/5/2015
 *      Author: ariel
 */

#ifndef SRC_MODELO_POSICION_H_
#define SRC_MODELO_POSICION_H_

#include <iostream>
#include <string>

#include "../utils/Loggeable.h"

using namespace std;

class Posicion: public Loggeable {
private:
	int x;
	int y;
	bool enfocado;
	bool elegido;
public:
	Posicion(int x, int y);
	virtual ~Posicion();
	int getX() const;
	int getY() const;

	bool estoyEnfocado();
	void enfocar();
	void desenfocar();

	bool estoyElegido();
	void elegir();
	void deselegir();

	void enfocarIzquierda();
	void enfocarDerecha();
	void enfocarArriba();
	void enfocarAbajo();

	friend ostream& operator<<(ostream &o, const Posicion &p);
	string toString();

};

#endif /* SRC_MODELO_POSICION_H_ */
