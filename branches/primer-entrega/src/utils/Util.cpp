/*
 * Util.cpp
 *
 *  Created on: 7/4/2015
 *      Author: ariel
 */

#include "Util.h"

#include <cstdio>

Util* Util::instancia = NULL;

Util::Util() {
	// TODO Auto-generated constructor stub

}

Util* Util::getInstancia() {
	if ( Util::instancia  == NULL )
		Util::instancia = new Util();
	return Util::instancia;
}

bool Util::existeArchivo(string ruta_archivo) {
	FILE* fd = fopen(ruta_archivo.c_str(),"r");
	return ( fd != NULL );
}

Util::~Util() {
	// TODO Auto-generated destructor stub
}

