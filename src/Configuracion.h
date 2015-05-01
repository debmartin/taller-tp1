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
#include <iostream> // TODO: Lo agrego yo Gaston para que compile la linea 34 de Configuracion.cpp

using namespace std;

class Configuracion {
private:
	static Configuracion* configuracion;
	Configuracion();
	string nivel_logger;
	string pisar_logs;
public:
	static Configuracion* getInstance();
	virtual ~Configuracion();
	string getNivelLogger();
	string getPisarLogs();

private:
	void cargar();
};

#endif /* SRC_CONFIGURACION_H_ */
