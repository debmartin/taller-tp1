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

#include "../json/CapaDef.h"

class EscenarioDef;
class PersonajeDef;
class VentanaDef;

using namespace std;

class Parser {
private:
	Json::Value root;
	Json::Reader reader;
	string entrada;

	//objectos que devolvera el parseador json
	VentanaDef* ventana;
	EscenarioDef * escenario;
	list<CapaDef*>* capas;
	list<PersonajeDef*>* personajes;

public:
	Parser();
	Parser(string archivo_json);

	list<CapaDef*>* getCapasDef() const;
	EscenarioDef* getEscenarioDef() const;
	list<PersonajeDef*>* getPersonajesDef() const;
	VentanaDef* getVentanaDef() const;

    void cargarJsonPorDefecto();
	bool parsearDesdeJson();

	virtual ~Parser();
	const Json::Reader& getReader() const;
	const Json::Value& getRoot() const;
	double getPersonajeDefSpritesAncho() const;
	void setPersonajeDefSpritesAncho(double personajeSpritesAncho);

private:
	void inicializar();
	void inciarValidacionSemantica();

};

#endif /* SRC_JSON_PARSER_H_ */
