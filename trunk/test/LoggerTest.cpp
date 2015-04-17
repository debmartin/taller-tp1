/*
 * LoggerTest.cpp
 *
 *  Created on: 4/4/2015
 *      Author: ariel
 */

#include "../src/utils/Logger.h"
#include "LoggerTest.h"

#include "../src/json/CapaDef.h"
#include "../src/json/EscenarioDef.h"
#include "../src/json/PersonajeDef.h"
#include "../src/json/SpriteDef.h"
#include "../src/json/VentanaDef.h"

LoggerTest::LoggerTest() {

}

void LoggerTest::ejecutar() {

	/*
	 * En el archivo src/recursos/configuracion.json se encuentra el parametro "nivel_debug" que define el nivel de logeo.
	 * Los mensajes de logging se cargan en logger.log que se encuentra en el directorio raiz.
	 *
	 * Ejemplo 1: si se elige nivel_debug": "ERROR", solo logean los mensajes de error.
	 *
	 * Ejemplo 2: si se elige nivel_debug": "INFO", se logean los mensajes de informacion, warning y error.
	 *
	 * Ejemplo 3: si se elige nivel_debug": "DEBUG", se logean todos los mensajes.
	 */

	Logger::getInstance()->debug("mensaje de debug");
	Logger::getInstance()->info("mensaje de informacion");
	Logger::getInstance()->error("mensaje de error");

	//ejemplo de logeo de objetos directamente
	VentanaDef* ventanaDef = new VentanaDef();
	EscenarioDef* escenarioDef = new EscenarioDef();
	CapaDef* capaDef = new CapaDef();
	PersonajeDef* personajeDef = new PersonajeDef();
	SpriteDef* spriteDef = new SpriteDef();

	Logger::getInstance()->info(ventanaDef);
	Logger::getInstance()->info(escenarioDef);
	Logger::getInstance()->info(capaDef);
	Logger::getInstance()->info(personajeDef);
	Logger::getInstance()->info(spriteDef);
}

LoggerTest::~LoggerTest() {
	// TODO Auto-generated destructor stub
}

