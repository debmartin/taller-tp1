/*
 * Logger.h
 *
 *  Created on: Mar 31, 2015
 *      Author: ariel
 */

/**
 * Clase singleton que permite hacer logging de mensajes
 * sobre uno o varios archivos de log
 */

#ifndef SRC_UTILS_LOGGER_H_
#define SRC_UTILS_LOGGER_H_

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <sstream>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "../json/ObjetoJson.h";

#include <jsoncpp/json/json.h>
using namespace std;

/**
 * Definición
 */
class Logger {

/* Miembros privados de la clase Logger*/
private:
	/**
	 * Instancia singleton de la clase Logger.
	 */
	static Logger* logger;

	/*
	 * Numero del proximo archivo de log
	 */
	int nextFile;

	/*
	 * Numero de registros en archivo de log actual
	 */
	int count;

	/*
	 * Numero de registros maximo en archivo de log
	 */
	static int limit;

	/**
	 * Almacena un stream de salida sobre el archivo de log.
	 */
	std::fstream ioFile;

	/**
	 * Constructor privado de la clase Logger.
	 */
	Logger();

	/*
	 * Se encarga de cerrar el archivo actual, lo renombra y lo vuelve a abrir.
	 */
	void renameFile();

	/*
	 * Obtiene el Valor del siguiente archivo de Log
	 */
	int setNextFile();

	/*
	 * Arma el string con la fecha y hora actuales.
	 */
	std::string getTime();

	/*
	 * para definir los niveles de logging con los siguientes valores y orden:
	 * 1) DEBUG
	 * 2) INFO
	 * 3) ERROR
	 */
	std::string nivel_log;

/*Miembros publicos de la clase Logger*/
public:
	/**
	 * Devuelve la unica instancia del singleton.
	 */
	static Logger* getInstance();

	/**
	 * Setea la cantidad de registros
	 */
	static void setLimit(int cantRegistros);

	/**
	 * Escribe un mensaje de debug sobre el log.
	 */
	void debug(std::string message);
	void debug(ObjetoJson* unObjetoJson);

	/**
	 * Escribe un mensaje de informacion sobre el log.
	 */
	void info(std::string message);
	void info(ObjetoJson* unObjetoJson);

	/**
	 * Escribe un mensaje de error sobre el log.
	 */
	void error(std::string message);
	void error(ObjetoJson* unObjetoJson);
	/**
	 * Inserta un mensaje en el archivo de log.
	 */
	void insert(std::string& key, std::string& value);

	/**
	 * Destructor virtual de la clase Logger.
	 */
	virtual ~Logger();

};

#endif /* SRC_UTILS_LOGGER_H_ */
