/*
 * Poder.cpp
 *
 *  Created on: 28/4/2015
 *      Author: val
 */

#include "Poder.h"

Poder::Poder() {
	// TODO Auto-generated constructor stub

}

void Poder::ejecutar(Objeto* objeto){
	objeto->update();
}

Poder::~Poder() {
	// TODO Auto-generated destructor stub
}

