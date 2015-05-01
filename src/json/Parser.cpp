/*
 * Parser.cpp
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#include "Parser.h"

#include <iostream>

#include "../modelo/Vector2f.h"
#include "../utils/Logger.h"
#include "../utils/Util.h"
#include "ColorAlternativoDef.h"
#include "EscenarioDef.h"
#include "SpriteDef.h"
#include "VentanaDef.h"


using std::string;

Parser::Parser() {

}

Parser::Parser(string archivo_json)
{
	this->entrada = archivo_json;
	this->ventana = NULL;
	this->escenario = NULL;
	this->capas = new list<CapaDef*>;

	this->personajesDef = new list<PersonajeDef*>();
	this->jugadoresDef = new list<JugadorDef*>();

	this->inicializar();
}

void Parser::inicializar()
{
	string escenario_defecto(JSON_POR_DEFECTO);

	if ( !Util::getInstancia()->existeArchivo(this->entrada) )
	{
		Logger::getInstance()->error("No existe el archivo de configuracion inicial "+this->entrada+
					". Se elije uno nuevo por defecto "+escenario_defecto);

		this->entrada = escenario_defecto;

	}

	ifstream archivo_escenario(this->entrada.c_str());
	if ( !this->reader.parse(archivo_escenario, this->root, false) )
	{
		this->entrada = escenario_defecto;

		Logger::getInstance()->error("No se pudo parsear con JSON por un problema sintactico. "+reader.getFormatedErrorMessages());
		Logger::getInstance()->info("Se va a cargar un escenario por defecto "+escenario_defecto);

		ifstream archivo_escenario2(this->entrada.c_str());
		this->reader.parse(archivo_escenario2, this->root, false);
	}

}

void Parser::cargarJsonPorDefecto(){
    entrada = JSON_POR_DEFECTO;
    ifstream archivo_escenario(this->entrada.c_str());
    reader.parse(archivo_escenario, this->root, false);
}

double obtenerValorDouble(Json::Value& principal, double alternativo, string msjNoNumerico){
    if (principal.isNumeric())
        return principal.asDouble();
    Logger::getInstance()->error(msjNoNumerico);
    return alternativo;
}

int obtenerValorInt(Json::Value& principal, int alternativo, string msjNoNumerico){
    if (principal.isInt())
        return principal.asInt();
    Logger::getInstance()->error(msjNoNumerico);
    return alternativo;
}

void Parser::parsearCapas(){

	if ( root.isMember(TAG_CAPAS) )
	{
		Json::Value valorCapas;
		valorCapas = root.get(TAG_CAPAS, &valorCapas);

		for (unsigned int idx_capas = 0; idx_capas < valorCapas.size(); ++idx_capas) {
			CapaDef* capa;
			string imagen_fondo;
			string id_capa;
			double ancho = 0;
			for( Json::ValueIterator it3 = valorCapas[idx_capas].begin() ; it3 != valorCapas[idx_capas].end() ; it3++ ) {
				string tag = it3.key().asString();

				if ( tag == TAG_CAPAS_IMAGEN ) {
					imagen_fondo = valorCapas[idx_capas][TAG_CAPAS_IMAGEN].asString();
				} else if ( tag == TAG_CAPAS_ID ) {
					id_capa = valorCapas[idx_capas][TAG_CAPAS_ID].asString();
				} else if ( tag == TAG_CAPAS_ANCHO ) {
					Json::Value valorAncho = valorCapas[idx_capas][TAG_CAPAS_ANCHO];
					ancho = obtenerValorDouble(valorAncho, ANCHO_CAPA_DEFAULT, "El valor de ancho de la capa no es un numero");
				} else {
					Logger::getInstance()->error("Dentro de la capa no se encuentra el parametro "+tag);
				}

			}
			capa = new CapaDef(imagen_fondo, id_capa, ancho);
			capas->push_back(capa);
		}
	}
	else
	{
		//se cargan capas por defecto porque no existe el tag "capas"
		CapaDef* capa_1 = new CapaDef("img_default/fondo-warrior-shrine-01.png", "id_capa_1", 700);
		CapaDef* capa_2 = new CapaDef("img_default/fondo-warrior-shrine-02.png", "id_capa_2", 1200);
		capas->push_back(capa_1);
		capas->push_back(capa_2);

    	Logger::getInstance()->error("No existe el tag "+(string)TAG_CAPAS+". Se van a cargar por defecto la siguientes 2 capas");
    	Logger::getInstance()->error(capa_1);
    	Logger::getInstance()->error(capa_2);
	}

}

void Parser::parsearEscenario(){
    Json::Value valorEsc;
    valorEsc = root.get(TAG_ESCENARIO, &valorEsc);

    //atributos del escenario
    double e_alto = 0;
    double e_ancho = 0;
    double e_ypiso = 0;

    for( Json::ValueIterator it2 = valorEsc.begin() ; it2 != valorEsc.end() ; it2++ ) {
        string tag = it2.key().asString();
        Json::Value subvalor = valorEsc[tag];

        if ( tag == TAG_ESCENARIO_ALTO ) {
            e_alto = obtenerValorDouble(subvalor, ALTO_ESC_DEFAULT, "Escenario alto no es valor numerico");
        } else if ( tag == TAG_ESCENARIO_ANCHO ) {
            e_ancho = obtenerValorDouble(subvalor, ANCHO_ESC_DEFAULT, "Escenario ancho no es valor numerico");
        } else if ( tag == TAG_ESCENARIO_YPISO) {
            e_ypiso = obtenerValorDouble(subvalor, Y_PISO_ESC_DEFAULT, "Escenario y_piso no es valor numerico");
        } else {
            Logger::getInstance()->error("Dentro del escenario no se encuentra el parametro "+tag);
        }
    }
    escenario = new EscenarioDef(e_ancho, e_alto, e_ypiso);
}

void Parser::parsearVentana(){
    Json::Value valorVentana;
    valorVentana = root.get(TAG_VENTANA, &valorVentana);

    //atributos de la ventana
    int v_alto_px = 0;
    double v_ancho = 0;
    int v_ancho_px = 0;

    for( Json::ValueIterator it2 = valorVentana.begin() ; it2 != valorVentana.end() ; it2++ ) {
        string tag = it2.key().asString();
        Json::Value subvalor = valorVentana[tag];

        if ( tag == TAG_VENTANA_ALTOPX ) {
            v_alto_px = obtenerValorInt(subvalor, ALTOPX_VENTANA_DEFAULT, "Ventana altopx no es valor entero");
        } else if ( tag == TAG_VENTANA_ANCHO ) {
            v_ancho = obtenerValorDouble(subvalor, ANCHO_VENTANA_DEFAULT, "Ventana ancho no es valor numerico");
        } else if ( tag == TAG_VENTANA_ANCHOPX ) {
            v_ancho_px = obtenerValorInt(subvalor, ANCHOPX_VENTANA_DEFAULT, "Ventana anchopx no es valor entero");
        } else {
            Logger::getInstance()->error("Dentro de la ventana no se encuentra el parametro "+tag);
        }
    }
    ventana = new VentanaDef(v_ancho_px, v_alto_px, v_ancho);
}

PersonajeDef* Parser::parsearPersonaje(string tag_personaje){
    Json::Value valorPersonaje;
    valorPersonaje = root.get(tag_personaje.c_str(), &valorPersonaje);

    //atributos del personaje
    double p_alto = 0;
    double p_ancho = 0;
    int p_zindex = 0;
    // del sprites reposo
    string p_sprites_imagen;
    string p_sprites_id;
    int p_sprites_cant_fotogramas = 0;
    int p_sprites_fps = 0;
	double color_alternativo_hinicial;
	double color_alternativo_hfinal;
	double color_alternativo_desplazamiento;

    int p_direccion = 0;
    list<SpriteDef*> sprites;

    for( Json::ValueIterator it2 = valorPersonaje.begin() ; it2 != valorPersonaje.end() ; it2++ ) {
        string tag = it2.key().asString();
        Json::Value subvalor = valorPersonaje[tag];

        if ( tag == TAG_PERSONAJE_ALTO ) {
            p_alto = obtenerValorDouble(subvalor, ALTO_PERS_DEFAULT, "Personaje alto no es valor numerico");
        } else if ( tag == TAG_PERSONAJE_ANCHO ) {
            p_ancho = obtenerValorDouble(subvalor, ANCHO_PERS_DEFAULT, "Personaje ancho no es valor numerico");
        } else if ( tag.compare(TAG_PERSONAJE_ZINDEX) >= 0) {
            p_zindex = obtenerValorInt(subvalor, Z_INDEX_PERS_DEFAULT, "Personaje zindex no es valor entero");
        } else if (tag.find(TAG_PERSONAJE_SPRITES) != std::string::npos) {
            p_sprites_imagen = (*it2)[TAG_PERSONAJE_SPRITES_IMAGEN].asString();
            int indiceId = string(TAG_PERSONAJE_SPRITES).size();
            p_sprites_id = (tag).substr(indiceId);

            Json::Value valorFotog = (*it2)[TAG_PERSONAJE_SPRITES_CANT_FOTOGRAMAS];
            Json::Value valorFps = (*it2)[TAG_PERSONAJE_SPRITES_FPS];

            p_sprites_cant_fotogramas = obtenerValorInt(valorFotog, CANT_FOTOGRAMAS_DEFAULT, "Personaje sprite cant_fotogramas no es valor entero");
            p_sprites_fps = obtenerValorInt(valorFps, FPS_DEFAULT, "Personaje sprite fps no es valor entero");

            SpriteDef* spriteDefAct = new SpriteDef(p_sprites_imagen, p_sprites_id, p_sprites_cant_fotogramas, p_sprites_fps);
            sprites.push_back(spriteDefAct);
        } else if ( tag == TAG_PERSONAJE_DIRECCION ) {
            p_direccion = obtenerValorInt(subvalor, DIRECCION_PERS_DERECHA, "Personaje direccion no es valor entero");
        } else if ( tag == TAG_COLOR_ALTERNATIVO ) {

            Json::Value valorColorAlternativo_hincial = (*it2)[TAG_COLOR_ALTERNATIVO_HINICIAL];
            Json::Value valorColorAlternativo_hfinal = (*it2)[TAG_COLOR_ALTERNATIVO_HFINAL];
            Json::Value valorColorAlternativo_desplazamiento = (*it2)[TAG_COLOR_ALTERNATIVO_DESPLAZAMIENTO];

            color_alternativo_hinicial = obtenerValorDouble(valorColorAlternativo_hincial, COLOR_ALTERNATIVO_HINICIAL_PERS_DEFAULT, "el h_inicial del color alternativo no es un valor numerico");
            color_alternativo_hfinal = obtenerValorDouble(valorColorAlternativo_hfinal, COLOR_ALTERNATIVO_HFINAL_PERS_DEFAULT, "el h_final del color alternativo no es un valor numerico");
            color_alternativo_desplazamiento = obtenerValorDouble(valorColorAlternativo_desplazamiento, COLOR_ALTERNATIVO_DESPLAZAMIENTO_PERS_DEFAULT, "el desplazamiento del color alternativo no es un valor numerico");

        }else {
            Logger::getInstance()->error("Dentro del personaje no se encuentra el parametro "+tag);
        }
    }
    Vector2f p_posInicial(escenario->getAncho()/2.0,escenario->getYpiso());
    ColorAlternativoDef* colorAlternativoDef = new ColorAlternativoDef(color_alternativo_hinicial, color_alternativo_hfinal, color_alternativo_desplazamiento);
    PersonajeDef* personajeParseado = new PersonajeDef(p_ancho, p_alto, p_zindex, p_direccion, p_posInicial, colorAlternativoDef);
    for (list<SpriteDef*>::iterator it = sprites.begin(); it != sprites.end(); ++it){
    	personajeParseado->agregarSpritesDef(*it);
    }

    return personajeParseado;
}

bool Parser::parsearDesdeJson() {
    Logger::getInstance()->info("Se Inicia el parseo desde el JSON "+this->entrada);

    if( root.size() <= 0 )
        return false;
    parsearVentana();
    parsearEscenario();
    parsearPersonajes();
    parsearCapas();
    parsearJugadores();

    Logger::getInstance()->info("Inicia la validacion semantica del json");
	this->inciarValidacionSemantica();
	Logger::getInstance()->info("Termina la validacion semantica del json");


    return true;
}

Parser::~Parser() {
	delete escenario;
    for (list<CapaDef*>::iterator it_capas = capas->begin() ; it_capas != capas->end(); ++capas)
        delete (*it_capas);
    delete ventana;
    //TODO eliminar los personajes
}

list<CapaDef*>* Parser::getCapasDef() const {
	return capas;
}

EscenarioDef* Parser::getEscenarioDef() const {
	return escenario;
}

VentanaDef* Parser::getVentanaDef() const {
	return ventana;
}

void Parser::inciarValidacionSemantica() {

	for (list<PersonajeDef*>::iterator it = personajesDef->begin() ; it != personajesDef->end(); ++it)
	{
	    (*it)->ajustarZIndex(capas->size());
	    //TODO ver de no ajustar 2 veces repetidas
	    escenario->ajustarYPiso((*it)->getAlto());
	    (*it)->ajustarAlto(escenario->getAlto(), escenario->getYpiso());
	    ventana->ajustarAncho(escenario->getAncho());
	    (*it)->ajustarPosicionIncial(escenario->getAncho(), ventana->getAncho(), escenario->getYpiso());
	    (*it)->ajustarColorAlternativo();
	}

    for (list<CapaDef*>::iterator it_capas = this->capas->begin() ; it_capas != this->capas->end(); it_capas++)
        (*it_capas)->ajustarAncho(escenario->getAncho(), ventana->getAncho());
}

list<PersonajeDef*>* Parser::getPersonajesDef() const {
	return this->personajesDef;
}

void Parser::parsearPersonajes() {

	//tomar los tag posibles de personajes
	list<string> tags_personajes;
	tags_personajes.push_back(TAG_PERSONAJE_1);
	tags_personajes.push_back(TAG_PERSONAJE_2);

	for (list<string>::iterator it = tags_personajes.begin() ; it != tags_personajes.end(); ++it)
	{
		this->personajesDef->push_back(this->parsearPersonaje(*it));
	}

}

list<JugadorDef*>* Parser::getJugadoresDef() const {
	return jugadoresDef;
}

JugadorDef* Parser::parsearJugador(string tag_jugador) {
    Json::Value valorJugador;
    valorJugador = root.get(tag_jugador.c_str(), &valorJugador);

    string personaje = "";

    for( Json::ValueIterator it2 = valorJugador.begin() ; it2 != valorJugador.end() ; it2++ ) {
        string tag = it2.key().asString();
        Json::Value subvalor = valorJugador[tag];

        if ( tag == TAG_JUGADOR_PERSONAJE ) {
        	personaje = subvalor.asString();
        } else {
            Logger::getInstance()->error("Dentro del jugador no se encuentra el parametro "+tag);
        }
    }

    JugadorDef* jugadorParseado = new JugadorDef(personaje);
    return jugadorParseado;
}

void Parser::parsearJugadores() {

	//tomar los tag posibles de personajes
	list<string> tags_jugadores;
	tags_jugadores.push_back(TAG_JUGADOR_1);
	tags_jugadores.push_back(TAG_JUGADOR_2);

	for (list<string>::iterator it = tags_jugadores.begin() ; it != tags_jugadores.end(); ++it)
	{
		this->jugadoresDef->push_back(this->parsearJugador(*it));
	}

}
