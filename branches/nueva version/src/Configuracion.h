/*
 * Configuracion.h
 *
 *  Created on: 20/3/2015
 *      Author: ariel
 */

#ifndef SRC_CONFIGURACION_H_
#define SRC_CONFIGURACION_H_

#include <jsoncpp/json/json.h>
#include <string>
using namespace std;

class Configuracion {
private:
	static Configuracion* configuracion;
	Configuracion();
	string nivel_logger;
	void cargar();
public:
	static Configuracion* getInstance();

	virtual ~Configuracion();

	string getNivelLogger();
};

#endif /* SRC_CONFIGURACION_H_ */