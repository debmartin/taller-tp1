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

#define JSON_POR_DEFECTO "src/recursos/escenario_defecto.json"
#define TAG_CAPAS "capas"
#define TAG_ESCENARIO "escenario"
#define TAG_VENTANA "ventana"
#define TAG_PERSONAJE_1 "personaje-1"
#define TAG_PERSONAJE_2 "personaje-2"
#define TAG_CAPAS_IMAGEN "imagen_fondo"
#define TAG_CAPAS_ID "id_capa"
#define TAG_CAPAS_ANCHO "ancho"
#define TAG_ESCENARIO_ALTO "alto"
#define TAG_ESCENARIO_ANCHO "ancho"
#define TAG_ESCENARIO_YPISO "y_piso"
#define TAG_VENTANA_ALTOPX "altopx"
#define TAG_VENTANA_ANCHOPX "anchopx"
#define TAG_VENTANA_ANCHO "ancho"
#define TAG_PERSONAJE_ALTO "alto"
#define TAG_PERSONAJE_ANCHO "ancho"
#define TAG_PERSONAJE_ZINDEX "zindex"
#define TAG_PERSONAJE_SPRITES "sprites-"
#define TAG_PERSONAJE_SPRITES_CANT_FOTOGRAMAS "cant_fotogramas"
#define TAG_PERSONAJE_SPRITES_FPS "fps"
#define TAG_PERSONAJE_SPRITES_IMAGEN "imagen"
#define TAG_PERSONAJE_DIRECCION "direccion"




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
	//PersonajeDef* personaje;

	list<PersonajeDef*>* personajesDef;

public:
	Parser();
	Parser(string archivo_json);

	list<CapaDef*>* getCapasDef() const;
	EscenarioDef* getEscenarioDef() const;
	//PersonajeDef* getPersonajeDef() const;
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

    void parsearCapas();
    void parsearVentana();
    void parsearEscenario();
    PersonajeDef* parsearPersonaje(string tag_personaje);
    void parsearPersonajes();

};

#endif /* SRC_JSON_PARSER_H_ */
