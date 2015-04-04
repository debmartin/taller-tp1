/*
 * LoggerTest.cpp
 *
 *  Created on: 4/4/2015
 *      Author: ariel
 */

#include "../src/utils/Logger.h"
#include "LoggerTest.h"

LoggerTest::LoggerTest() {
	// TODO Auto-generated constructor stub

}

void LoggerTest::ejecutar() {

	/*
	 * En el archivo src/recursos/configuracion.json se encuentra el parametro "nivel_debug" que define el nivel de logeo.
	 * Los mensajes de logging se cargar en logger.log que se encuentra en el duirectorio raiz.
	 *
	 * Ejemplo 1: si se elige nivel_debug": "ERROR", solo logean los mensajes de error.
	 *
	 * Ejemplo 2: si se elige nivel_debug": "INFO", se logean los mensajes de informacion, warning y error.
	 *
	 * Ejemplo 3: si se elige nivel_debug": "INFO", se logean todos los mensajes.
	 */

	Logger::getInstance()->debug("mensaje de debug");
	Logger::getInstance()->info("mensaje de informacion");
	Logger::getInstance()->warn("mensaje de warning");
	Logger::getInstance()->error("mensaje de error");
}

LoggerTest::~LoggerTest() {
	// TODO Auto-generated destructor stub
}

