/*
 * Parser.cpp
 *
 *  Created on: 24/3/2015
 *      Author: ariel
 */

#include "Parser.h"

#include <iostream>

#include "../utils/Logger.h"
#include "../utils/Util.h"
#include "ColorAlternativoDef.h"
#include "ControlDef.h"
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

void Parser::parsearPersonajes()
{

	Json::Value valorPersonajes;
	valorPersonajes = root.get(TAG_PERSONAJES, &valorPersonajes);

	for (unsigned int idx_personajes = 0; idx_personajes < valorPersonajes.size(); ++idx_personajes)
	{
	    //atributos del personaje
		string id_personaje = "";
	    double p_alto = 0;
	    double p_ancho = 0;
	    int p_zindex = 0;
	    // del sprites reposo
	    string p_sprites_imagen = "";
	    string p_sprites_id = "";
	    int p_sprites_cant_fotogramas = 0;
	    int p_sprites_fps = 0;
		double color_alternativo_hinicial = 0;
		double color_alternativo_hfinal =0;
		double color_alternativo_desplazamiento = 0;

		//Sprite arma
		string p_arma_imagen;
		int p_arma_cant_fotogramas = 0;
		int p_arma_fps = 0;
		SpriteDef* spriteDefArma;
		int velocidad_arma = 0;
		double alto_arma = 0;
		double ancho_arma = 0;
		ArmaDef* arma;
		ColorAlternativoDef* colorAlternativoDef;

	    list<SpriteDef*> sprites;

		for( Json::ValueIterator it = valorPersonajes[idx_personajes].begin() ; it != valorPersonajes[idx_personajes].end() ; it++ )
		{
			string tag = it.key().asString();
			Json::Value subvalor = valorPersonajes[idx_personajes][tag];

			if ( tag == TAG_PERSONAJE_ID ) {
				id_personaje = subvalor.asString();
			} else if ( tag == TAG_PERSONAJE_ALTO ) {
				p_alto = obtenerValorDouble(subvalor, ALTO_PERS_DEFAULT, "Personaje alto no es valor numerico");
			} else if ( tag == TAG_PERSONAJE_ANCHO ) {
				p_ancho = obtenerValorDouble(subvalor, ANCHO_PERS_DEFAULT, "Personaje ancho no es valor numerico");
			} else if ( tag.compare(TAG_PERSONAJE_ZINDEX) >= 0) {
				p_zindex = obtenerValorInt(subvalor, Z_INDEX_PERS_DEFAULT, "Personaje zindex no es valor entero");
			} else if (tag.find(TAG_PERSONAJE_SPRITES) != std::string::npos) {
				p_sprites_imagen = (*it)[TAG_PERSONAJE_SPRITES_IMAGEN].asString();
				int indiceId = string(TAG_PERSONAJE_SPRITES).size();
				p_sprites_id = (tag).substr(indiceId);

				Json::Value valorFotog = (*it)[TAG_PERSONAJE_SPRITES_CANT_FOTOGRAMAS];
				Json::Value valorFps = (*it)[TAG_PERSONAJE_SPRITES_FPS];

				p_sprites_cant_fotogramas = obtenerValorInt(valorFotog, CANT_FOTOGRAMAS_DEFAULT, "Personaje sprite cant_fotogramas no es valor entero");
				p_sprites_fps = obtenerValorInt(valorFps, FPS_DEFAULT, "Personaje sprite fps no es valor entero");

				SpriteDef* spriteDefAct = new SpriteDef(p_sprites_imagen, p_sprites_id, p_sprites_cant_fotogramas, p_sprites_fps);
				sprites.push_back(spriteDefAct);
			}else if ( tag == TAG_PERSONAJE_ARMA ){
				Json::Value valor_alto_arma = (*it)[TAG_PERSONAJE_ARMA_ALTO];
				Json::Value valor_ancho_arma = (*it)[TAG_PERSONAJE_ARMA_ANCHO];
				p_arma_imagen = (*it)[TAG_PERSONAJE_SPRITES_IMAGEN].asString();
				Json::Value valorFotog = (*it)[TAG_PERSONAJE_SPRITES_CANT_FOTOGRAMAS];
				Json::Value valorFps = (*it)[TAG_PERSONAJE_SPRITES_FPS];
				Json::Value valor_velocidad_arma = (*it)[TAG_PERSONAJE_VELOCIDAD_ARMA];

				alto_arma = obtenerValorInt(valor_alto_arma, VELOCIDAD_ARMA_DEFAULT, "Personaje alto arma no es valor entero");
				ancho_arma = obtenerValorInt(valor_ancho_arma, VELOCIDAD_ARMA_DEFAULT, "Personaje ancho arma no es valor entero");
				p_arma_cant_fotogramas = obtenerValorInt(valorFotog, CANT_FOTOGRAMAS_DEFAULT, "Personaje sprite arma cant_fotogramas no es valor entero");
				p_arma_fps = obtenerValorInt(valorFps, FPS_DEFAULT, "Personaje sprite arma fps no es valor entero");
				velocidad_arma = obtenerValorInt(valor_velocidad_arma, VELOCIDAD_ARMA_DEFAULT, "Personaje velocidad arma no es valor entero");
				spriteDefArma = new SpriteDef(p_arma_imagen, TAG_PERSONAJE_ARMA, p_arma_cant_fotogramas, p_arma_fps);
				arma = new ArmaDef(spriteDefArma, velocidad_arma, ancho_arma, alto_arma);
			} else if ( tag == TAG_COLOR_ALTERNATIVO ) {

				Json::Value valorColorAlternativo_hincial = (*it)[TAG_COLOR_ALTERNATIVO_HINICIAL];
				Json::Value valorColorAlternativo_hfinal = (*it)[TAG_COLOR_ALTERNATIVO_HFINAL];
				Json::Value valorColorAlternativo_desplazamiento = (*it)[TAG_COLOR_ALTERNATIVO_DESPLAZAMIENTO];

				color_alternativo_hinicial = obtenerValorDouble(valorColorAlternativo_hincial, COLOR_ALTERNATIVO_HINICIAL_PERS_DEFAULT, "el h_inicial del color alternativo no es un valor numerico");
				color_alternativo_hfinal = obtenerValorDouble(valorColorAlternativo_hfinal, COLOR_ALTERNATIVO_HFINAL_PERS_DEFAULT, "el h_final del color alternativo no es un valor numerico");
				color_alternativo_desplazamiento = obtenerValorDouble(valorColorAlternativo_desplazamiento, COLOR_ALTERNATIVO_DESPLAZAMIENTO_PERS_DEFAULT, "el desplazamiento del color alternativo no es un valor numerico");

			    colorAlternativoDef = new ColorAlternativoDef(color_alternativo_hinicial, color_alternativo_hfinal, color_alternativo_desplazamiento);

			}else {
				Logger::getInstance()->error("Dentro del personaje no se encuentra el parametro "+tag);
			}

		}

	    PersonajeDef* personaje = new PersonajeDef(id_personaje, p_ancho, p_alto, p_zindex, colorAlternativoDef);

	    for (list<SpriteDef*>::iterator it = sprites.begin(); it != sprites.end(); ++it){
	    	personaje->agregarSpritesDef(*it);
	    }

	    personaje->agregarArmaDef(arma);
	    this->personajesDef->push_back(personaje);
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
	    (*it)->ajustarColorAlternativo();
	}

    for (list<CapaDef*>::iterator it_capas = this->capas->begin() ; it_capas != this->capas->end(); it_capas++)
        (*it_capas)->ajustarAncho(escenario->getAncho(), ventana->getAncho());
}

