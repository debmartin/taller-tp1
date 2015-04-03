/*
 * Parser.h
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#ifndef SRC_JSON_PARSER_H_
#define SRC_JSON_PARSER_H_

#include <jsoncpp/json/json.h>
#include <list>
#include <string>

#include "../../src/modelo/Capa.h"
#include "../../src/modelo/Escenario.h"
#include "../../src/modelo/Personaje.h"
#include "../../src/vista/VentanaGrafica.h"

#define NOMBRE_ARCHIVO_DEFECTO "archivo_json_defecto"

using namespace std;

class Parser {
private:
	Json::Value root;
	Json::Reader reader;
	bool bienParseado;
	string entrada;

	//objectos que devolvera el parseador json
	VentanaGrafica* ventana;
	Escenario * escenario;
	list<Capa*>* capas;
	Personaje* personaje;


public:
//	Parser();
	Parser(string archivo_json  = NOMBRE_ARCHIVO_DEFECTO);

	list<Capa*>* getCapas() const;
	Escenario* getEscenario() const;
	Personaje* getPersonaje() const;
	VentanaGrafica* getVentana() const;

	void parsearDesdeJson();

	virtual ~Parser();
	const Json::Reader& getReader() const;
	const Json::Value& getRoot() const;
	double getPersonajeSpritesAncho() const;
	void setPersonajeSpritesAncho(double personajeSpritesAncho);

private:
	void inicializar();

};

#endif /* SRC_JSON_PARSER_H_ */
