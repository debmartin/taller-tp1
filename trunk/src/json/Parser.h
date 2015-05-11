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

#include "CapaDef.h"
#include "JugadorDef.h"
#include "PersonajeDef.h"

#define JSON_POR_DEFECTO "src/recursos/escenario_defecto.json"
#define TAG_CAPAS "capas"
#define TAG_PERSONAJES "personajes"
#define TAG_ESCENARIO "escenario"
#define TAG_VENTANA "ventana"
#define TAG_CAPAS_IMAGEN "imagen_fondo"
#define TAG_CAPAS_ID "id_capa"
#define TAG_CAPAS_ANCHO "ancho"
#define TAG_ESCENARIO_ALTO "alto"
#define TAG_ESCENARIO_ANCHO "ancho"
#define TAG_ESCENARIO_YPISO "y_piso"
#define TAG_VENTANA_ALTOPX "altopx"
#define TAG_VENTANA_ANCHOPX "anchopx"
#define TAG_VENTANA_ANCHO "ancho"
#define TAG_PERSONAJE_ID "id_personaje"
#define TAG_PERSONAJE_ALTO "alto"
#define TAG_PERSONAJE_ANCHO "ancho"
#define TAG_PERSONAJE_ZINDEX "zindex"
#define TAG_PERSONAJE_SPRITES "sprites-"
#define TAG_PERSONAJE_SPRITES_CANT_FOTOGRAMAS "cant_fotogramas"
#define TAG_PERSONAJE_SPRITES_FPS "fps"
#define TAG_PERSONAJE_SPRITES_IMAGEN "imagen"
#define TAG_PERSONAJE_ARMA "arma"
#define TAG_PERSONAJE_VELOCIDAD_ARMA "velocidad"
#define TAG_COLOR_ALTERNATIVO "color-alternativo"
#define TAG_COLOR_ALTERNATIVO_HINICIAL "h-inicial"
#define TAG_COLOR_ALTERNATIVO_HFINAL "h-final"
#define TAG_COLOR_ALTERNATIVO_DESPLAZAMIENTO "desplazamiento"
#define TAG_JUGADOR_1 "jugador-1"
#define TAG_JUGADOR_2 "jugador-2"
#define TAG_JUGADOR_PERSONAJE "personaje"
#define TAG_JUGADOR_CONTROLJOYSTICK "control-joystick"
#define TAG_JUGADOR_CONTROLJOYSTICK_ID "id"
#define TAG_JUGADOR_CONTROLJOYSTICK_IZQ "izquierda"
#define TAG_JUGADOR_CONTROLJOYSTICK_DER "derecha"
#define TAG_JUGADOR_CONTROLJOYSTICK_ARRIBA "arriba"
#define TAG_JUGADOR_CONTROLJOYSTICK_ABAJO "abajo"
#define TAG_JUGADOR_CONTROLJOYSTICK_ARROJAR_ARMA "arrojar-arma"
#define TAG_JUGADOR_CONTROLJOYSTICK_GOLPE_ALTO "golpe-alto"
#define TAG_JUGADOR_CONTROLJOYSTICK_PATADA_ALTA "patada-alta"
#define TAG_JUGADOR_CONTROLJOYSTICK_BLOQUEAR "bloquear"

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
	list<PersonajeDef*>* personajesDef;
	list<JugadorDef*>* jugadoresDef;

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
	list<JugadorDef*>* getJugadoresDef() const;

private:
	void inicializar();
	void inciarValidacionSemantica();

    void parsearCapas();
    void parsearVentana();
    void parsearEscenario();
    void parsearPersonajes();
    JugadorDef* parsearJugador(string tag_jugador);
    void parsearJugadores();

};

#endif /* SRC_JSON_PARSER_H_ */