list<PersonajeDef*>* Parser::getPersonajesDef() const {
	return this->personajesDef;
}

list<JugadorDef*>* Parser::getJugadoresDef() const {
	return jugadoresDef;
}

JugadorDef* Parser::parsearJugador(string tag_jugador) {
    Json::Value valorJugador;
    valorJugador = root.get(tag_jugador.c_str(), &valorJugador);

    string personaje = "";
    string tipo_control = "";
    int control_pinia_alta = 0;
    int control_patada_alta = 0;
    int control_pinia_baja = 0;
    int control_patada_baja = 0;
    int control_defenza = 0;
    int control_poder = 0;
    int control_eje_horizontal = 0;
    int control_eje_vertical = 0;

    map<string, int>* correspondenciaTeclas = new map<string, int>;
    map<string, int>* correspondenciaEjes = new map<string, int>;

    for( Json::ValueIterator it2 = valorJugador.begin() ; it2 != valorJugador.end() ; it2++ ) {
        string tag = it2.key().asString();
        Json::Value subvalor = valorJugador[tag];

        if ( tag == TAG_JUGADOR_PERSONAJE ) {
        	personaje = subvalor.asString();
        } else if ( tag == TAG_JUGADOR_TIPO_CONTROL ) {
        	tipo_control = subvalor.asString();
        }
        else if ( tag == TAG_JUGADOR_CONTROL ) {
			control_pinia_alta = subvalor[TAG_JUGADOR_CONTROL_JOY_PINIA_ALTA].asInt();
			control_patada_alta = subvalor[TAG_JUGADOR_CONTROL_JOY_PATADA_ALTA].asInt();
			control_pinia_baja = subvalor[TAG_JUGADOR_CONTROL_JOY_PINIA_BAJA].asInt();
			control_patada_baja = subvalor[TAG_JUGADOR_CONTROL_JOY_PATADA_BAJA].asInt();
			control_defenza = subvalor[TAG_JUGADOR_CONTROL_JOY_DEFENSA].asInt();
			control_poder = subvalor[TAG_JUGADOR_CONTROL_JOY_PODER].asInt();
			control_eje_horizontal = subvalor[TAG_JUGADOR_CONTROL_JOY_EJE_HORIZONTAL].asInt();
			control_eje_vertical = subvalor[TAG_JUGADOR_CONTROL_JOY_EJE_VERTICAL].asInt();
		}else{
            Logger::getInstance()->error("Dentro del jugador no se encuentra el parametro "+tag);
        }
    }

    (*correspondenciaTeclas)[TAG_JUGADOR_CONTROL_JOY_PINIA_ALTA]  	= control_pinia_alta;
    (*correspondenciaTeclas)[TAG_JUGADOR_CONTROL_JOY_PATADA_ALTA]  	= control_patada_alta;
    (*correspondenciaTeclas)[TAG_JUGADOR_CONTROL_JOY_PINIA_BAJA]  	= control_pinia_baja;
    (*correspondenciaTeclas)[TAG_JUGADOR_CONTROL_JOY_PATADA_BAJA]  	= control_patada_baja;
    (*correspondenciaTeclas)[TAG_JUGADOR_CONTROL_JOY_DEFENSA]  		= control_defenza;
    (*correspondenciaTeclas)[TAG_JUGADOR_CONTROL_JOY_PODER]  		= control_poder;
    (*correspondenciaEjes)[TAG_JUGADOR_CONTROL_JOY_EJE_HORIZONTAL]  = control_eje_horizontal;
    (*correspondenciaEjes)[TAG_JUGADOR_CONTROL_JOY_EJE_VERTICAL]  	= control_eje_vertical;

    ControlDef* controlDef = new ControlDef(correspondenciaTeclas,correspondenciaEjes);

    JugadorDef* jugadorParseado = new JugadorDef(personaje, tipo_control, controlDef);
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
