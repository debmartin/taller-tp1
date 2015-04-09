/*
 * Parser.h
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#ifndef SRC_JSON_PARSER_H_
#define SRC_JSON_PARSER_H_

#include <jsoncpp/json/reader.h>
#include <jsoncpp/json/value.h>
#include <list>
#include <string>

#include "../modelo/Capa.h"

class Escenario;
class Personaje;
class Ventana;

using namespace std;

class Parser {
private:
	Json::Value root;
	Json::Reader reader;
	string entrada;

	//objectos que devolvera el parseador json
	Ventana* ventana;
	Escenario * escenario;
	list<Capa*>* capas;
	Personaje* personaje;


public:
	Parser();
	Parser(string archivo_json);

	list<Capa*>* getCapas() const;
	Escenario* getEscenario() const;
	Personaje* getPersonaje() const;
	Ventana* getVentana() const;

	void parsearDesdeJson();

	virtual ~Parser();
	const Json::Reader& getReader() const;
	const Json::Value& getRoot() const;
	double getPersonajeSpritesAncho() const;
	void setPersonajeSpritesAncho(double personajeSpritesAncho);

private:
	void inicializar();
	void inciarValidacionSemantica();

};

#endif /* SRC_JSON_PARSER_H_ */
